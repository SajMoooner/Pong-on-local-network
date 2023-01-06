all:compile link

compile:
	g++ -Isrc/include -c .\main.cpp -pthread

link:
	g++ main.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -pthread