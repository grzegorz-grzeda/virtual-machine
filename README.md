# Virtual Machine
Simple virtual machine library in C.

## Run tests
Just run `./test.sh`.

## How to compile and link it?

Just include this directory in your CMake project.

Example `CMakeLists.txt` content:
```
...

add_subdirectory(<PATH TO VIRTUAL MACHINE LIBRARY>)

target_link_libraries(${PROJECT_NAME} PRIVATE virtual_machine)

...
```

## Documentation
If you want, you can run `doxygen` to generate HTML documentation. It will be available in `documentation` 
directory.


# Copyright
This library was written by Grzegorz Grzęda, and is distributed under MIT Licence. Check the `LICENSE` file for
more details.