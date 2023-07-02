#pragma once

#include "void_pointer/void_pointer.h"

typedef VoidPointers::VoidPointer VoidPointer;

#define void_pointer(...) VoidPointers::make_void_pointer(__VA_ARGS__)
