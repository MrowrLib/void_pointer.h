#pragma once

namespace VoidPointers {

    struct IVoidPointer {
        virtual ~IVoidPointer() = default;

        virtual void* void_pointer() const                                   = 0;
        virtual void  set_destruct_on_delete(bool destruct_on_delete = true) = 0;
        virtual void  disable_destruct_on_delete()                           = 0;
        virtual void  enable_destruct_on_delete()                            = 0;
        virtual bool  destruct_on_delete() const                             = 0;

        template <typename T>
        T* as() const {
            auto* ptr = void_pointer();
            if (!ptr) return nullptr;
            return static_cast<T*>(ptr);
        }
    };
}
