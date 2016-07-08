#!/bin/sh



make_so()
{
	local obj=$1
	local src=$2
	gcc -shared -fPIC -o $obj $src 
}

make_dl()
{
	local obj=$1
	local src=$2
	gcc -shared -fPIC -DUSE_DL -o $obj $src -ldl
}


file_lib=test_lib
file_so=test_so
file_test=test
current_path=$(pwd)


for CMD in "$@"
do
	case $CMD in
		so)
			make_so lib${file_lib}.so ${file_lib}.c
			make_dl lib${file_so}.so ${file_so}.c
			make_dl lib${file_so}2.so ${file_so}2.c
			gcc -DUSE_DL -o   $file_test ${file_test}.c -ldl
			break
			;;
		cm)			
			gcc -o   $file_test ${file_test}.c ${file_so}.c ${file_so}2.c ${file_lib}.c
			break
			;;
		clean)
			rm -f *.so *.o $file_test
			break
			;;	
		run)			
			./$file_test
			break
			;;	
		env)			
			export LD_LIBRARY_PATH=$current_path:$LD_LIBRARY_PATH
			export
			break
			;;				
		*)
			echo "args error : $CMD"
			break
			;;
	esac
done

exit 0

