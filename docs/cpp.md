# CPP learnings (from hnswlib)

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

# Namespaces
- in C all global variables and functions are in one `space``
- using namespaces global variables and functions can be stored in a namespace (like a folder)
- the variables and functions can be accessed by using the scope-operator (`::`)
- example: using std::string means using the class string from the namescape `std`
- namespaces have no influence at linking / locating time
- after compilation the namespaces are completely removed, the compiler uses them internally to rename symbol-names

# References
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