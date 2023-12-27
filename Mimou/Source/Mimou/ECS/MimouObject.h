#pragma once
#include "Mimou/Logging.h"
#include "yaml-cpp/yaml.h"

namespace Mimou
{
	enum class MimouValueType : INT32
	{
		NONE = 0,
		STRING = 1,
	};
	extern const std::string TypeStr[256];

	//void SerializeString(YAML::Emitter& Out, const std::string& Key, const std::string& Value)
	//{
	//	Out << YAML::Key << Key;
	//	Out << YAML::Value << Value;
	//}

	//template<typename Property>
	//void SerializeProperty(YAML::Emitter& Out, const std::string& Key, const Property& Value, const std::string& ValueType)
	//{
	//	switch (ValueType)
	//	{
	//	case "std::string":
	//	{
	//		SerializeString(Out, Key, Value);
	//		break;
	//	}
	//	default:
	//	{
	//		ME_ENGINE_WARN("Serialization failed due to unsupported value type: {}", ValueType);
	//		break;
	//	}
	//	}
	//}

	//template<typename Property>
	//using SerializeFn = std::function<void<YAML::Emitter&, const std::string&, const T&, const std::string&>>;


	template<typename ClassType>
	class ClassDescriptor
	{
	public:

		template<typename ValueType>
		using SetValueFn = std::function<void(ClassType*, ValueType)>;

		template<typename ValueType>
		using GetValueFn = std::function<ValueType(ClassType*)>;

		template<typename ValueType>
		struct MimouProperty
		{
			std::string PropertyName;
			MimouValueType PropertyType;

			SetValueFn<ValueType> SetValue;
			GetValueFn<ValueType> GetValue;

			//SerializeFn Serialize;
		};

	public:
		ClassDescriptor() = delete;
		ClassDescriptor(const std::string& ClassName) : m_ClassName(ClassName) {}

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
		ValueType GetPropertyValue(ClassType* Obj, const std::string& PropName)
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
			return Prop.GetValueFn(Obj);
		}

		template<typename ValueType>
		bool SetPropertyValue(ClassType* Obj, const std::string& PropName, const ValueType& Value)
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
			Prop.SetValueFn(Obj, Value);
		}

		std::map<std::string, MimouValueType> PropertySignitures;


		std::map<std::string, MimouProperty<std::string>> StringProperties;

		std::string m_ClassName;

	//public:
	//	template<typename T>
	//	static ClassDescriptor* Get();

	//private:
	//	static ClassDescriptor* s_Instance;
	};
	
	template<typename ClassType>
	Ref<ClassType> LoadObject(const std::string& AssetPath)
	{
		return CreateRef<ClassType>("Demo Scene");
	}
}


#define ME_CLASS(ClassType) class ClassType;

#define DECLARE_ME_CLASS(ClassType) static std::string StaticClass() { return #ClassType; } \
								::Mimou::ClassDescriptor<ClassType>* GetClass();

//#define ME_PROPERTY(PropType, PropName) 


#define IMPLEMENT_ME_CLASS(ClassType) ::Mimou::ClassDescriptor<ClassType>* m_ClassDescriptor##ClassType = new ::Mimou::ClassDescriptor<ClassType>(#ClassType); \
								::Mimou::ClassDescriptor<ClassType>* ClassType::GetClass() { return m_ClassDescriptor##ClassType; }

