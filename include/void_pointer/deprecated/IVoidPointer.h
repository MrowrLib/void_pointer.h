#pragma once

#include <type_traits>

namespace VoidPointers {

    struct IVoidPointer {
        virtual ~IVoidPointer() = default;

        struct IVoidPointerDeleteRule {
            virtual void set_destruct_on_delete(bool destruct_on_delete = true) = 0;
            virtual void disable_destruct_on_delete()                           = 0;
            virtual void enable_destruct_on_delete()                            = 0;
            virtual bool destruct_on_delete() const                             = 0;
        };

        virtual void* void_ptr() const = 0;

        virtual IVoidPointerDeleteRule* delete_rule() = 0;

        template <typename T, typename std::enable_if<std::is_pointer<T>::value, int>::type = 0>
        T as() const {
            auto* ptr = void_ptr();
            if (!ptr) return nullptr;
            return static_cast<T>(ptr);
        }

        template <typename T, typename std::enable_if<!std::is_pointer<T>::value, int>::type = 0>
        T as() const {
            auto* ptr = void_ptr();
            if (!ptr) return {};
            return *static_cast<T*>(ptr);
        }
    };
}
