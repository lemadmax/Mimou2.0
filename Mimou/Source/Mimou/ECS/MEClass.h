#pragma once

namespace Mimou
{
	class MEObject;
	class MEProperty;
	class MEClassManager;
	class GameObject;

	enum class MEPropType : UINT32
	{
		NONE = 0,
		BOOL,
		INT,
		FLOAT,
		STRING,
		STRING_VEC,
		OBJ_REF,
		GAME_OBJ_REF_MAP,
		COMP_SET,
		VEC3,
	};

	struct MEProperty
	{
		uint32_t m_Offset;
		std::string m_PropName;
		MEPropType m_PropType;
	};

	class MEClass
	{
		using InstantiateFn = std::function<Ref<MEObject>()>;
		using InstantiateFnPtr = std::function<MEObject* ()>;
	public:
		MEClass() = delete;
		MEClass(const std::string& ClassName, InstantiateFn InstFn, InstantiateFnPtr InstFnPtr);

		Ref<MEObject> Instantiate()
		{
			return m_InstFn();
		}

		MEObject* InstantiatePtr()
		{
			return m_InstFnPtr();
		}

		void RegisterProperty(const std::string& PropName, MEProperty Prop);

		inline std::string GetName() const { return m_ClassName; }

		inline std::map<std::string, MEProperty> GetProperties() const { return m_Properties; }

		bool HasProperty(const std::string& PropName)
		{
			return (m_Properties.contains(PropName));
		}

		template<typename T>
		T GetValue(const void* Obj, const std::string& PropName)
		{
			if (!m_Properties.contains(PropName))
			{
				return T();
			}
			MEProperty Prop = m_Properties[PropName];
			char* Dest = (char*)Obj + Prop.m_Offset;
			return *(T*)Dest;
		}

		template<typename T>
		void SetValue(const void* Obj, const std::string& PropName, const T& Value)
		{
			if (!m_Properties.contains(PropName))
			{
				return;
			}
			MEProperty Prop = m_Properties[PropName];
			char* Dest = (char*)Obj + Prop.m_Offset;
			*(T*)Dest = Value;
		}

	private:
		std::string m_ClassName;

		InstantiateFn m_InstFn;
		InstantiateFnPtr m_InstFnPtr;

		std::map<std::string, MEProperty> m_Properties;
	};

	class MEPropertyCreator
	{
	public:
		MEPropertyCreator() = delete;
		MEPropertyCreator(MEObject* ObjPtr, const std::string& PropName, void* PropPtr, MEPropType PropType);
	};

	class MEClassManager
	{
	private:
		MEClassManager() = default;

	public:
		static MEClassManager* GetInstance()
		{
			static MEClassManager s_Instance;
			return &s_Instance;
		}


		void RegisterMEClass(MEClass* Class);
		MEClass* GetClass(const std::string& ClassName);


	private:
		std::map<std::string, MEClass*> ClassMap;
	};
}

#define DECLARE_ME_CLASS(ClassName) public: \
static std::string StaticClass() { return #ClassName; } \
virtual ::Mimou::MEClass* GetClass() { return MEClassManager::GetInstance()->GetClass(#ClassName); } \
virtual bool IsA(const std::string& Class) { return #ClassName == Class; }

#define IMPLEMENT_ME_CLASS(ClassName) ::Mimou::MEClass* MEClass##ClassName = new ::Mimou::MEClass(#ClassName, []() { return CreateRef<ClassName>(); }, []() { return new ClassName(); });

#define ME_PROPERTY(PropName, PropType) const ::Mimou::MEPropertyCreator __Creator##PropName = ::Mimou::MEPropertyCreator((::Mimou::MEObject*)this, #PropName, &this->PropName, PropType);