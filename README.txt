CIS2750W15 A1 Test
===

A framework for testing assignment 1 of CIS2750W15 at the University of Guelph.

Testing
---

1. Clone this repository on one of the socs.uoguelph.ca servers.
2. Copy the contents of this repository into the repository to be tested.
3. Run `make` to compile the libpm.a library.
4. Run `make -f TestMake` to test the library.

Common Errors
---

- "No rule to make target 'ParameterManager.h', needed by 'build'. Stop.": ParameterManager.h is not in the same directory as TestMakefile.
- "No rule to make target 'libpm.a', needed by 'build'. Stop.": libpm.a is not in the same directory as TestMakefile.
