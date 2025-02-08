#include "Json.h"
#include <fstream>

namespace Json
{
	JsonValue Json::ParseJsonByFile(const std::string& _FileName)
	{
		JsonValue jsonValue;
		std::string jsonString = Json::SerializeJson(_FileName);
		parseJson(jsonValue, jsonString, 0, false);
		return jsonValue;
	}
	size_t Json::parseJson(JsonValue& _ParentJson, const std::string& _JsonString, size_t _StartIdx, bool _IsArray)
	{
		auto getFirstChar = [](const std::string& string, size_t startIdx)->std::pair<char, size_t>
			{
				char ch = 0;
				while (true)
				{
					if (string[startIdx] == ' ')
					{
						startIdx = startIdx + 1;
						continue;
					}

					ch = string[startIdx];

					if (ch)
						break;

					startIdx = startIdx + 1;
				}
				return std::make_pair(ch, startIdx);
			};
		std::string key;
		std::string value;
		size_t finish = 0;
		size_t count = 0;
		std::pair<char, size_t> pair;

		while (true)
		{
			JsonValue* jsonValue = nullptr;
			if (_IsArray == false)
			{
				_StartIdx = _JsonString.find('\"', _StartIdx) + 1;
				finish = _JsonString.find('\"', _StartIdx);
				count = finish - _StartIdx;
				key = _JsonString.substr(_StartIdx, count);
				_StartIdx = _JsonString.find(':', finish) + 1;
			}

			pair = getFirstChar(_JsonString, _StartIdx);
			_StartIdx = pair.second + 1;
			if (pair.first == '{')
			{
				jsonValue = new JsonValue;
				jsonValue->SetJsonType(eJsonType::Object);
				finish = parseJson(*jsonValue, _JsonString, _StartIdx, false);
			}
			else if (pair.first == '[')
			{
				finish = parseJson(_ParentJson[key], _JsonString, _StartIdx, true);
			}
			else if (pair.first == ',')
			{
				continue;
			}
			else if (pair.first == '\"')
			{
				jsonValue = new JsonValue;
				finish = _JsonString.find('\"', _StartIdx);
				count = finish - _StartIdx;
				*jsonValue = _JsonString.substr(_StartIdx, count);
				jsonValue->SetJsonType(eJsonType::String);
			}
			else if (pair.first == ']')
			{
				_ParentJson.SetJsonType(eJsonType::Array);
				return pair.second;
			}
			else if (pair.first == '}')
			{
				return pair.second;
			}
			else
			{
				jsonValue = new JsonValue;
				_StartIdx -= 1;
				int i = 1;
				char c = 0;
				while (true)
				{
					c = _JsonString[_StartIdx + i];
					if (('0' <= c && c <= '9') || c == 'n' || c == 'u' || c == 'l'
						|| c == 'f' || c == 'a' || c == 's'
						|| c == 't' || c == 'r' || c == 'u' || c == 'e'
						|| c == '.' || c == '-')
						++i;
					else
						break;
				}
				finish = _StartIdx + i - 1;
				count = finish - _StartIdx + 1;
				*jsonValue = _JsonString.substr(_StartIdx, count);

				eJsonType type;
				if (jsonValue->GetJsonValueString() == "null")
					type = eJsonType::Null;
				else if (jsonValue->GetJsonValueString() == "true" || jsonValue->GetJsonValueString() == "false")
					type = eJsonType::Boolean;
				else if (jsonValue->GetJsonValueString().find('.') != std::string::npos
					|| jsonValue->GetJsonValueString().find('e') != std::string::npos)
					type = eJsonType::Double;
				else
					type = eJsonType::Int;
				jsonValue->SetJsonType(type);
			}

			if (jsonValue)
			{
				if (_IsArray)
					_ParentJson.Append(*jsonValue);
				else
					_ParentJson[key] = *jsonValue;
				delete jsonValue;
			}

			pair = getFirstChar(_JsonString, finish + 1);
			_StartIdx = pair.second;
			if (pair.first == '}' || pair.first == ']')
				break;
		}
		return _StartIdx;
	}

	std::string Json::SerializeJson(const std::string& _FileName)
	{
		std::ifstream ifs(_FileName);
		std::string result;
		result.reserve(200);
		std::string str;
		while (std::getline(ifs, str, '\n'))
		{
			size_t i = str.find("//");
			if (i < str.size())
				continue;
			result += str;
		}
		ifs.close();
		return result;
	}

	void Json::SaveToJson(const JsonValue& _JsonValue, const std::string& _FileName)
	{
		std::ofstream ofs(_FileName);
		const std::string& jsonFormatString = _JsonValue.Stringfy();
		ofs << jsonFormatString;
		ofs.close();
	}

}