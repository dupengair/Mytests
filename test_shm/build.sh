#! /bin/sh

build()
{
rm -f prc? test_shm.txt
gcc -DTEST_SHM_1 -o prc1 prc1.c &&
gcc -DTEST_SHM_2 -o prc2 prc1.c &&
gcc -DTEST_SHM_3 -o prc3 prc1.c
}

clean()
{
rm -f prc? test_shm.txt
}

kill()
{
killall prc1 prc2 prc3
}

run()
{
	./prc1 & 
	sleep 1
	./prc2 &
	./prc3 &
}

for CMD in "$@"
do
	case $CMD in
		-b)
			echo "[compile]"
			build
			ls
			;;
		-c)
			echo "[clean]"
			clean
			ls
			;;
		-k)
			echo "[kill]"
			kill
			;;		
		-r)
			echo "[run all]"
			run
			;;	
		-1)
			echo "[run prc1]"
			./prc1 &
			;;	
		-2)
			echo "[run prc2]"
			./prc2 &
			;;
		-3)
			echo "[run prc3]"
			./prc3 &
			;;	
		*)
			echo "args error : $CMD"
			break
			;;
	esac
done

exit 0