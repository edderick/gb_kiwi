GB_Kiwi
=======

A Nintendo Gameboy Emulator, written in C++.

How to Build
------------

This project uses CMake to handle the build process. Use the following commands in a terminal:

mkdir build & cd build
cmake -G "Unix Makefiles" ../
make 
make install 
cd ..

This will create the binary file bin/GB_Kiwi

Dependencies
------------

This project depends on SDL2. 

Testing
-------

To run the unit tests google test must be installed, and available in the build
paths.

To run the tests 

cd test 
make test 
