all:compile link

compile:
	g++ -Isrc/include -c .\main.cpp .\Paddle.cpp .\Ball.cpp -pthread

link:
	g++ main.o paddle.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -pthread