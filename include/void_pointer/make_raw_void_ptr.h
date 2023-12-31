#pragma once

#include <managed_pointer/managed_ptr.h>

#include "void_ptr_raw.h"

namespace VoidPointers {
    template <typename T>
    inline void_ptr_raw make_raw_void_ptr(T* ptr, bool deletes_pointer = true) {
        return new ManagedPointer::managed_ptr<T>(ptr, deletes_pointer);
    }
}
