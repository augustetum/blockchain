hash: main.o functions.o  SHA256.o
	g++ -std=c++17 -O3 main.o functions.o SHA256.o -o hash

main.o: main.cpp
	g++ -std=c++17 -O3 -c main.cpp

functions.o: functions.cpp
	g++ -std=c++17 -O3 -c functions.cpp

SHA256.o: SHA256.cpp
	g++ -std=c++17 -O3 -c SHA256.cpp

clean:
	del *.o *.exe

run: hash
	./hash.exe

