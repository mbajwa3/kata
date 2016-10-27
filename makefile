

all: libkata test
	
libkata:
	@if [ ! -d "./lib" ];then	\
		mkdir lib;	\
	fi
	
	@if [ ! -d "./bld" ];then	\
		mkdir bld;	\
	fi
	
	make -f src/makefile libkata
		
test: libkata
	@if [ ! -d "./bin" ];then	\
		mkdir bin;	\
	fi	
	make -f tst/makefile test

runtest:test
	bin/tst.exe tst/testcases.csv

clean:
	make -f src/makefile clean
	make -f tst/makefile clean