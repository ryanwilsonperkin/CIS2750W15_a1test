CIS2750W15 A1 Test
===

A framework for testing assignment 1 of CIS2750W15 at the University of Guelph.

Testing
---

1. Clone this repository on one of the socs.uoguelph.ca servers.
2. Copy the libpm.a library and any associated header files into the root of this repository.
3. Run `make build` to compile.
4. Run `make test` to test the library.
5. Run `make clean` to cleanup.

Common Errors
---

- "No rule to make target 'ParameterManager.h', needed by 'build'. Stop.": You have not copied ParameterManager.h into the root of this repository.
- "No rule to make target 'libpm.a', needed by 'build'. Stop.": You have not copied libpm.a into the root of this repository.
