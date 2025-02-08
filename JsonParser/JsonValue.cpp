#include "JsonValue.h"
#include <cassert>

namespace Json
{
	JsonValue::JsonValue()
		: JsonType(eJsonType::Object)
	{

	}
	JsonValue::JsonValue(const JsonValue& _Other)
		: JsonValueString(_Other.JsonValueString)
		, JsonType(_Other.JsonType)
	{
		VecJsonValue.reserve(_Other.VecJsonValue.size());
		for (size_t i = 0; i < _Other.VecJsonValue.size(); ++i)
		{
			VecJsonValue.push_back(new JsonValue(*_Other.VecJsonValue[i]));
		}

		for (auto iter = _Other.MapJsonValue.begin(); iter != _Other.MapJsonValue.end(); ++iter)
		{
			MapJsonValue.insert(std::make_pair(iter->first, new JsonValue(*iter->second)));
		}
	}
	JsonValue::~JsonValue()
	{
		for (size_t i = 0; i < VecJsonValue.size(); ++i)
		{
			if (VecJsonValue[i])
				delete VecJsonValue[i];
		}

		for (auto iter = MapJsonValue.begin(); iter != MapJsonValue.end(); ++iter)
		{
			if (iter->second)
				delete iter->second;
		}
	}
	JsonValue& Json::JsonValue::operator[](const std::string& _Name)
	{
		JsonValue* jsonValue = nullptr;
		auto iter = MapJsonValue.find(_Name);
		if (iter == MapJsonValue.end())
		{
			jsonValue = new JsonValue;
			MapJsonValue.insert(std::make_pair(_Name, jsonValue));
		}
		else
			jsonValue = iter->second;
		return *jsonValue;
	}
	JsonValue& JsonValue::operator[](size_t _Index)
	{
		if (VecJsonValue.size() <= _Index)
		{
			VecJsonValue.resize(_Index + 1);
		}
		return *VecJsonValue[_Index];
	}
	JsonValue& JsonValue::operator=(const std::string& _StringValue)
	{
		if (VecJsonValue.empty() == false)
		{
			for (size_t i = 0; i < VecJsonValue.size(); ++i)
				delete VecJsonValue[i];
			VecJsonValue.clear();
		}
		if (MapJsonValue.empty() == false)
		{
			for (auto iter = MapJsonValue.begin(); iter != MapJsonValue.end();)
			{
				delete iter->second;
				iter = MapJsonValue.erase(iter);
			}
			MapJsonValue.clear();
		}
		JsonType = eJsonType::String;
		JsonValueString = _StringValue;
		return *this;
	}
	JsonValue& JsonValue::operator=(int _IntValue)
	{
		if (VecJsonValue.empty() == false)
		{
			for (size_t i = 0; i < VecJsonValue.size(); ++i)
				delete VecJsonValue[i];
			VecJsonValue.clear();
		}
		if (MapJsonValue.empty() == false)
		{
			for (auto iter = MapJsonValue.begin(); iter != MapJsonValue.end();)
			{
				delete iter->second;
				iter = MapJsonValue.erase(iter);
			}
			MapJsonValue.clear();
		}
		JsonType = eJsonType::Int;
		JsonValueString = std::to_string(_IntValue);

		return *this;
	}
	JsonValue& JsonValue::operator=(double _DoubleValue)
	{
		if (VecJsonValue.empty() == false)
		{
			for (size_t i = 0; i < VecJsonValue.size(); ++i)
				delete VecJsonValue[i];
			VecJsonValue.clear();
		}
		if (MapJsonValue.empty() == false)
		{
			for (auto iter = MapJsonValue.begin(); iter != MapJsonValue.end();)
			{
				delete iter->second;
				iter = MapJsonValue.erase(iter);
			}
			MapJsonValue.clear();
		}
		JsonType = eJsonType::Double;
		JsonValueString = std::to_string(_DoubleValue);

		return *this;
	}
	JsonValue& JsonValue::operator=(eBooleanType _BooleanType)
	{
		if (VecJsonValue.empty() == false)
		{
			for (size_t i = 0; i < VecJsonValue.size(); ++i)
				delete VecJsonValue[i];
			VecJsonValue.clear();
		}
		if (MapJsonValue.empty() == false)
		{
			for (auto iter = MapJsonValue.begin(); iter != MapJsonValue.end();)
			{
				delete iter->second;
				iter = MapJsonValue.erase(iter);
			}
			MapJsonValue.clear();
		}
		JsonType = eJsonType::Boolean;
		if (_BooleanType == eBooleanType::False)
			JsonValueString = "false";
		else
			JsonValueString = "true";

		return *this;
	}
	JsonValue& JsonValue::operator=(eNullType _Null)
	{
		if (VecJsonValue.empty() == false)
		{
			for (size_t i = 0; i < VecJsonValue.size(); ++i)
				delete VecJsonValue[i];
			VecJsonValue.clear();
		}
		if (MapJsonValue.empty() == false)
		{
			for (auto iter = MapJsonValue.begin(); iter != MapJsonValue.end();)
			{
				delete iter->second;
				iter = MapJsonValue.erase(iter);
			}
			MapJsonValue.clear();
		}
		JsonType = eJsonType::Null;
		JsonValueString = "null";

		return *this;
	}
	JsonValue& JsonValue::operator=(const JsonValue& _JsonValue)
	{
		JsonType = _JsonValue.JsonType;
		JsonValueString = _JsonValue.JsonValueString;

		for (size_t i = 0; i < VecJsonValue.size(); ++i)
		{
			if (VecJsonValue[i])
				delete VecJsonValue[i];
		}
		VecJsonValue.clear();
		VecJsonValue.reserve(_JsonValue.VecJsonValue.size());
		for (size_t i = 0; i < _JsonValue.VecJsonValue.size(); ++i)
		{
			VecJsonValue.push_back(new JsonValue(*_JsonValue.VecJsonValue[i]));
		}

		for (auto iter = MapJsonValue.begin(); iter != MapJsonValue.end(); ++iter)
		{
			if (iter->second)
				delete iter->second;
		}
		MapJsonValue.clear();
		for (auto iter = _JsonValue.MapJsonValue.begin(); iter != _JsonValue.MapJsonValue.end(); ++iter)
		{
			MapJsonValue.insert(std::make_pair(iter->first, new JsonValue(*iter->second)));
		}

		return *this;
	}
	JsonValue& JsonValue::Append(const std::string& _StringValue)
	{
		JsonType = eJsonType::Array;
		if (MapJsonValue.empty() == false)
		{
			for (auto iter = MapJsonValue.begin(); iter != MapJsonValue.end(); )
			{
				delete iter->second;
				iter = MapJsonValue.erase(iter);
			}
		}
		if (JsonValueString.empty() == false)
			JsonValueString.clear();
		JsonValue* jsonValue = new JsonValue;
		*jsonValue = _StringValue;
		VecJsonValue.push_back(jsonValue);

		return *this;
	}
	JsonValue& JsonValue::Append(int _IntValue)
	{
		JsonType = eJsonType::Array;
		if (MapJsonValue.empty() == false)
		{
			for (auto iter = MapJsonValue.begin(); iter != MapJsonValue.end(); )
			{
				delete iter->second;
				iter = MapJsonValue.erase(iter);
			}
		}
		if (JsonValueString.empty() == false)
			JsonValueString.clear();
		JsonValue* jsonValue = new JsonValue;
		*jsonValue = _IntValue;
		VecJsonValue.push_back(jsonValue);

		return *this;
	}
	JsonValue& JsonValue::Append(double _DoubleValue)
	{
		JsonType = eJsonType::Array;
		if (MapJsonValue.empty() == false)
		{
			for (auto iter = MapJsonValue.begin(); iter != MapJsonValue.end(); )
			{
				delete iter->second;
				iter = MapJsonValue.erase(iter);
			}
		}
		if (JsonValueString.empty() == false)
			JsonValueString.clear();
		JsonValue* jsonValue = new JsonValue;
		*jsonValue = _DoubleValue;
		VecJsonValue.push_back(jsonValue);

		return *this;
	}
	JsonValue& JsonValue::Append(eBooleanType _BooleanType)
	{
		JsonType = eJsonType::Array;
		if (MapJsonValue.empty() == false)
		{
			for (auto iter = MapJsonValue.begin(); iter != MapJsonValue.end(); )
			{
				delete iter->second;
				iter = MapJsonValue.erase(iter);
			}
		}
		if (JsonValueString.empty() == false)
			JsonValueString.clear();
		JsonValue* jsonValue = new JsonValue;
		*jsonValue = _BooleanType;
		VecJsonValue.push_back(jsonValue);

		return *this;
	}
	JsonValue& JsonValue::Append(eNullType _Null)
	{
		JsonType = eJsonType::Array;
		if (MapJsonValue.empty() == false)
		{
			for (auto iter = MapJsonValue.begin(); iter != MapJsonValue.end(); )
			{
				delete iter->second;
				iter = MapJsonValue.erase(iter);
			}
		}
		if (JsonValueString.empty() == false)
			JsonValueString.clear();
		JsonValue* jsonValue = new JsonValue;
		*jsonValue = _Null;
		VecJsonValue.push_back(jsonValue);

		return *this;
	}
	JsonValue& JsonValue::Append(JsonValue& _JsonValue)
	{
		JsonType = eJsonType::Array;
		if (MapJsonValue.empty() == false)
		{
			for (auto iter = MapJsonValue.begin(); iter != MapJsonValue.end(); )
			{
				delete iter->second;
				iter = MapJsonValue.erase(iter);
			}
		}
		if (JsonValueString.empty() == false)
			JsonValueString.clear();
		VecJsonValue.push_back(new JsonValue(_JsonValue));
		return *this;
	}
	std::string JsonValue::AsString() const
	{
		if (JsonType == eJsonType::Object || JsonType == eJsonType::Array)
			return Stringfy();
		else
			return JsonValueString;
	}
	std::int32_t JsonValue::AsInt(eErrorType* error) const
	{
		std::int32_t returnValue = 0;
		*error = eErrorType::Ok;
		if (JsonType == eJsonType::Int)
			returnValue = std::stoi(JsonValueString);
		else if (JsonType == eJsonType::Double)
			returnValue = std::int32_t(std::stod(JsonValueString));
		else if (JsonType == eJsonType::Boolean)
			returnValue = JsonValueString == "true" ? true : false;
		else
			*error = eErrorType::Fail;

		return returnValue;
	}
	double JsonValue::AsDouble(eErrorType* error) const
	{
		double returnValue = 0.0f;
		*error = eErrorType::Ok;
		if (JsonType == eJsonType::Int)
			returnValue = double(std::stoi(JsonValueString));
		else if (JsonType == eJsonType::Double)
			returnValue = std::stod(JsonValueString);
		else
			*error = eErrorType::Fail;
		return returnValue;
	}
	bool JsonValue::AsBoolean(eErrorType* error) const
	{
		bool returnValue = true;
		*error = eErrorType::Ok;
		if (JsonType == eJsonType::Int)
			returnValue = std::stoi(JsonValueString);
		else if (JsonType == eJsonType::Boolean)
			returnValue = JsonValueString == "true" ? bool(eBooleanType::True) : bool(eBooleanType::False);
		else
			*error = eErrorType::Fail;

		return returnValue;
	}
	void* JsonValue::AsNull(eErrorType* error) const
	{
		void* returnValue = nullptr;
		*error = eErrorType::Ok;
		if (JsonType != eJsonType::Null)
			*error = eErrorType::Fail;

		return returnValue;
	}
	std::string JsonValue::Stringfy() const
	{
		return stringfy(0, false).substr(1);
	}
	std::string JsonValue::stringfy(size_t _Indent, bool _IsArray) const
	{
		std::string spacing;
		spacing.resize(_Indent);
		std::fill(spacing.begin(), spacing.end(), ' ');

		std::string result;

		if (JsonValueString.empty() == false)
		{
			if (_IsArray)
				result += spacing;
			if (JsonType == eJsonType::String)
				result += '\"' + JsonValueString + '\"';
			else
				result += JsonValueString;
		}

		else if (JsonType == eJsonType::Array)
		{
			if (VecJsonValue.size())
				result += '\n' + spacing;
			result += '[';
			if (VecJsonValue.size())
				result += '\n';
			for (size_t i = 0; i < VecJsonValue.size(); ++i)
			{
				result += VecJsonValue[i]->stringfy(_Indent + 2, true);
				if (i != VecJsonValue.size() - 1)
					result += ',';
				result += '\n';
			}
			if (VecJsonValue.size())
				result += spacing;
			result += "]";
		}
		else if (JsonType == eJsonType::Object)
		{
			if (_IsArray == false)
				result += '\n';
			result += spacing + "{\n";
			for (auto iter = MapJsonValue.begin(); iter != MapJsonValue.end(); ++iter)
			{
				result += spacing + "  \"" + iter->first + "\": " + iter->second->stringfy(_Indent + 2, false);
				if (iter->first != MapJsonValue.rbegin()->first)
					result += ',';
				result += '\n';
			}
			result += spacing + "}";
		}

		return result;
	}
}

std::ostream& operator<<(std::ostream& _Os, const Json::JsonValue& _JsonValue)
{
	_Os << _JsonValue.Stringfy();
	return _Os;
}

