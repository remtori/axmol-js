# JavaScript Bindings Generator for Axmol

This directory contains the updated JavaScript bindings generator templates that use **v8pp** instead of the previous Lua-based system.

## Overview

The bindings generator creates JavaScript bindings for Axmol's C++ classes using the v8pp library, which provides a modern C++ wrapper around Google's V8 JavaScript engine.

## Key Features

- **Type Safety**: v8pp provides compile-time type checking and automatic conversions
- **Exception Handling**: C++ exceptions are automatically caught and converted to JavaScript errors
- **Memory Management**: Automatic lifetime management for wrapped objects with reference counting support
- **Performance**: Direct V8 integration without intermediate conversion layers

## Architecture

### Templates

- `layout_head.c/h` - File headers and includes
- `layout_foot.c` - Module registration function
- `ifunction.c` - Instance method wrappers
- `sfunction.c` - Static method wrappers
- `register.c` - Class registration with v8pp::class_

### Type Conversions

The system supports two types of conversions:

#### 1. Direct Conversions (v8pp::convert specializations)
For simple value types like `Vec2`, `Color4B`, etc.:
```cpp
// Automatically converted to/from JavaScript objects
Vec2 pos = {10, 20}; // C++
var pos = {x: 10, y: 20}; // JavaScript
```

#### 2. Wrapped Classes (v8pp::class_)
For complex objects with reference counting:
```cpp
// Wrapped as JavaScript objects with proper lifetime management
auto node = new Node(); // C++
var node = new ax.Node(); // JavaScript
```

### Exception Safety

All generated bindings include exception handling:
- C++ exceptions are caught and converted to JavaScript errors
- Invalid arguments throw TypeError exceptions
- Null pointer access is prevented
- Stack traces are preserved

## Manual Integration

The `/manual` directory contains:
- `JSConversions.h/cpp` - Type conversion implementations
- `JSEngine.h/cpp` - V8 engine wrapper and integration

## Usage Example

```cpp
// Register bindings in your application
auto* engine = JSEngine::getInstance();
v8::Isolate* isolate = engine->getIsolate();
v8::Local<v8::Object> global = engine->getGlobalObject();

// Register all generated bindings
ax::jsb::register_all_ax(isolate, global);

// Now JavaScript can use Axmol classes
engine->executeString(R"(
    var node = new ax.Node();
    node.setPosition({x: 100, y: 200});
    var pos = node.getPosition();
    console.log('Position:', pos.x, pos.y);
)");
```

## Configuration

The `conversions.yaml` file defines how C++ types map to JavaScript:
- Primitive types use built-in v8pp conversions
- Axmol types use custom converter specializations
- Object types use v8pp::class_ wrapping

## Error Handling

The bindings are designed to be crash-safe:
- All JavaScript calls are wrapped in try-catch blocks
- Invalid operations throw JavaScript exceptions instead of crashing
- Memory management is handled automatically
- Debug logging provides detailed error information

## Extending the System

To add support for new types:

1. **Value Types**: Add v8pp::convert specialization in JSConversions.h/cpp
2. **Classes**: The generator will automatically create v8pp::class_ bindings
3. **Containers**: Use existing std::vector/std::map conversions

Example custom conversion:
```cpp
template<>
struct v8pp::convert<MyType> {
    using from_type = MyType;
    using to_type = v8::Local<v8::Object>;

    static bool is_valid(v8::Isolate*, v8::Local<v8::Value> value);
    static from_type from_v8(v8::Isolate*, v8::Local<v8::Value> value);
    static to_type to_v8(v8::Isolate*, MyType const& value);
};

template<>
struct v8pp::is_wrapped_class<MyType> : std::false_type {};
```