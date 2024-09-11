package main

import (
	"fmt"
	"time"
)

func main() {
	// Using interface{} as a substitute for std::any
	var anyValue interface{} = 42

	// Using bool
	var boolValue bool = true

	// Using int, int8, int16, int32, int64
	var intValue int = 42
	var i8Value int8 = 8
	var i16Value int16 = 16
	var i32Value int32 = 32
	var i64Value int64 = 64

	// Using rune (similar to char32_t in C++)
	var c32Value rune = 'A' // Unicode code point

	// Using byte (similar to char8_t in C++)
	var c8Value byte = 'B' // ASCII

	// Using float32, float64
	var floatValue float32 = 3.14
	var doubleValue float64 = 3.14

	// Using string
	var stringValue string = "Hello, world!"

	// Using slices (similar to std::vector<Any> in C++)
	sliceValue := []interface{}{1, 2, 3, "hello", true}

	// Using maps (similar to std::map<Any, Any> in C++)
	mapValue := map[interface{}]interface{}{
		"key1": 1,
		"key2": "value",
		3:      "number",
	}

	// Display some values
	fmt.Println("Any:", anyValue)
	fmt.Println("Bool:", boolValue)
	fmt.Println("Int:", intValue)
	fmt.Println("i8:", i8Value)
	fmt.Println("i16:", i16Value)
	fmt.Println("i32:", i32Value)
	fmt.Println("i64:", i64Value)
	fmt.Println("c32:", string(c32Value)) // Convert rune to string
	fmt.Println("c8:", string(c8Value))   // Convert byte to string
	fmt.Println("Float:", floatValue)
	fmt.Println("Double:", doubleValue)
	fmt.Println("String:", stringValue)

	fmt.Println("Slice:")
	for _, v := range sliceValue {
		fmt.Println(v)
	}

	fmt.Println("Map:")
	for k, v := range mapValue {
		fmt.Printf("%v: %v\n", k, v)
	}

	// Time in Go
	now := time.Now()
	fmt.Println("Current time:", now)
}

