#pragma once
#include "Mimou/Logging.h"
#include "yaml-cpp/yaml.h"

namespace Mimou
{

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
			std::string PropertyType;

			SetValueFn<ValueType> SetValue;
			GetValueFn<ValueType> GetValue;

			//SerializeFn Serialize;
		};

	public:
		ClassDescriptor() = delete;
		ClassDescriptor(const std::string& ClassName) : m_ClassName(ClassName) {}

		template<typename ValueType>
		bool RegisterProperty(const std::string& PropName, const MimouProperty<ValueType>& Property)
		{
			Properties.insert(PropName, Property);
			PropertySignitures.insert(PropName, Property.PropertyName);
		}

		template<typename ValueType>
		ValueType GetPropertyValue(ClassType* Obj, const std::string& PropName)
		{
			if (!Obj)
			{
				ME_ENGINE_WARN("Object is null");
				return ValueType();
			}
			if (!Properties.contains(PropName))
			{
				ME_ENGINE_WARN("Property {} doesn't exist", PropName);
				return ValueType();
			}

			MimouProperty<ValueType> Prop = Properties[PropName];
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
			if (!Properties.contains(PropName))
			{
				ME_ENGINE_WARN("Property {} doesn't exist", PropName);
				return false;
			}

			MimouProperty<ValueType> Prop = Properties[PropName];
			Prop.SetValueFn(Obj, Value);
		}

		std::map<std::string, std::string> PropertySignitures;

		template<typename ValueType>
		static std::map<std::string, MimouProperty<ValueType>> Properties;

		std::string m_ClassName;

	public:
		static ClassDescriptor* Get();

	private:
		static ClassDescriptor* s_Instance;
	};
	
}


#define ME_CLASS(ClassType) class ClassType;

#define DECLARE_ME_CLASS(ClassType) static std::string StaticClass() { return #ClassType; } \
								::Mimou::ClassDescriptor<ClassType>* GetClass() { return ::Mimou::ClassDescriptor<ClassType>::Get(); }

//#define ME_PROPERTY(PropType, PropName) 


#define IMPLEMENT_ME_CLASS(ClassType) ::Mimou::ClassDescriptor<ClassType>* ::Mimou::ClassDescriptor<ClassType>::s_Instance = nullptr; \
			::Mimou::ClassDescriptor<ClassType>* ::Mimou::ClassDescriptor<ClassType>::Get() { if (!s_Instance) s_Instance = new ::Mimou::ClassDescriptor<ClassType>(#ClassType); return s_Instance; }

