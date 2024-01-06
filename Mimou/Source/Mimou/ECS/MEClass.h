#pragma once

namespace Mimou
{
	class MEObject;
	class MEProperty;
	class MEClassManager;

	enum class MEPropType : UINT32
	{
		NONE = 0,
		INT,
		STRING,
		OBJ_MAP,
	};

	class MEClass
	{
	public:
		MEClass() = delete;
		MEClass(const std::string& ClassName) : m_ClassName(ClassName)
		{

		}

		void RegisterProperty(const std::string& PropName, MEProperty* Prop);

		inline std::string GetName() const { return m_ClassName; }

		inline std::map<std::string, MEProperty*> GetProperties() const { return m_Properties; }

	private:
		std::string m_ClassName;

		std::map<std::string, MEProperty*> m_Properties;
	};

	class MEProperty
	{
	public:
		MEProperty() = delete;
		MEProperty(MEObject* ObjPtr, const std::string& PropName, void* PropPtr, MEPropType PropType);

		std::string GetString(const void* Obj);
		int GetInt(const void* Obj);

	public:
		uint32_t m_Offset;
		std::string m_PropName;
		MEPropType m_PropType;
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

		MEClass* GetClass(const std::string& ClassName);


	private:
		std::map<std::string, MEClass*> ClassMap;
	};
}

#define DECLARE_ME_CLASS(ClassName) public: \
static std::string StaticClass() { return #ClassName; } \
virtual ::Mimou::MEClass* GetClass() { return ::Mimou::MEClassManager::GetInstance()->GetClass(#ClassName); }

#define ME_PROPERTY(PropName, PropType) const ::Mimou::MEProperty __##PropName = ::Mimou::MEProperty((::Mimou::MEObject*)this, #PropName, &this->PropName, PropType);