objects = main.o geometry.o readfile.o transform.o
cc = g++ -std=c++11 -Wall

all : $(objects)
	$(cc) -o raytracer $(objects)
main.o : src/main.cpp
	$(cc) -c src/main.cpp
geometry.o : src/geometry.cpp
	$(cc) -c src/geometry.cpp
readfile.o : src/readfile.cpp
	$(cc) -c src/readfile.cpp
transform.o : src/transform.cpp
	$(cc) -c src/transform.cpp

clean :
	rm raytracer $(objects)
