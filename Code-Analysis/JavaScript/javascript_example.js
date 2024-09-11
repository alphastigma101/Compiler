// Mimicking the provided C++ types in JavaScript

// Undefined
let undefinedValue = undefined;

// Null
let nullValue = null;

// Bool
let boolValue = true;

// Int
let intValue = 42;

// Double
let doubleValue = 3.14;

// Float (JavaScript has only one type for floating-point numbers, but we can simulate float precision)
let floatValue = 3.14; // All numbers are treated as doubles in JavaScript

// String
let stringValue = "Hello, world!";

// Array
let arrayValue = [intValue, floatValue, stringValue, boolValue];

// Map
let mapValue = new Map();
mapValue.set("number", intValue);
mapValue.set("text", stringValue);

// Set
let setValue = new Set([intValue, floatValue, stringValue]);

// WeakMap
let weakMapValue = new WeakMap();
let key = {};
weakMapValue.set(key, "value associated with key");

// WeakSet
let weakSetValue = new WeakSet();
weakSetValue.add(key);

// Date
let dateValue = new Date();

// RegExp
let regexValue = new RegExp("\\d+");

// Promise
let promiseValue = new Promise((resolve, reject) => {
    resolve("Promise resolved!");
});

// Function
let functionValue = function() {
    console.log("This is a function!");
};

// Usage examples
console.log("Undefined:", undefinedValue);
console.log("Null:", nullValue);
console.log("Bool:", boolValue);
console.log("Int:", intValue);
console.log("Double:", doubleValue);
console.log("Float:", floatValue);
console.log("String:", stringValue);
console.log("Array:", arrayValue);
console.log("Map:", mapValue);
console.log("Set:", setValue);
console.log("WeakMap:", weakMapValue.get(key));
console.log("WeakSet:", weakSetValue.has(key));
console.log("Date:", dateValue);
console.log("RegExp:", regexValue.test("123"));
functionValue();
promiseValue.then(result => console.log(result));

