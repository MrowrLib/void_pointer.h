#include <_Log_.h>
#include <void_pointer.h>

#include <memory>

class DeleteMe {
    int id;

public:
    DeleteMe(int id) : id(id) {}
    ~DeleteMe() { _Log_("DeleteMe::~DeleteMe ID:{}", id); }
    int get_id() const { return id; }
};

int main() {
    // Create a void pointer from a raw pointer
    auto voidPtr = std::make_unique<VoidPointer<DeleteMe>>(new DeleteMe(1));

    _Log_("The pointer address is: 0x{:x}", reinterpret_cast<uintptr_t>(voidPtr->void_ptr()));

    _Log_("Getting type from ptr");
    auto* ptr = voidPtr->as<DeleteMe>();
    _Log_("ID:{}", ptr->get_id());

    _Log_("Deleting ptr, shouldn't delete the underlying ptr");
    voidPtr->disable_destruct_on_delete();
    voidPtr.reset();

    // Make a new one which should delete underlying (default behavior)
    _Log_("Deleting ptr, should delete the underlying ptr");
    voidPtr.reset(new VoidPointer(new DeleteMe(2)));

    // Or use a raw IVoidPointer*
    IVoidPointer* rawVoidPtr = new VoidPointer(new DeleteMe(3));

    // Let's do a normal delete of it
    delete rawVoidPtr;

    VoidPointer another(new DeleteMe(69));

    IVoidPointer* interface = &another;
    _Log_("ID: {}", interface->as<DeleteMe>()->get_id());

    IVoidPointer* newInterface = new VoidPointer(new DeleteMe(420));
    _Log_("ID: {}", newInterface->as<DeleteMe>()->get_id());
    delete newInterface;
}