#include<iostream>
#include<string>
#include<Windows.h>
#include<time.h>
#include<random>
#include<vector>
#include<conio.h>
#include <fstream>
#include <cstdlib>
using namespace std;
//방향키 코드값 정의
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

class snake { // snake클레스 생성
private:
	vector<snake> v; // snake클레스로 된 벡터
	string name;
	int mapx;
	int mapy;
	int foodx;
	int foody;
	int bamx;
	int bamy;

	vector<int> posx; // x 좌표
	vector<int> posy; // y 좌표

	int length;
	int speed;
	int direction;
	int score;
public:
	snake(string name = " ", int mapx = 100, int mapy = 100, int length = 1, int speed = 1) { // 생성자
		this->name = name, this->mapx = mapx, this->mapy = mapy, this->length = length, this->speed = speed, this->foodx = 0, this->foody = 0, this->direction = RIGHT, this->bamx = mapx / 2, this->bamy = mapy / 2, this->score = 0;
	}
	void menu();

	void start();
	void setsnake();
	void gameend();
	void makemap();
	void makefood();
	void move();
	void setscore();
	void end();
	void getdirection(int &dir) { this->direction = dir; }
	void getbamx(int &x) { this->bamx = x; }
	void getbamy(int &y) { this->bamy = y; }
	friend void gotoxy(int x, int y, string s); // friend를 이용한 전역함수 사용
};

void gotoxy(int x, int y, string s) { // x,y좌표에 s를 출력  
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	cout << s;
}

void snake::setscore() { // 게임 기록을 표시하기 위한 함수
	system("cls");
	string s;

	vector<string> vscore;
	vector<string> jumsu;
	ifstream fin("Record.txt"); // 읽기 위해 Record.txt 파일 열기
	string line;
	int x = 0;
	string temp1, temp2;
	while (true) { // Record.txt 파일에서 한줄씩 vscore벡터에 입력
		getline(fin, line);
		if (fin.eof()) break;
		vscore.push_back(line);
	}
	if (vscore.size() > 1) {
		for (int i = 0; i < vscore.size(); i++) { // vscore벡터에서 숫자만 jumsu벡터로 입력
			x = vscore[i].find(" ");
			jumsu.push_back(vscore[i].substr(0, x));
		}
		for (int i = vscore.size() - 2; i >= 0; i--) {
			if (atoi(jumsu[i].c_str()) < atoi(jumsu[i + 1].c_str())) { // jumsu벡터에 string을 int로 바꿔서 크기 비교
				temp1 = jumsu[i];
				temp2 = vscore[i];
				jumsu[i] = jumsu[i + 1];
				vscore[i] = vscore[i + 1];
				jumsu[i + 1] = temp1;
				vscore[i + 1] = temp2;
			}
		}
	}

	if (vscore.size() >= 5) {
		cout << "1위. " << vscore[0].substr(vscore[0].find(" ") + 1, -1) << "  " << "점수 : " << jumsu[0] << endl;
		cout << "2위. " << vscore[1].substr(vscore[1].find(" ") + 1, -1) << "  " << "점수 : " << jumsu[1] << endl;
		cout << "3위. " << vscore[2].substr(vscore[2].find(" ") + 1, -1) << "  " << "점수 : " << jumsu[2] << endl;
		cout << "4위. " << vscore[3].substr(vscore[3].find(" ") + 1, -1) << "  " << "점수 : " << jumsu[3] << endl;
		cout << "5위. " << vscore[4].substr(vscore[4].find(" ") + 1, -1) << "  " << "점수 : " << jumsu[4] << endl;
	}
	else if (vscore.size() == 4) {
		cout << "1위. " << vscore[0].substr(vscore[0].find(" ") + 1, -1) << "  " << "점수 : " << jumsu[0] << endl;
		cout << "2위. " << vscore[1].substr(vscore[1].find(" ") + 1, -1) << "  " << "점수 : " << jumsu[1] << endl;
		cout << "3위. " << vscore[2].substr(vscore[2].find(" ") + 1, -1) << "  " << "점수 : " << jumsu[2] << endl;
		cout << "4위. " << vscore[3].substr(vscore[3].find(" ") + 1, -1) << "  " << "점수 : " << jumsu[3] << endl;
	}
	else if (vscore.size() == 3) {
		cout << "1위. " << vscore[0].substr(vscore[0].find(" ") + 1, -1) << "  " << "점수 : " << jumsu[0] << endl;
		cout << "2위. " << vscore[1].substr(vscore[1].find(" ") + 1, -1) << "  " << "점수 : " << jumsu[1] << endl;
		cout << "3위. " << vscore[2].substr(vscore[2].find(" ") + 1, -1) << "  " << "점수 : " << jumsu[2] << endl;
	}
	else if (vscore.size() == 2) {
		cout << "1위. " << vscore[0].substr(vscore[0].find(" ") + 1, -1) << "  " << "점수 : " << jumsu[0] << endl;
		cout << "2위. " << vscore[1].substr(vscore[1].find(" ") + 1, -1) << "  " << "점수 : " << jumsu[1] << endl;
	}
	else {
		cout << "기록을 확인하려면 한번 더 플레이 하세요!" << endl;
	}
	cout << "0을 입력하면 메뉴로 돌아갑니다." << endl;
	fin.close(); // 파일 닫기
	cin.ignore();
	getline(cin, s, '0'); // 0을 입력받으면 메뉴로
}


void snake::menu() { // 메뉴 함수 생성
	system("cls");
	cout << endl << "     1. 게임 설정" << endl << endl;
	cout << endl << "     2. 게임 기록" << endl << endl;
	cout << endl << "     3. 게임 시작" << endl << endl;
	cout << endl << "     4. 게임 종료" << endl << endl;
}

