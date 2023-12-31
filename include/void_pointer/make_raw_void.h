#pragma once

#include <managed_pointer/managed_ptr.h>

#include "void_ptr_raw.h"

namespace VoidPointers {
    template <typename T, typename... Args>
    inline void_ptr_raw make_raw_void(Args&&... args) {
        auto* ptr = new T(std::forward<Args>(args)...);
        return new ManagedPointer::managed_ptr<T>(ptr);
    }
}
