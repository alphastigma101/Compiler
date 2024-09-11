#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <array>
#include <deque>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <tuple>
#include <memory>
#include <cstdint> // for int8_t, int16_t, etc.
#include <cwchar>  // for wchar_t

int main() {
    // Using std::any
    std::any anyValue = 42;

    // Using void
    void* voidPtr = nullptr; // Void pointer

    // Using class and struct
    struct MyStruct {
        int a;
        double b;
    };
    MyStruct myStruct = {10, 20.5};

    class MyClass {
    public:
        int x;
        double y;
    };
    MyClass myClass = {10, 20.5};

    // Using union
    union MyUnion {
        int intVal;
        float floatVal;
    };
    MyUnion myUnion;
    myUnion.intVal = 42;

    // Using nullptr
    std::nullptr_t nullValue = nullptr;

    // Using bool
    bool boolValue = true;

    // Using char, int, int8_t, int16_t, int32_t, int64_t, char32_t, char16_t, char8_t
    char charValue = 'A';
    int intValue = 42;
    int8_t i8Value = 8;
    int16_t i16Value = 16;
    int32_t i32Value = 32;
    int64_t i64Value = 64;
    char32_t c32Value = U'A'; // UTF-32
    char16_t c16Value = u'B'; // UTF-16
    char c8Value = 'C'; // ASCII/UTF-8
    long longValue = 1234567890L;
    float floatValue = 3.14f;
    double doubleValue = 3.14;
    std::string stringValue = "Hello, world!";
    wchar_t wcharValue = L'W';
    short shortValue = 123;
    std::size_t sizeValue = 100;
    unsigned unsignedValue = 42;
    signed signedValue = -42;

    // Using std::vector, std::map, std::array, std::deque, std::set, std::unordered_map, std::unordered_set, std::queue, std::stack, std::pair, std::tuple, std::unique_ptr, std::shared_ptr, std::weak_ptr
    std::vector<int> vectorValue = {1, 2, 3};
    std::map<std::string, int> mapValue = {{"key1", 1}, {"key2", 2}};
    std::array<int, 5> arrayValue = {1, 2, 3, 4, 5};
    std::deque<int> dequeValue = {1, 2, 3};
    std::set<int> setValue = {1, 2, 3};
    std::unordered_map<std::string, int> unorderedMapValue = {{"key1", 1}, {"key2", 2}};
    std::unordered_set<int> unorderedSetValue = {1, 2, 3};
    std::queue<int> queueValue;
    queueValue.push(1);
    queueValue.push(2);
    std::stack<int> stackValue;
    stackValue.push(1);
    stackValue.push(2);
    std::pair<int, std::string> pairValue = {1, "example"};
    std::tuple<int, double, std::string> tupleValue = {1, 3.14, "example"};
    std::unique_ptr<int> uniquePtrValue = std::make_unique<int>(10);
    std::shared_ptr<int> sharedPtrValue = std::make_shared<int>(20);
    std::weak_ptr<int> weakPtrValue = sharedPtrValue;

    // Display some values
    std::cout << "Any: " << std::any_cast<int>(anyValue) << std::endl;
    std::cout << "Bool: " << boolValue << std::endl;
    std::cout << "Char: " << charValue << std::endl;
    std::cout << "Int: " << intValue << std::endl;
    std::cout << "i8: " << static_cast<int>(i8Value) << std::endl;
    std::cout << "i16: " << i16Value << std::endl;
    std::cout << "i32: " << i32Value << std::endl;
    std::cout << "i64: " << i64Value << std::endl;
    std::cout << "c32: " << c32Value << std::endl;
    std::cout << "c16: " << c16Value << std::endl;
    std::cout << "c8: " << c8Value << std::endl;
    std::cout << "Long: " << longValue << std::endl;
    std::cout << "Float: " << floatValue << std::endl;
    std::cout << "Double: " << doubleValue << std::endl;
    std::cout << "String: " << stringValue << std::endl;
    std::cout << "wChar: " << wcharValue << std::endl;
    std::cout << "Short: " << shortValue << std::endl;
    std::cout << "SizeT: " << sizeValue << std::endl;
    std::cout << "Unsigned: " << unsignedValue << std::endl;
    std::cout << "Signed: " << signedValue << std::endl;

    std::cout << "Vector: ";
    for (const auto& val : vectorValue) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    std::cout << "Map: ";
    for (const auto& [key, val] : mapValue) {
        std::cout << "{" << key << ": " << val << "} ";
    }
    std::cout << std::endl;

    std::cout << "Array: ";
    for (const auto& val : arrayValue) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    std::cout << "Deque: ";
    for (const auto& val : dequeValue) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    std::cout << "Set: ";
    for (const auto& val : setValue) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    std::cout << "UnorderedMap: ";
    for (const auto& [key, val] : unorderedMapValue) {
        std::cout << "{" << key << ": " << val << "} ";
    }
    std::cout << std::endl;

    std::cout << "UnorderedSet: ";
    for (const auto& val : unorderedSetValue) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    std::cout << "Queue: ";
    while (!queueValue.empty()) {
        std::cout << queueValue.front() << " ";
        queueValue.pop();
    }
    std::cout << std::endl;

    std::cout << "Stack: ";
    while (!stackValue.empty()) {
        std::cout << stackValue.top() << " ";
        stackValue.pop();
    }
    std::cout << std::endl;

    std::cout << "Pair: {" << pairValue.first << ", " << pairValue.second << "}" << std::endl;
    std::cout << "Tuple: (" << std::get<0>(tupleValue) << ", " << std::get<1>(tupleValue) << ", " << std::get<2>(tupleValue) << ")" << std::endl;

    std::cout << "UniquePtr: " << *uniquePtrValue << std::endl;
    std::cout << "SharedPtr: " << *sharedPtrValue << std::endl;
    std::cout << "WeakPtr (expired? " << weakPtrValue.expired() << ")" << std::endl;

    return 0;
}

