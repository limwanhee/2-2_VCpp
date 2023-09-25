#include <iostream>
#include <chrono>
#include <conio.h>
#define SIZE 5

using namespace std;
using namespace chrono;


int main() {
	char key [SIZE];
	int i = 0;

    if (_kbhit()) {        //키보드 입력 확인 (true / false)
		system_clock::time_point start = system_clock::now(); // 입력하면 시간 측정 시작
		for (i = 0; i < SIZE; i++) {
			key[i] = _getch();      // 방향키 입력시 224 00이 들어오게 되기에 앞에 있는 값 224를 없앰
			if (key[i] == -32) {    // -32로 입력되면
				key[i] = _getch();  // 새로 입력값을 판별하여 상하좌우 출력
			}
	
			duration<double>sec = system_clock::now() - start; //입력하면 시간 측정 끝

			if(key[i] == 27 || key[i] == '\r' || sec.count() > 0.3 || i == 4) { //esc 눌렀을때, 엔터키 눌렀을때, 입력 시간이 0.3초 지났을때, 입력이 5개 입력 됐을때 종료
					break; 
			}
		}

		if (key[0] == 80 && key[1] == 77 && key[2] == 'a') { // 아래, 오른쪽, a
			printf("아도겐! =o");
		}
		else if (key[0] == 77 && key[1] == 80 && key[2] == 77) { //오른쪽, 아래, 오른쪽
			printf("승룡권!");
		}
		else if (key[0] == 80 && key[1] == 1 && key[2] == 75 && key[4] == 'k') { //아래, 왼하단(1번키), 왼쪽, k
			printf("용권선풍각!");
		}
		else {
			printf("잘못된 커맨드를 입력했습니다");
		}
		/*
			
		2번째 입력하고 0.3초가 지나도 다음 입력을 기다리고 입력이 되는 문제
		커맨드를 여러번 할 수 없는 문제
		("asdf↓→a" 처럼 이상한 단어가 섞여있으면 인식시킬것") 이 조건을 만족하지 못한 문제가 있습니다

		*/
	}

}
