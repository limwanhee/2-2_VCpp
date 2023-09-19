#include <iostream>
#include <chrono>
#include <conio.h>

using namespace std;
using namespace chrono;

int main() {
	char key;

	while (1) {
		while (true){

		}
		system_clock::time_point start_time = system_clock::now();
		char key = _getch();
		system_clock::time_point end_time = system_clock::now();


		printf("%c", key);

		if (key == 27)
			break;
	}
	
}