void snake::start() { // 게임 시작을 위한 함수
	system("cls");
	string b;
	cout << endl << endl << endl << "----------------------------------------------------" << endl << "Do you want to play? (y/n)" << endl << "----------------------------------------------------";
	cin >> b;
	if (b == "y") {
		v[v.size() - 1].makemap();
		v[v.size() - 1].makefood();
		v[v.size() - 1].move();
	}
	else if (b == "n") {
		gameend();
	}
}

void snake::gameend() { // 종료 함수 생성
	system("cls");
	exit(0);
}

void snake::setsnake() { // 게임설정을 위한 함수
	system("cls");
	string name;
	int mapx;
	int mapy;
	int length;
	int speed;
	cout << "1. 플레이어 이름 : ";
	cin >> name;
	cout << "2. 플레이 할 맵의 크기 : ";
	cin >> mapx;
	cin >> mapy;
	cout << "3. 게임 시작 시 스네이크의 길이(1~10) : ";
	cin >> length;
	cout << "4. 게임 속도(1 = 0.1ms) : ";
	cin >> speed;
	snake a(name, mapx, mapy, length, speed);
	v.push_back(a);
}

void snake::makemap() { // 맵을 만들기 위한 함수
	system("cls");
	for (int i = 0; i < mapx; i++) {
		gotoxy(i, 0, "@");
		gotoxy(i, mapy, "@");
	}
	for (int i = 0; i < mapy; i++) {
		gotoxy(0, i, "@");
		gotoxy(mapx, i, "@");
	}
	posx.push_back(mapx / 2); // 처음 뱀머리의 x좌표
	posy.push_back(mapy / 2); // 처음 뱀머리의 y좌표
	posx.push_back(mapx / 2 - 1); // 머리 뒤의 꼬리 x좌표
	posy.push_back(mapy / 2); // 머리 뒤의 꼬리 y좌표
	posx.push_back(mapx / 2 - 2);
	posy.push_back(mapy / 2);
	for (int i = 0; i < 101; i++) { // 최대 꼬리 100개
		posx.push_back(0);
		posy.push_back(0);
	}
}

void snake::makefood() { // 뱀 음식을 만들기 위한 함수
	while (true) {
		srand((unsigned)time(NULL)); // 랜덤 함수 사용
		foodx = (rand() % (mapx - 2)) + 1;
		foody = (rand() % (mapy - 2)) + 1;
		for (int i = 0; i < length; i++) {
			if (foodx == bamx + i && foody == bamy + i) { // 뱀과 음식이 겹칠경우 다시 while
				continue;
			}
			else { // 안겹칠경우 해당 좌표에 +생성
				gotoxy(foodx, foody, "+");
			}
		}
		break;
	}
}

void snake::move() { // 뱀이 움직이기 위한 함수
	string s;
	while (true) {
		Sleep(speed * 100); //뱀의 속도
		if (_kbhit()) {//키 입력이 되어있는가
			if (_getch() == 224) { // 키 입력
				direction = _getch(); // 입력받은 키를 방향 변수에 넣음
			}
		}
		gotoxy(posx[length - 1], posy[length - 1], " "); // 뱀의 마지막 꼬리를 지움
		for (int i = length - 1; i >= 0; i--) { // 뱀의 좌표를 한칸씩 전진
			posx[i + 1] = posx[i];
			posy[i + 1] = posy[i];
		}
		if (length > 1) { // 꼬리를 출력
			gotoxy(posx[0], posy[0], "o");
		}
		if (direction == RIGHT) posx[0]++; // 입력받은 방향에 따라 뱀머리의 방향을 이동
		if (direction == LEFT) posx[0]--;
		if (direction == UP) posy[0]--;
		if (direction == DOWN) posy[0]++;

		if (posx[0] == 0 || posy[0] == 0 || posx[0] == mapx || posy[0] == mapy) { // 맵에 충돌 할 경우
			end();
			return;
		}
		bamx = posx[0];
		bamy = posy[0];
		if (length > 1) {
			for (int i = 1; i < length; i++) {
				if ((posx[i] == bamx) && (posy[i] == bamy)) { // 머리와 몸이 충돌 할 경우
					end();
					return;
				}
			}
		}
		if (posx[0] == foodx && posy[0] == foody) { // 뱀이 음식을 먹은 경우
			makefood();
			length++;
			score += 10;
		}
		gotoxy(posx[0], posy[0], "$"); // 뱀 머리 출력
	}
}

void snake::end() { // 뱀이 죽었을 경우
	string s;
	bamx = mapx / 2; // 뱀 머리 좌표 초기화
	bamy = mapy / 2;
	posx[0] = bamx;
	posy[0] = bamy;
	
	ofstream fout;
	fout.open("Record.txt", ios::app); // 쓰기 위해 Record.txt열기 커서는 마지막 위치로


	if (!fout) { // fout 스트림의 파일 열기가 실패한 경우
		cout << "파일이 없습니다." << endl;		 // 파일 열기 실패를 처리하는 코드
	}
	fout << score << " " << name << endl;
	system("cls");
	cout << "Score = " << score << endl;
	cout << "Press [Enter] to quit...";
	cin.ignore();
	getline(cin, s, '\n');

	fout.close(); // 파일 닫기
	score = 0; // 점수 초기화
}

int main() {
	snake a;
	int choice;
	while (true) {
		a.menu();
		cin >> choice;
		switch (choice) { // switch문을 이용하여 메뉴에 맞는 함수로 이동
		case 1:
			a.setsnake();
			break;
		case 2:
			a.setscore();
			break;
		case 3:
			a.start();
			break;
		case 4:
			a.gameend();
			break;
		default:
			continue;
		}
	}
}