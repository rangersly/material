INCLUDE = -I/home/e0x2d/include
main: file1.o file2.o
	g++ -o $@ file1.o file2.o

file1.o: file1.cpp
	g++ -c file1.o file1.cpp 

file2.o: file2.cpp
	g++ -c file2.o file2.cpp ${INCLUDE}

clean: 
	rm *.o demo
