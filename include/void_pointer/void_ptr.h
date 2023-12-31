#pragma once

#include <managed_pointer/untyped_managed_ptr_impl.h>

#include <memory>

namespace VoidPointers {
    using void_ptr = std::unique_ptr<ManagedPointer::untyped_managed_ptr_impl>;
}
