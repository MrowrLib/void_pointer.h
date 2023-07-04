#include <_Log_.h>
#include <void_pointer.h>

class DeleteMe {
    int id;

public:
    DeleteMe(int id) : id(id) {}
    ~DeleteMe() { _Log_("DeleteMe::~DeleteMe ID:{}", id); }
    int get_id() const { return id; }
};

int main() {
    // Create a void pointer from a raw pointer
    VoidPointer voidPtr = void_pointer(new DeleteMe(1));

    _Log_("The pointer address is: 0x{:x}", reinterpret_cast<uintptr_t>(voidPtr->pointer()));

    _Log_("Getting type from ptr");
    auto* ptr = voidPtr->as<DeleteMe>();
    _Log_("ID:{}", ptr->get_id());

    _Log_("Deleting ptr, shouldn't delete the underlying ptr");
    voidPtr->disable_destruct_on_delete();
    voidPtr.reset();

    // Make a new one which should delete underlying (default behavior)
    voidPtr = void_pointer(new DeleteMe(2));

    _Log_("Deleting ptr, should delete the underlying ptr");
    voidPtr.reset();

    // Or use a raw IVoidPointer*
    IVoidPointer* rawVoidPtr = new_void_pointer(new DeleteMe(3));

    // Let's do a normal delete of it
    delete rawVoidPtr;
}