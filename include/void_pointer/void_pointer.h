#pragma once

#include "VoidPointer.h"
#include "VoidPointerBase.h"

namespace VoidPointers {

    template <typename T>
    IVoidPointer* new_void_pointer(T* pointer) {
        return new VoidPointerBase<T>(pointer);
    }

    template <typename T>
    VoidPointer unique_void_pointer(T* pointer) {
        return VoidPointer(new VoidPointerBase<T>(pointer));
    }
}
