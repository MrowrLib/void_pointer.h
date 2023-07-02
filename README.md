# `#include <void_pointer.h>`

```cpp
#include <void_pointer.h>

void Example() {
    // Given a pointer to a known type...
    Something* somePointer = new Something();

    // Store it as a void*
    VoidPointer voidPointer = void_pointer(somePointer);

    // Get the void*
    void* ptr = voidPointer.void_pointer();

    // Or cast it back to a known type
    Something* thing = voidPointer.as<Something>();

    // VoidPointer is a std::unique_ptr so it will automatically
    // delete the Something* when it goes out of scope AND it
    // knows how to call the destructor of the type it was created from.
}
```

## What?

A `void*` that knows how to delete itself.

## Installation

### xmake

#### `xmake.lua`

```lua
add_repositories("MrowrLib https://github.com/MrowrLib/Packages.git")
add_requires("void_pointer")

target("Example")
    add_packages("void_pointer")
```

### vcpkg

#### `CMakeLists.txt`

```cmake
add_executable(Example main.cpp)

# Find void_pointer and link it to your target
find_package(void_pointer CONFIG REQUIRED)
target_link_libraries(Example PRIVATE void_pointer::void_pointer)
```

#### `vcpkg.json`

```json
{
    "dependencies": ["mrowr-void-pointer"]
}
```

#### `vcpkg-configuration.json`

```json
{
    "default-registry": {
        "kind": "git",
        "repository": "https://github.com/microsoft/vcpkg.git",
        "baseline": "95252eadd63118201b0d0df0b4360fa613f0de84"
    },
    "registries": [
        {
            "kind": "git",
            "repository": "https://github.com/MrowrLib/Packages.git",
            "baseline": "90c22863a5a6b0a746bb030026e851446d33fd96",
            "packages": ["mrowr-void-pointer"]
        }
    ]
}
```

> _Update the default-registry baseline to the latest commit from https://github.com/microsoft/vcpkg_  
> _Update the MrowrLib/Packages baseline to the latest commit from https://github.com/MrowrLib/Packages_

## Why?

I needed a `void*` that knew how to delete itself.

True `void*` pointers are useful for storing pointers to unknown types.

But they come with the down side that you can't call `delete` on them.

This library provides a `void*` that knows how to delete itself.

You must know the type of the pointer when you create it, but after that you can use it as a `void*`.

> _Note: I need this for scenarios when I'm working with true `void*`._  
> _If you have the option of using `std::any`, I recommend trying that instead!_

## How?

```cpp
#include <void_pointer.h>
```

```cpp
// Given a pointer to a known type...
Something* somePointer = new Something();
```

```cpp
// Store it as a VoidPointer
VoidPointer voidPointer = void_pointer(somePointer);

// This is shorthand for:
std::unique_ptr<IVoidPointer> voidPointer = VoidPointers::unique_void_pointer(somePointer);

// Because the VoidPointer is a unique_ptr, it will automatically
// delete the Something* when it goes out of scope
```

```cpp
// If you want a raw pointer instead of a std::unique_ptr
IVoidPointer* voidPointer = new_void_pointer(somePointer);

// This is shorthand for:
IVoidPointer* voidPointer = VoidPointers::new_void_pointer(somePointer).release();

// It will automatically delete the Something* when explicitly deleted:
delete voidPointer;
```

```cpp
// Get the void*
void* ptr = voidPointer.void_pointer();

// Or cast it back to a known type
Something* thing = voidPointer.as<Something>();
```

```cpp
// To disable memory management:
voidPointer->disable_destruct_on_delete();

// This will prevent the VoidPointer from calling the destructor
// of the underlying pointer.

// To re-enable it:
voidPointer->enable_destruct_on_delete();
```

## License

Use however, no attribution required.

```
BSD Zero Clause License (SPDX: 0BSD)

Permission to use, copy, modify, and/or distribute this software for any purpose
with or without fee is hereby granted.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF
THIS SOFTWARE.
```
