#pragma once

#include <managed_pointer/managed_ptr.h>

#include "void_ptr.h"

namespace VoidPointers {
    template <typename T, typename... Args>
    inline void_ptr make_void(Args&&... args) {
        auto* ptr     = new T(std::forward<Args>(args)...);
        auto* managed = new ManagedPointer::managed_ptr<T>(ptr);
        return void_ptr(managed);
    }
}
