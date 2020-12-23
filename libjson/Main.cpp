
#include "libjson/JsonFormatter.h"
#include "libjson/JsonParser.h"

using namespace libjson;
using namespace std;

int test1() {
    ifstream ifs("test.json");
    // string json = R"({ "key": 1234,"arr":[[],true,false,{}] })";
    JsonParser parser(ifs);
    ifs.close();
    try {
        auto [object, arr, value] = parser.parse();
        if (value) {
            // do something
            return 0;
        }
        JsonFormatter formatter;

        if (object) {
            formatter.set_source(object.get());
            cout << object->toString() << endl;
        } else if (arr) {
            formatter.set_source(arr.get());
            cout << arr->toString() << endl;
        }
        cout << endl;
        // format json text
        string json = formatter.format();
        cout << json << endl;

    } catch (JsonError& e) {
        cout << e.what() << endl;
    }

    return 0;
}

int test2() {
    JsonObject* obj = new JsonObject();
    obj->add("name", "xxxx");
    obj->add("integer", 99);
    obj->add("float", 0.1123e4);
    obj->add("bool", false);
    obj->add("null");

    JsonArray* arr = new JsonArray();
    obj->add("array", arr);
    arr->add();
    arr->add(false);
    arr->add(true);
    arr->add(string("xx\txx\txx"));
    arr->add(new JsonArray());
    arr->add(new JsonObject());
    arr->add(11111);

    int a = 100;
    int& b = a;
    string s1 = "hello";
    const char* s2 = "world";
    JsonNumber* number = new JsonNumber(1000.123, false);
    arr->add_values(s1, ("xxxxxx"), s2, 10011.1213, a, string("1xxx"), false,
                    1.234, new JsonString("haha"), new JsonArray(),
                    new JsonObject(), make_shared<JsonString>("xxx"), number,
                    b);

    JsonArray* arr2 = new JsonArray();
    arr2->add(obj);
    cout << arr2->toString() << endl;

    JsonFormatter format{2, true};
    format.set_source(arr2);
    cout << format.format() << endl;

    return 0;
}

int main() {
    test1();
    test2();
    return 0;
}
