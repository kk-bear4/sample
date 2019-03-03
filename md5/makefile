hash_test.exe: hash_test.obj hash_md5.obj makefile
	cl hash_test.obj hash_md5.obj


hash_md5.obj: hash_md5.cpp hash_md5.h makefile
	cl /c hash_md5.cpp


hash_test.obj: hash_test.cpp makefile
	cl /c hash_test.cpp


.PHONY: clean
clean:
	rm -f *.obj
	rm -f *.exe

