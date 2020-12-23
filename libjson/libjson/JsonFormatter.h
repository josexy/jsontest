#ifndef LIBJSON_JSONFORMATTRT_H
#define LIBJSON_JSONFORMATTRT_H

#include <memory>

#include "JsonArray.h"
#include "JsonObject.h"

namespace libjson {
class JsonFormatter {
   public:
    explicit JsonFormatter(int indent = 4, bool escape = false)
        : __indent(indent), __escape(escape) {}

    void set_source(JsonObject* object) {
        __object = object;
        __array = nullptr;
    }
    void set_source(JsonArray* array) {
        __array = array;
        __object = nullptr;
    }

    std::string format() {
        __fmt.clear();

        if (__object) {
            if (__indent <= 0) return __object->toString();
            recursive_formatter(1, __object, false);
        } else if (__array) {
            if (__indent <= 0) return __array->toString();
            recursive_formatter(1, __array, false);
        } else
            throw JsonError("the source of JsonObject or JsonArray is null");
        return __fmt.str();
    }

   protected:
    void append_space_character(int c) {
        for (int i = 0; i < c; i++) __fmt << " ";
    }

    void recursive_formatter(int, JsonObject*, bool);
    void recursive_formatter(int, JsonArray*, bool);

   private:
    int __indent;
    bool __escape;
    JsonObject* __object;
    JsonArray* __array;
    std::stringstream __fmt;
    static constexpr char NEWLINE = '\n';
};

void JsonFormatter::recursive_formatter(int depth, JsonArray* array,
                                        bool empty) {
    __fmt << "[";
    int pos = 0;
    int size = array->__lstValue.size();
    bool once = false;
    for (auto& v : array->__lstValue) {
        if (!once) {
            __fmt << NEWLINE;
            once = true;
        }
        append_space_character(depth * __indent);
        if (v->type() == JsonType::Object) {
            recursive_formatter(depth + 1, v->toJsonObject(), v->empty());
        } else if (v->type() == JsonType::Array) {
            recursive_formatter(depth + 1, v->toJsonArray(), v->empty());
        } else {
            if (v->type() == JsonType::String)
                __fmt << ((JsonString*)(v.get()))->toString(__escape);
            else
                __fmt << v->toString();
        }
        if (pos + 1 < size) {
            __fmt << ",";
        }
        pos++;
        __fmt << NEWLINE;
    }
    // []
    if (!empty) append_space_character((depth - 1) * __indent);
    __fmt << "]";
}

void JsonFormatter::recursive_formatter(int depth, JsonObject* object,
                                        bool empty) {
    __fmt << "{";
    int pos = 0;
    int size = object->__kvObjects.size();
    bool once = false;
    for (auto& [k, v] : object->__kvObjects) {
        if (!once) {
            __fmt << NEWLINE;
            once = true;
        }
        // Add indentation when recursing to different depths
        append_space_character(depth * __indent);

        __fmt << k->toString(__escape) << ": ";
        if (v->type() == JsonType::Object) {
            // Recursive formatting Object
            recursive_formatter(depth + 1, v->toJsonObject(), v->empty());
        } else if (v->type() == JsonType::Array) {
            // Recursive formatting Array
            recursive_formatter(depth + 1, v->toJsonArray(), v->empty());
        } else {
            if (v->type() == JsonType::String)
                __fmt << ((JsonString*)(v.get()))->toString(__escape);
            else
                __fmt << v->toString();
        }
        if (pos + 1 < size) {
            __fmt << ",";
        }
        pos++;
        __fmt << NEWLINE;
    }
    // {}
    if (!empty) append_space_character((depth - 1) * __indent);
    __fmt << "}";
}
}  // namespace libjson
#endif