#pragma once

#include "void_pointer/void_pointer.h"

typedef VoidPointers::VoidPointer  VoidPointer;
typedef VoidPointers::IVoidPointer IVoidPointer;

#define void_pointer(...) VoidPointers::unique_void_pointer(__VA_ARGS__)
#define new_void_pointer(...) VoidPointers::new_void_pointer(__VA_ARGS__)
