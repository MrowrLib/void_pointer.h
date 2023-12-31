#pragma once

#include <managed_pointer/managed_ptr.h>

#include "void_ptr.h"

namespace VoidPointers {
    template <typename T>
    inline void_ptr make_void_ptr(T* ptr, bool deletes_pointer = true) {
        auto* managed = new ManagedPointer::managed_ptr<T>(ptr, deletes_pointer);
        return void_ptr(managed);
    }
}
