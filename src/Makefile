main:main.o wol.o
	g++ -o wol -lstdc++ main.o wol.o 
main.o:main.cpp
	g++ -c main.cpp
wol.o:wol.cpp
	g++ -c wol.cpp

.PHONY:clean
clean:
	rm -f *.o