#! /bin/sh

#gcc -fPIC -shared -o libfunc.so  libfunc.c 
gcc  -shared -o libfunc.so  libfunc.c 
gcc -o test_so test_so.c -L./ -lfunc

#gcc -c -o libfunc.o  libfunc.c 
#ar -rcs libfunc.a libfunc.o
#gcc -o test_so test_so.c libfunc.a
