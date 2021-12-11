build:
	rm -f application.exe
	g++ -g -std=c++11 -Wall application.cpp -o application.exe
	
run:
	./application.exe

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./tests.exe


build_tests:
	rm -f tests.exe
	g++ -g -std=c++11 -Wall tests.cpp -o tests.exe -lgtest -lgtest_main -lpthread

run_tests:
	./tests.exe
