#pragma once

#include <memory>

#include "IVoidPointer.h"

namespace VoidPointers {

    using VoidPointer = std::unique_ptr<IVoidPointer>;
}
