# `#include <void_pointer.h>`

```cpp
#include <void_pointer.h>

void Example() {
    // Create some void* which know how to delete themselves
    void_ptr rover   = make_void<Dog>("Rover");
    void_ptr mittens = make_void<Cat>("Mittens");

    // Their types are erased, so feel free to store
    // them together in a container
    std::vector<void_ptr> pets;
    pets.emplace_back(std::move(rover));
    pets.emplace_back(std::move(mittens));

    // Cast them back to their original type
    Dog* rover_ptr   = pets[0]->as<Dog*>();
    Cat* mittens_ptr = pets[1]->as<Cat*>();
}
```

## What?

A `void*` that knows how to delete itself.

## Table of Contents

- [`#include <void_pointer.h>`](#include-void_pointerh)
  - [What?](#what)
  - [Table of Contents](#table-of-contents)
  - [Installation](#installation)
    - [xmake](#xmake)
      - [`xmake.lua`](#xmakelua)
    - [vcpkg](#vcpkg)
      - [`CMakeLists.txt`](#cmakeliststxt)
      - [`vcpkg.json`](#vcpkgjson)
      - [`vcpkg-configuration.json`](#vcpkg-configurationjson)
  - [Why?](#why)
  - [How?](#how)
  - [Types](#types)
    - [`void_ptr`](#void_ptr)
      - [`make_void()`](#make_void)
      - [`make_void_ptr()`](#make_void_ptr)
    - [`void_ptr_raw`](#void_ptr_raw)
      - [`make_raw_void()`](#make_raw_void)
      - [`make_raw_void_ptr()`](#make_raw_void_ptr)
  - [Memory Management / Ownership](#memory-management--ownership)
  - [License](#license)


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
            "baseline": "9721c54b76c90b0e644ed914886aa6d12ead452b",
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

The latest version of `<void_pointer.h>` is is a thin wrapper around `<managed_pointer.h>`.

> **`<managed_pointer.h>`**
>
> https://github.com/MrowrLib/managed_pointer.h

The `managed_pointer` library offers a pointer which provides:

- Type-erasure
  - (_e.g. to easily store any kind of pointers in the same container_)
- Configuring the ownership of each pointer
  - (_i.e. if the pointer should `delete` its internal pointer when it is destroyed_)

## Types

### `void_ptr`

The `void_ptr` type is shorthand for:

```cpp
std::unique_ptr<ManagedPointer::untyped_managed_ptr_impl>
```

The `untyped_managed_ptr_impl` type is the untyped base class for every `managed_ptr`.

It provides the type-erasure and ownership configuration features.

> Note that it is a `unique_ptr` which means that:
>
> - It cannot be copied, it must be moved
> - It will be automatically deleted when it goes out of scope
>   - This will `delete` its internal pointer (_unless you configure it otherwise_)

#### `make_void()`

Helper for creating `void_ptr` instances.

It constructs a `new T`.

```cpp
void_ptr dog = make_void<Dog>("Rover");
```

#### `make_void_ptr()`

Helper for creating `void_ptr` instances from an existing pointer.

```cpp
void_ptr dog = make_void_ptr(new Dog("Rover"));
```

### `void_ptr_raw`

The `void_ptr_raw` type is shorthand for:

```cpp
ManagedPointer::untyped_managed_ptr_impl*;
```

The `untyped_managed_ptr_impl` type is the untyped base class for every `managed_ptr`.

The `void_ptr_raw` type is the raw pointer version of `void_ptr`.

> Note that it is a raw pointer which means that:
>
> - It can be copied
> - It will **not** be automatically deleted when it goes out of scope
> - You must explicitly `delete` it when desired
>   - This will `delete` its internal pointer (_unless you configure it otherwise_)

#### `make_raw_void()`

Helper for creating `void_ptr_raw` instances.

It constructs a `new T`.

```cpp
void_ptr_raw dog = make_raw_void<Dog>("Rover");
```

#### `make_raw_void_ptr()`

Helper for creating `void_ptr_raw` instances from an existing pointer.

```cpp
void_ptr_raw dog = make_raw_void_ptr(new Dog("Rover"));
```

## Memory Management / Ownership

For the full memory management interface, see `<managed_pointer.h>`:

- https://github.com/MrowrLib/managed_pointer.h

By default, every `void_ptr` and `void_ptr_raw` will `delete` their internal pointer when they are destroyed.

This can be disabled:

```cpp
void_ptr dog = make_void<Dog>("Rover");

// Disable automatic deletion
dog->disable_delete();
```

Here is an overview of the available functions:

```cpp
void_ptr dog = make_void<Dog>("Rover");

// Disable automatic deletion
dog->disable_delete();

// Enable automatic deletion
dog->enable_delete();

// Explicitly configure automatic deletion
dog->set_deletes_pointer(true);

// Check if automatic deletion is enabled
bool deletes_pointer = dog->deletes_pointer();
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
