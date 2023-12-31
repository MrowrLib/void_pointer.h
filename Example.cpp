#include <void_pointer.h>

#include <iostream>
#include <string>
#include <vector>

class Dog {
    std::string _name;

public:
    Dog(std::string name) : _name(std::move(name)) {
        std::cout << "Dog " << _name << " created" << std::endl;
    }
    ~Dog() { std::cout << "Dog " << _name << " destroyed" << std::endl; }
    std::string name() const { return _name; }
};

class CollectionOfPointers {
    std::vector<void_ptr> pointers;

public:
    void add(void_ptr ptr) { pointers.emplace_back(std::move(ptr)); }
    void clear() { pointers.clear(); }
};

void print(const std::string& text) { std::cout << text << std::endl; }

int main() {
    auto dontDeleteMe = make_void<Dog>("Spot");
    dontDeleteMe->disable_delete();

    auto dog    = new Dog("Rex");
    auto dogPtr = make_void_ptr(dog);
    print("Created void_ptr with dog named " + dogPtr->as<Dog*>()->name());

    print("Creating collection...");
    auto* collection = new CollectionOfPointers;
    collection->add(make_void<Dog>("Fido"));
    collection->add(make_void<Dog>("Rover"));
    collection->add(std::move(dontDeleteMe));

    print("Deleting collection...");
    delete collection;
    print("Collection deleted");

    void_ptr_raw rawPtr = make_raw_void<Dog>("Snoopy");
    print("Created raw void_ptr with dog named " + rawPtr->as<Dog*>()->name());

    void_ptr_raw rawPtr2 = make_raw_void_ptr<Dog>(new Dog("Lassie"));
    print("Created raw void_ptr with dog named " + rawPtr2->as<Dog*>()->name());
}