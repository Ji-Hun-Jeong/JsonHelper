#pragma once
#include <string>
#include <vector>
#include <map>
#include <iostream>

namespace Json
{
    enum class eJsonType
    {
        String,
        Int,
        Double,
        Boolean,
        Null,
        Object,
        Array,
    };
    enum class eBooleanType
    {
        False,
        True,
    };
    enum class eNullType
    {
        Null,
    };
    enum class eErrorType
    {
        Ok,
        Fail,
    };
    class JsonValue
    {
    public:
        JsonValue();
        JsonValue(const JsonValue& _Other);
        ~JsonValue();

    public:
        JsonValue& operator[](const std::string& _Name);
        JsonValue& operator[](size_t _Index);
        JsonValue& operator = (const std::string& _StringValue);
        JsonValue& operator = (int _IntValue);
        JsonValue& operator = (double _DoubleValue);
        JsonValue& operator = (eBooleanType _BooleanType);
        JsonValue& operator = (eNullType _Null);
        JsonValue& operator = (const JsonValue& _JsonValue);

        JsonValue& Append(const std::string& _StringValue);
        JsonValue& Append(int _IntValue);
        JsonValue& Append(double _DoubleValue);
        JsonValue& Append(eBooleanType _BooleanType);
        JsonValue& Append(eNullType _Null);
        JsonValue& Append(JsonValue& _JsonValue);

        std::string         Stringfy() const;
        std::string         AsString() const;
        std::int32_t        AsInt(eErrorType* error) const;
        double              AsDouble(eErrorType* error) const;
        bool                AsBoolean(eErrorType* error) const;
        void*               AsNull(eErrorType* error) const;
        const std::string&  GetJsonValueString() const { return JsonValueString; }

        void                SetJsonType(eJsonType _JsonType) { JsonType = _JsonType; }

    private:
        std::string stringfy(size_t _Indent, bool _IsArray) const;

    private:
        std::string                         JsonValueString;
        std::vector<JsonValue*>             VecJsonValue;
        std::map<std::string, JsonValue*>   MapJsonValue;

        eJsonType                           JsonType;
    };
}
std::ostream& operator << (std::ostream& _Os, const Json::JsonValue& _JsonValue);