#pragma once
#include "Mimou/Logging.h"
#include "MimouSerializer.h"

namespace Mimou
{
	enum class MimouValueType : INT32
	{
		NONE = 0,
		STRING = 1,
		ME_OBJ_MAP = 2,
		ME_OBJECT = 3,
	};
	extern const std::string TypeStr[256];

	class MEObject;

	class ClassDescriptor
	{
	public:

		using CreateObjectFn = std::function<MEObject*()>;
		using InitFn = std::function<void(ClassDescriptor*)>;

		template<typename ValueType>
		using SetValueFn = std::function<void(MEObject*, ValueType)>;

		template<typename ValueType>
		using GetValueFn = std::function<ValueType(MEObject*)>;

		template<typename ValueType>
		struct MimouProperty
		{
			std::string PropertyName;
			MimouValueType PropertyType;

			SetValueFn<ValueType> SetValue;
			GetValueFn<ValueType> GetValue;
		};

	public:
		ClassDescriptor() = delete;
		ClassDescriptor(const std::string& ClassName, CreateObjectFn CreateFn, InitFn Init) : m_ClassName(ClassName), m_CreateObject(CreateFn) 
		{
			Init(this);
		}

		std::string GetClassType() { return m_ClassName; }

		CreateObjectFn m_CreateObject;

		MEObject* CreateNewObject()
		{
			return m_CreateObject();
		}

		template<typename ValueType>
		void RegisterProperty(const std::string& PropName, const MimouProperty<ValueType>& Property)
		{
			if (!PropertySignitures.contains(PropName))
				PropertySignitures.insert(std::make_pair(PropName, Property.PropertyType));
			MimouProperty<ValueType> Temp = Property;
			SetGetProperty<ValueType>(PropName, Property.PropertyType, Temp);
		}

		template<typename ValueType>
		void SetGetProperty(const std::string PropName, MimouValueType PropType, MimouProperty<ValueType>& Out)
		{
			switch (PropType)
			{
			case MimouValueType::STRING:
			{
				if (StringProperties.contains(PropName))
				{
					Out = StringProperties[PropName];
				}
				else
				{
					StringProperties.insert(std::make_pair(PropName, Out));
				}
				break;
			}
			case MimouValueType::ME_OBJECT:
			{
				if (MEObjProperties.contains(PropName))
				{
					Out = MEObjProperties[PropName];
				}
				else
				{
					MEObjProperties.insert(std::make_pair(PropName, Out));
				}
			}
			default:
			{
				ME_ENGINE_WARN("Mimou hasn't support type {}", TypeStr[(INT32)PropType]);
				break;
			}
			}
		}

		template<typename ValueType>
		ValueType GetPropertyValue(MEObject* Obj, const std::string& PropName)
		{
			if (!Obj)
			{
				ME_ENGINE_WARN("Object is null");
				return ValueType();
			}
			if (!PropertySignitures.contains(PropName))
			{
				ME_ENGINE_WARN("Property {} doesn't exist", PropName);
				return ValueType();
			}

			MimouProperty<ValueType> Prop;
			SetGetProperty<ValueType>(PropName, PropertySignitures[PropName], Prop);
			return Prop.GetValue(Obj);
		}

		template<typename ValueType>
		bool SetPropertyValue(MEObject* Obj, const std::string& PropName, const ValueType& Value)
		{
			if (!Obj)
			{
				ME_ENGINE_WARN("Object is null");
				return false;
			}
			if (!PropertySignitures.contains(PropName))
			{
				ME_ENGINE_WARN("Property {} doesn't exist", PropName);
				return false;
			}

			MimouProperty<ValueType> Prop;
			SetGetProperty<ValueType>(PropName, PropertySignitures[PropName], Prop);
			Prop.SetValue(Obj, Value);
		}

		std::map<std::string, MimouValueType> PropertySignitures;


		std::map<std::string, MimouProperty<std::string>> StringProperties;

		std::map<std::string, MimouProperty<Ref<MEObject>>> MEObjProperties;

		std::string m_ClassName;

	};

	class MEObjectManager
	{
	private:
		MEObjectManager() = default;

	public:

		static MEObjectManager* GetInstance()
		{
			if (!s_Instance)
			{
				s_Instance = new MEObjectManager();
			}
			return s_Instance;
		}

		void RegisterMEClass(const std::string& ClassName, ClassDescriptor* CD);

		MEObject* CreateObject(const std::string& ClassName);

	private:
		static MEObjectManager* s_Instance;

		std::map<std::string, ClassDescriptor*> ClassLibs;
	};

	//class MEObject
	//{
	//public:

	//	virtual ClassDescriptor* GetClass() = 0;

	//};

	class MEObject
	{
	public:
		MEObject()
		{
			ME_ENGINE_LOG("Initializing properties");
		}
		virtual ClassDescriptor* GetClass() { return nullptr; }
	};
	
	class MimouSerializer;

	template<typename ClassType>
	Ref<MEObject> LoadObject(const std::string& AssetPath)
	{
		return MimouSerializer::LoadMEObject(ClassType::StaticClass(), AssetPath);
	}

	template<typename ClassType>
	bool SaveObject(Ref<ClassType> Obj, const std::string& AssetPath)
	{
		MimouSerializer::SaveMEObject(Obj, AssetPath);
		return true;
	}

}


#define ME_CLASS(ClassType) class ClassType;

#define DECLARE_ME_CLASS(ClassType) public: static std::string StaticClass() { return #ClassType; } \
								virtual ::Mimou::ClassDescriptor* GetClass(); 

#define ME_MAP(Key, Value) std::map<Key, Value>


#define BEGIN_ME_CLASS(ClassType) ::Mimou::ClassDescriptor* m_ClassDescriptor##ClassType = new ::Mimou::ClassDescriptor(#ClassType, []() { return new ClassType(); }, \
								[](::Mimou::ClassDescriptor* CD) { 

#define REGISTER_PROPERTY(ClassType, PropName, PropType, MimouType) CD->RegisterProperty<PropType>(#PropName, { #PropName, MimouType, \
									[](MEObject* Obj, PropType Value) { \
										ClassType* Derived = static_cast<ClassType*>(Obj); \
										Derived->PropName = Value; \
										}, \
										[](MEObject* Obj) { \
										ClassType* Derived = static_cast<ClassType*>(Obj); \
										return Derived->PropName; \
										} });

#define END_ME_CLASS(ClassType)	}); ::Mimou::ClassDescriptor* ClassType::GetClass() { return m_ClassDescriptor##ClassType; }
						


#define DECLARE_ME_STRUCT(StructName) static std::string StaticClass() { return #StructName;} \
								virtual ::Mimou::ClassDescriptor* GetClass();

#define IMPLEMENT_ME_STRUCT(StructName) ::Mimou::ClassDescriptor* m_ClassDescriptor##StructName = new ::Mimou::ClassDescriptor(#StructName, []() { return new StructName(); }); \
								::Mimou::ClassDescriptor* StructName::GetClass() { return m_ClassDescriptor##StructName; }