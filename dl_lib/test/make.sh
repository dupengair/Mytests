#!/bin/sh



make_so()
{
	local obj=$1
	local src=$2
	gcc -shared -fPIC -o $obj $src
}


file_lib=test_libexosip
file_mod1=test_plugin
file_mod2=test_sipmodule
file_fmw=framework

current_path=$(pwd)


for CMD in "$@"
do
	case $CMD in
		dl)
			make_so lib${file_lib}.so ${file_lib}.c
			make_so lib${file_mod1}.so ${file_mod1}.c -L./ -l$file_lib
			make_so lib${file_mod2}.so ${file_mod2}.c -L./ -l$file_lib
			gcc -DUSE_DL -o   $file_fmw ${file_fmw}.c -ldl 
			break
			;;
		whole)			
			gcc -o   $file_fmw ${file_fmw}.c ${file_mod1}.c ${file_mod2}.c ${file_lib}.c
			break
			;;
		clean)
			rm -f *.so *.o $file_fmw
			break
			;;	
		run)			
			./$file_fmw
			break
			;;	
		env)			
			export LD_LIBRARY_PATH=$current_path
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

