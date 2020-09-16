#ifndef JSONTEST_JSONCONVERT_H
#define JSONTEST_JSONCONVERT_H

#include "JsonParser.h"
#include "JsonArray.h"
#include "JsonObject.h"
#include <stack>

namespace Json {

    class JsonConvert {
    public:
        JsonConvert() = delete;

        JsonConvert(const JsonConvert &) = delete;

        JsonConvert(JsonConvert &&) = delete;

        JsonConvert &operator=(const JsonConvert &) = delete;

        JsonConvert &operator=(JsonConvert &&) = delete;

        explicit JsonConvert(const JsonParser &jsonParser, bool format = false, int indent = 4, bool escape = false)
                : __format(format), __indent(indent), __ptr(0) {
            jsonParser.__escape = escape;
            if (!jsonParser.__parser) const_cast<JsonParser &>(jsonParser).parseJsonDocument();
            __lstJsonValue = jsonParser.jsonValue;
            __len = __lstJsonValue.size();
        }

        explicit JsonConvert(const std::string &jsonText, bool format = false, int indent = 4, bool escape = false)
                : JsonConvert(JsonParser(jsonText), format, indent, escape) {}

        explicit JsonConvert(std::ifstream &ifs, bool format = false, int indent = 4, bool escape = false)
                : JsonConvert(JsonParser(ifs), format, indent, escape) {}

        explicit JsonConvert(FILE *fp, bool format = false, int indent = 4, bool escape = false)
                : JsonConvert(JsonParser(fp), format, indent, escape) {}

        JsonValue *convertJson();

    protected:
        void convertObject(JsonObject *jsonObject, const std::string &value);

        void convertArray(JsonArray *jsonArray, const std::string &value);

        void __remove_quotation(std::string &v) {
            if (v.size() < 2) return;
            v.pop_back();
            v.erase(v.begin(), v.begin() + 1);
        }

        bool __isNumber(const std::string &number) {
            for (int i = 0; i < number.size(); ++i)
                if (!(JsonParser::is_number(number[i]) || number[i] == '.'))
                    return false;
            return true;
        }

    private:
        std::vector<std::string> __lstJsonValue;
        JsonValue *jsonValue= nullptr;
        bool __format;
        int __ptr, __len, __indent;
    };
}
#endif
