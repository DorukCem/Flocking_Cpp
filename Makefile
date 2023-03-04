all: compile link

compile:
	g++ -Isrc/include -c main.cpp Boids.cpp Grid.cpp vector_calculations.cpp

link:
	g++ main.o Boids.o Grid.o vector_calculations.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system
