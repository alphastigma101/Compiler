from typing import Any, Dict, List, Tuple, Set, FrozenSet

# Define Python-like types and usage

# Any: Can hold any type of value
any_value: Any = "This could be any type"

# NoneType: Represents the absence of a value
none_value: None = None

# Bool: Boolean value
bool_value: bool = True

# Int: Integer value
int_value: int = 42

# Float: Floating-point value
float_value: float = 3.14

# Double: Python does not distinguish between float and double
# but float is analogous to double in C++
double_value: float = 3.14

# String: String value
string_value: str = "Hello, world!"

# List: List of values
list_value: List[Any] = [int_value, float_value, string_value, bool_value]

# Dict: Dictionary with key-value pairs
dict_value: Dict[str, Any] = {
    "number": int_value,
    "text": string_value
}

# Tuple: Tuple of values
tuple_value: Tuple[int, float, str, bool] = (int_value, float_value, string_value, bool_value)

# Set: Set of values
set_value: Set[Any] = {int_value, float_value, string_value}

# FrozenSet: Immutable set of values
frozen_set_value: FrozenSet[Any] = frozenset({int_value, float_value, string_value})

# NoneType: Simulated as None in Python
none_type_value: NoneType = None

# Example usage
print("Any:", any_value)
print("None:", none_value)
print("Bool:", bool_value)
print("Int:", int_value)
print("Float:", float_value)
print("Double:", double_value)
print("String:", string_value)
print("List:", list_value)
print("Dict:", dict_value)
print("Tuple:", tuple_value)
print("Set:", set_value)
print("FrozenSet:", frozen_set_value)
print("NoneType:", none_type_value)

