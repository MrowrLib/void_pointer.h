#pragma once

#include <memory>

#include "IVoidPointer.h"
#include "VoidPointerDeleter.h"

namespace VoidPointers {

    template <typename T>
    class VoidPointerBase : public IVoidPointer {
        std::unique_ptr<void, VoidPointerDeleter<T>> _pointer;

        VoidPointerBase(const VoidPointerBase&)            = delete;
        VoidPointerBase& operator=(const VoidPointerBase&) = delete;

    public:
        VoidPointerBase(T* pointer) : _pointer(pointer) {}
        ~VoidPointerBase() override = default;

        void* pointer() const override { return _pointer.get(); }
        void  set_destruct_on_delete(bool destruct_on_delete) override {
            _pointer.get_deleter().set_deletes_pointer(destruct_on_delete);
        }
        void disable_destruct_on_delete() override { set_destruct_on_delete(false); }
        void enable_destruct_on_delete() override { set_destruct_on_delete(true); }
        bool destruct_on_delete() const override {
            return _pointer.get_deleter().deletes_pointer();
        }
    };
}
