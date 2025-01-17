# Generic Linked List Library
This is a simple and reusable C library that implements a generic linked list. 
It includes functions to manipulate linked list data structures and is built with `Make`. 
Unit tests are written using the `Check` testing framework.

## Installation

Install with these commands.

```bash
make build_dir
make
sudo make install
```

## Usage
```c
#include "linked_list.h"

linked_list_t list = ll_create_linked_list();

// data can be any type
ll_add_head(list, &data, sizeof(data));

/*
    All the details about the functions those manipulate data in list can be found in linked_list.h
*/

ll_delete_list(list);

```

### Testing

Tests are made with a unit test framework called [`Check`](https://libcheck.github.io/check/)
create test program with

installation instruction can be found [here](https://libcheck.github.io/check/web/install.html)

build the test with
```bash
make test
```

then run the test with
```bash
make run
```

You can run test program with
```bash
./bin/test/test
```

### Memory Leak Checks

You can check the memory leaks with
```bash
make mem_check
```

### Cleaning 

You can clean all the outputs of building by
```bash
make clean
```

## Notes
This is project for applying a technique called learn-by-doing.

My aim was to learn concepts by creating a library.

The concepts which i learned by making this projects can be listed as:

- GNU Make & Makefiles
- GDB
- Valgrind
- Markdown Files(Like this one)
- Git & GitHub
- Documenting
  
## Contributing

The best contribution to this project will be criticizing it and giving feedback to me.
Please let me know about what can be added to this project and my learning path. 
Feel free to use or copy or do whatever you want ofc.

## License

This project is licensed under the [MIT License](./LICENSE).

### Third-party Licenses

The unit tests for this project make use of the `check.h` library, which is licensed under the [LGPL 2.1 or later](https://www.gnu.org/licenses/old-licenses/lgpl-2.1.html). This applies only to the testing code and does not affect the licensing of the library itself.
