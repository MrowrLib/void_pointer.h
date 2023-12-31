#pragma once

#include <memory>

#include "IVoidPointer.h"
#include "VoidPointerDeleter.h"

namespace VoidPointers {

    template <typename T>
    class VoidPointer : public IVoidPointer {
    public:
        class VoidPointerDeleteRule : public IVoidPointer::IVoidPointerDeleteRule {
            std::unique_ptr<void, VoidPointerDeleter<T>>* _pointer = nullptr;

        public:
            void set_pointer(std::unique_ptr<void, VoidPointerDeleter<T>>* pointer) {
                _pointer = pointer;
            }
            void set_destruct_on_delete(bool destruct_on_delete = true) override {
                if (_pointer != nullptr)
                    _pointer->get_deleter().set_deletes_pointer(destruct_on_delete);
            }
            void disable_destruct_on_delete() override { set_destruct_on_delete(false); }
            void enable_destruct_on_delete() override { set_destruct_on_delete(true); }
            bool destruct_on_delete() const override {
                if (_pointer != nullptr) return _pointer->get_deleter().get_deletes_pointer();
                else return false;
            }
        };

    private:
        std::unique_ptr<void, VoidPointerDeleter<T>> _pointer;
        VoidPointerDeleteRule                        _delete_rule;

        VoidPointer(const VoidPointer&)            = delete;
        VoidPointer& operator=(const VoidPointer&) = delete;

    public:
        VoidPointer(T* pointer) : _pointer(pointer) {}
        ~VoidPointer() override = default;

        IVoidPointer::IVoidPointerDeleteRule* delete_rule() override {
            _delete_rule.set_pointer(&_pointer);
            return &_delete_rule;
        }

        void* void_ptr() const override { return _pointer.get(); }
    };
}
