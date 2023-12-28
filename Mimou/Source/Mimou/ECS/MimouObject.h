#pragma once
#include "Mimou/Logging.h"
#include "yaml-cpp/yaml.h"

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
			return Prop.GetValue(Obj);
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
			Prop.SetValue(Obj, Value);
		}

		std::map<std::string, MimouValueType> PropertySignitures;


		std::map<std::string, MimouProperty<std::string>> StringProperties;

		std::string m_ClassName;

	};
	
	template<typename ClassType>
	Ref<ClassType> LoadObject(const std::string& AssetPath)
	{
		Ref<ClassType> Out = CreateRef<ClassType>();
		YAML::Node RawData = YAML::LoadFile(AssetPath);
		if (RawData)
		{
			ClassDescriptor<ClassType>* ClassDesc = Out->GetClass();
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
		}
		else
		{
			ME_ENGINE_ERROR("Failed to load asset: {}", AssetPath);
		}
		return Out;
	}
}


#define ME_CLASS(ClassType) class ClassType;

#define DECLARE_ME_CLASS(ClassType) public: static std::string StaticClass() { return #ClassType; } \
								::Mimou::ClassDescriptor<ClassType>* GetClass();



#define IMPLEMENT_ME_CLASS(ClassType) ::Mimou::ClassDescriptor<ClassType>* m_ClassDescriptor##ClassType = new ::Mimou::ClassDescriptor<ClassType>(#ClassType); \
								::Mimou::ClassDescriptor<ClassType>* ClassType::GetClass() { return m_ClassDescriptor##ClassType; }

#define ME_MAP(Key, Value) std::map<Key, Value>
#define REGISTER_PROPERTY(ClassType, PropName, PropType, MimouType) m_ClassDescriptor##ClassType->RegisterProperty<PropType>(#PropName, { #PropName, MimouType, \
									[](ClassType* Obj, PropType Value) { \
										Obj->PropName = Value; \
										}, \
										[](ClassType* Obj) { \
										return Obj->PropName; \
										} });
