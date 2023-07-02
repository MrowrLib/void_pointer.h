#pragma once

namespace VoidPointers {

    template <typename T>
    class VoidPointerDeleter {
        bool _deletesPointer = true;

    public:
        void set_deletes_pointer(bool deletesPointer = true) { _deletesPointer = deletesPointer; }
        bool deletes_pointer() const { return _deletesPointer; }

        void operator()(void* ptr) const {
            if (_deletesPointer) {
                auto* castedPtr = static_cast<T*>(ptr);
                if (castedPtr) delete castedPtr;
            }
        }
    };
}
