# CPP Learnings from hnswlib

## Smart Pointer
- `std::unique_ptr<VisitedListPool> visited_list_pool_;`
- is initialized with nullptr
- initialize with make_unique: `visited_list_pool_ = std::make_unique<VisitedListPool>();`
- make_unique (like malloc) allocated a memory space to the variable
- the variable is an instance of the class std::unique_ptr which encapsulates a pointer and thereby is used like a C-Pointer
- attributes and methods of objects of the type std::unique_ptr can be acces using * and -> operators (exactly like pointers)
- allocated memory doesn't need to be deallocated later 
- at any time in the program only one unique_ptr can point to the reserved memory space; this variable is the owner of this memory space
  and is responsible for deallocating after leaving the scope of the variable
- the destructor of std::unique_ptr is automaticall called if the scope of the variable ends. Within the destructor the occupied memory is deallocated

## Value-Initialization (braced-init-list)
- example: `size_t ef{0}` // value is initialized with 0

## Atomic variables
- e.g. `std::atomic<size_t>` creates a variable, on which all operations are atomic (and thereby thread-safe)
- compiler uses special CPU-Instructions which guarantuee amotic operations 

## Mutex (Mutual Exclusion)
- class used to secure critical code areas which aren't atomic
- on thread can lock the mutex, other threads that also want to lock the mutex must wait until the first thread unlocks it
- example: `std::mutex global`

**Mutex-Flow**
1. thread tries to lock the mutex. If the mutex is 0 (free) it is set to locked (1)
2. if the mutex is locked, the thread is send to sleep (doesn't use any CPU Time) by the OS
3. only the mutex-owner (thread that locked the mutex) can unlock the mutex, then the OS waked the sleeping thread

In CPP a mutex can be locked with `std::lock_guard<std::mutex> lock(global);`. An instance of the lock_guard-class is created. the std::lock_guard-class is a template, therefore within <> the type of mutex must be specified. `lock` is just the variable name. `(global)` is the constructor-call. The lock_guard-instance nows which mutex to lock and locks the mutex within its constructor.

The unlock()-call is positioned by the compiler exactly at the point where the `lock`-variable stops existing. 

## std::vector<Datatype>
- dynamic array
- example: `std::vector<std::mutex>` can be used to create an array of mutexes to lock each element of an array separately instead of the whole structure

## const-Functions
- const function don't change any variable

## mutable-keyword
- a const-readonly-function wouldn't allow locking a mutex or increasing an atomic counter
- variables with the keyword mutable are mutable withing const-functions

## Throwing errors in CPP
- example: `throw std::runtime_error("Not enough memory");`
- example: `throw std::invalid_argument("Division durch Null ist verboten!");`
- throw exceptions within the catch-block
- catching an error: 
```
catch (const std::invalid_argument& e) {
  // Hier landen wir, wenn oben 'throw' aufgerufen wurde
  std::cerr << "Fehler abgefangen: " << e.what() << "\n";
}
```
- `#include <stdexcept>`contains the standard exceptions
- when an exception is thrown, CPP uses stack unwinding to destroy all objects on the stack that were created to this point

## Namespaces
- in C all global variables and functions are in one `space``
- using namespaces global variables and functions can be stored in a namespace (like a folder)
- the variables and functions can be accessed by using the scope-operator (`::`)
- example: using std::string means using the class string from the namescape `std`
- namespaces have no influence at linking / locating time
- after compilation the namespaces are completely removed, the compiler uses them internally to rename symbol-names

## References
- alias for an already existing variable
Example: 
```
int zahl = 42;
int& referenz = zahl;
referenz = 100;
```
In C one must give a pointer to a function to change an outside-variable. A reference is an alternativ.

**Rules for references**:
- no nullptr: a reference must be bound to a real variable at all times. The can't reference nothing. For this reason references are
  safer than pointers
- direct initialization: a reference must be bound to a variable instantly at creation
- once bound, a reference can't be changed to reference another variable

## Destructors
- syntax: ~ClassName()
- a constructor for a class is needed if the class uses resources that aren't automatically deallocated by the OS. For exapmle if `malloc` or `new` is used, files are opened or also when using `mmap`. 
- `mmap`: when using `mmap` in a class, in the destructor the mapping must be cleaned up using `munmap`

## CPP-Templates
- write `template <typename T>` before a class or a function
- `T` is a generic type, which is inserted later by the compiler
- when using a template, a concrete type must by passed, thereby the compiler knows which type to insert
- the declaration and implementation of templates both must be in the same header file. Reason for that is, that the compiler can't compile a generic class / function implementation without seeing how the template is instanciated. Therefore the compiler must include both the header-declaration of the template and the implementation into the file, where the template is intanciated.

## OOP
Example:
`class Dog: public Tier {
...};`


**virtual-keyword**:
- when overriding a function from from the parent class and calling it on an instance of the child class, CPP uses pointers to the
  parent class, thereby the original function from the parent class is used, this is called static bindings
- using the `virtual void function_name() {...};` keyword before a function (in the parent class) tells the compiler to look up the actual object-type at runtime and call the overridden function of the child class
- overridden functions can also be marked as with `override` e.g. `void func() override {...};`

## Values vs. Pointers vs. References vs. unique_ptr
- use values if the attribute exists as long as the object (object is logical owner)
- use Pointers for pointing to something that already exists elsewhere (not ownership)
- references are similar to pointers, but offer more safety (see above)
- a unique_ptr can have exactly one owner (only one variable can point to this memory area)
