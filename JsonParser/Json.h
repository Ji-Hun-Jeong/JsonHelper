#pragma once
#include "JsonValue.h"

namespace Json
{
	class Json
	{
	public:
		static class JsonValue ParseJsonByFile(const std::string& _FileName);
		static std::string SerializeJson(const std::string& _FileName);
		static void SaveToJson(const JsonValue& _JsonValue, const std::string& _FileName);

	private:
		static size_t parseJson(JsonValue& _ParentJson, const std::string& _JsonString, size_t _StartIdx, bool _IsArray);

	};
}