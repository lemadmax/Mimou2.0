#pragma once
#include "Mimou/Logging.h"

namespace Mimou
{
	enum class MimouValueType : INT32
	{
		NONE = 0,
		STRING = 1,
		MAP = 2,
		ME_OBJECT = 3,
	};
	extern const std::string TypeStr[256];

	struct MEObject;

	class ClassDescriptor
	{
	public:

		using CreateObjectFn = std::function<MEObject*()>;

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
		ClassDescriptor(const std::string& ClassName, CreateObjectFn CreateFn) : m_ClassName(ClassName), m_CreateObject(CreateFn) {}

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

	struct MEObject
	{
		virtual ClassDescriptor* GetClass() = 0;
	};
	
	template<typename ClassType>
	Ref<ClassType> LoadObject(const std::string& AssetPath)
	{
		YAML::Node RawData = YAML::LoadFile(AssetPath);
		if (RawData)
		{
			std::string AssetType = RawData["ClassType"].as<std::string>();
			if (AssetType == ClassType::StaticClass())
			{
				MEObject* OutPtr = MEObjectManager::GetInstance()->CreateObject(AssetType);
				if (!OutPtr)
				{
					ME_ENGINE_ERROR("Failed to create object {}", AssetType);
					return nullptr;
				}
				Ref<ClassType> Out(static_cast<ClassType*>(OutPtr));
				ClassDescriptor* ClassDesc = Out->GetClass();
				for (auto [PropName, PropType] : ClassDesc->PropertySignitures)
				{
					switch (PropType)
					{
					case MimouValueType::STRING:
					{
						std::string Data = RawData[PropName].as<std::string>();
						ClassDesc->SetPropertyValue<std::string>(Out.get(), PropName, Data);
						break;
					}
					default:
					{
						ME_ENGINE_WARN("Data type not supported");
						break;
					}
					}
				}
				return Out;
			}
		}
		else
		{
			ME_ENGINE_ERROR("Failed to load asset: {}", AssetPath);
		}
		return nullptr;
	}

	template<typename T>
	bool SaveObject(T* Obj, const std::string& AssetPath)
	{
		MimouSerializer::SaveMEObject(Obj, AssetPath);
	}

}


#define ME_CLASS(ClassType) class ClassType;

#define DECLARE_ME_CLASS(ClassType) public: static std::string StaticClass() { return #ClassType; } \
								virtual ::Mimou::ClassDescriptor* GetClass();



#define IMPLEMENT_ME_CLASS(ClassType) ::Mimou::ClassDescriptor* m_ClassDescriptor##ClassType = new ::Mimou::ClassDescriptor(#ClassType, []() { return new ClassType(); }); \
								::Mimou::ClassDescriptor* ClassType::GetClass() { return m_ClassDescriptor##ClassType; }

#define ME_MAP(Key, Value) std::map<Key, Value>
#define REGISTER_CLASS(ClassType) ::Mimou::MEObjectManager::GetInstance()->RegisterMEClass(#ClassType, m_ClassDescriptor##ClassType); 
#define REGISTER_PROPERTY(ClassType, PropName, PropType, MimouType) m_ClassDescriptor##ClassType->RegisterProperty<PropType>(#PropName, { #PropName, MimouType, \
									[](MEObject* Obj, PropType Value) { \
										ClassType* Derived = static_cast<ClassType*>(Obj); \
										Derived->PropName = Value; \
										}, \
										[](MEObject* Obj) { \
										ClassType* Derived = static_cast<ClassType*>(Obj); \
										return Derived->PropName; \
										} });

#define DECLARE_ME_STRUCT(StructName) static std::string StaticClass() { return #StructName;} \
								virtual ::Mimou::ClassDescriptor* GetClass();

#define IMPLEMENT_ME_STRUCT(StructName) ::Mimou::ClassDescriptor* m_ClassDescriptor##StructName = new ::Mimou::ClassDescriptor(#StructName, []() { return new StructName(); }); \
								::Mimou::ClassDescriptor* StructName::GetClass() { return m_ClassDescriptor##StructName; }