# jsontest
This is just a simple C++ JSON parser

# sample
```cpp
#include <iostream>
#include "json/include/Json.h"

using namespace Json;
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
    ifs.open("test_array.json");
//    ifs.open("test_object.json");
    if(!ifs.is_open()) {
        cout<<"Not open\n";
        return -1;
    }
    try {
        JsonConvert jsonConvert(ifs,true);
        JsonValue *value=jsonConvert.convertJson();

        JsonArray *array = nullptr;
        JsonObject *object = nullptr;

        if(value->type()==JsonValueType::Array)
            array=dynamic_cast<JsonArray *>(value);
        else if(value->type()==JsonValueType::Object)
            object=dynamic_cast<JsonObject *>(value);

        if (object) {
            array=(JsonArray*)object->value("menu")->value("popup")->value("menuitem");
            for (auto &x:*array) {
                if (x->type() == JsonValueType::Object) {
                    JsonObject *obj = (JsonObject *) x.get();
                    for (auto &y:*obj) {
                        cout << y.key << " => " << y.value << endl;
                    }
                }
            }
        }else if(array){
            cout<<array<<endl;
            for (auto x=array->begin();x!=array->end();x++){
                cout<<x->get()->value("email")->data().data1<<endl;
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

```

