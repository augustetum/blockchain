hash: main.o functions.o
	g++ -std=c++17 -O3 main.o functions.o -o hash

main.o: main.cpp
	g++ -std=c++17 -O3 -c main.cpp

functions.o: functions.cpp
	g++ -std=c++17 -O3 -c functions.cpp

clean:
	del *.o *.exe

run: hash
	./hash.exe

