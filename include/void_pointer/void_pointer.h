#pragma once

#include "VoidPointer.h"
#include "VoidPointerBase.h"

namespace VoidPointers {

    template <typename T>
    VoidPointer make_void_pointer(T* pointer) {
        return VoidPointer(new VoidPointerBase<T>(pointer));
    }
}
