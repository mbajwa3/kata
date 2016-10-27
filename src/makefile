
libkata:
	@echo "Building libkata"
	gcc -c $(CURDIR)/src/romanarithmetic.c -o $(CURDIR)/bld/romanarithmetic.o
	ar  rcs $(CURDIR)/lib/libkata.a $(CURDIR)/bld/romanarithmetic.o
		
clean:
	rm -f $(CURDIR)/lib/*.a
	rm -f $(CURDIR)/bld/romanarithmetic.o