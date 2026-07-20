
# Variables
vector_dimension = 1024 # will set the makro VEC_DIM when compiling

# Parameters
DEBUG = 1

all: build_main
	./run_bit_vec_db

CFLAGS = -std=c++17 -DVEC_DIM=$(vector_dimension)

ifeq ($(DEBUG),1)
	CFLAGS += -DDEBUG_MODE=1
endif

# Build Files 
FILES = ./src/main.cpp
FILES += ./src/lin_alg/bit_vec.cpp
FILES += ./src/vector_store.cpp

# Additional test-Files
FILES += ./src/tests/test_bit_vector_transform.cpp

build_main: ./src/main.cpp
	@echo "building with Flags $(CFLAGS)"
	@g++ $(FILES) $(CFLAGS) -o run_bit_vec_db
