#ifndef HELLOWORLD_JSONNULL_H
#define HELLOWORLD_JSONNULL_H

#include "JsonValue.h"

class JsonNull : public JsonValue {
public:
    explicit JsonNull() {}

    JsonValueType type() const override { return JsonValueType::Null; }

    std::string toString() override { return "null"; }

    Data data() const override { return Data{"null"}; }

    bool isNull() const override { return true; }

protected:
    using JsonValue::setData;
    using JsonValue::toList;
};

#endif //HELLOWORLD_JSONNULL_H
