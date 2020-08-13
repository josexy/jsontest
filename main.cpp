#include <iostream>
#include "json/include/Json.h"

using namespace std;

int json_write() {
    JsonObject root(true);
    root.put("string", _JS("JSON"));
    root.put("number", 1.234);
    root.put("boolean", false);
    root.put("null");

    JsonObject *object = new JsonObject;
    object->put("number2", -0.123);
    object->put("number3", -123);

    JsonArray *array = new JsonArray;
    array->put(_JS("hello world"));
    array->put(100);
    array->put();

    root.put("object", object);
    root.put("array", array);

    cout << root << endl;
    cout << root.get(5).key << endl;
    cout << root.get(5).value->value(0) << endl;
    cout << root.get(5).value->value(1) << endl;
    return 0;
}

int json_read() {
    string jsonText = R""({"menu":{"id":"file","value":null,"popup":{"menuitem":[{"value":"New","onclick":"CreateNewDoc()"},{"value":"Open","onclick":"OpenDoc()"},{"value":"Close","onclick":"CloseDoc()"}]}}})"";
    ifstream ifs;
    ifs.open("test.json");
    try {
        JsonConvert jsonConvert(jsonText, true);
        JsonObject *object = dynamic_cast<JsonObject *>(jsonConvert.convertJson());
        if (object) {
            JsonArray *array = (JsonArray*)object->value("menu")->value("popup")->value("menuitem");
            cout << object << endl;
            cout << array << endl;
            for (auto &x:*array) {
                if (x->type() == JsonValueType::Object) {
                    JsonObject *obj = (JsonObject *) x.get();
                    for (auto &y:*obj) {
                        cout << y.key << " => " << y.value << endl;
                    }
                }
            }
        }
    } catch (JsonException &jsonException) {
        cout << jsonException.what() << endl;
    }
    ifs.close();
    return 0;
}

int main() {
    json_write();

    cout<<endl;
    
    json_read();
    
    return 0;
}
