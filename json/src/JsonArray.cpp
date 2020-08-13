
#include "../include/JsonArray.h"
#include "../include/JsonException.h"

bool JsonArray::put(JsonValue *jsonValue) {
    if (!jsonValue) return false;
    if (find(jsonValue) != __lstJsonArray.end())return false;
    jsonValue->setEscapeChar(__escape);
    __lstJsonArray.push_back(std::shared_ptr<JsonValue>(jsonValue));
    return true;
}

bool JsonArray::put(const std::shared_ptr<JsonValue> &jsonValue) {
    if (jsonValue == nullptr)return false;
    if (find(jsonValue.get()) != __lstJsonArray.end())return false;
    jsonValue->setEscapeChar(__escape);
    __lstJsonArray.push_back(jsonValue);
    return true;
}

const JsonArray::json_array_element_t &JsonArray::get(int index) {
    if (index < 0 || index >= size())throw JsonException("Error: Invalid Index");
    return __lstJsonArray.at(index);
}

JsonArray::json_array_citerator JsonArray::find(JsonValue *jsonValue) {
    for (int i = 0; i < __lstJsonArray.size(); i++)
        if (__lstJsonArray[i].get() == jsonValue)
            return __lstJsonArray.begin() + i;
    return __lstJsonArray.end();
}

void JsonArray::__toList() {
    __lstJsonText.clear();
    __lstJsonText.push_back(_JSCS(JSON_ARRAY_BEGIN));
    int __index = 0, __size = __lstJsonArray.size();
    for (std::shared_ptr<JsonValue> jsonValue : __lstJsonArray) {
        for (auto &&p : jsonValue->toList()) __lstJsonText.push_back(p);
        __index++;
        if (__index < __size) __lstJsonText.push_back(_JSCS(JSON_SEPARATE));
    }
    __lstJsonText.push_back(_JSCS(JSON_ARRAY_END));
}

const std::vector<std::string> &JsonArray::toList() {
    __toList();
    return __lstJsonText;
}

std::string JsonArray::toString() {
    __toList();
    std::string str;
    if (!__format)
        for (auto _S : __lstJsonText) str += _S;
    else
        str = getJson(__lstJsonText);
    return str;
}






