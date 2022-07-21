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
//����Ű �ڵ尪 ����
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

class snake { // snakeŬ���� ����
private:
	vector<snake> v; // snakeŬ������ �� ����
	string name;
	int mapx;
	int mapy;
	int foodx;
	int foody;
	int bamx;
	int bamy;

	vector<int> posx; // x ��ǥ
	vector<int> posy; // y ��ǥ

	int length;
	int speed;
	int direction;
	int score;
public:
	snake(string name = " ", int mapx = 100, int mapy = 100, int length = 1, int speed = 1) { // ������
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
	friend void gotoxy(int x, int y, string s); // friend�� �̿��� �����Լ� ���
};

void gotoxy(int x, int y, string s) { // x,y��ǥ�� s�� ���  
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	cout << s;
}

void snake::setscore() { // ���� ����� ǥ���ϱ� ���� �Լ�
	system("cls");
	string s;

	vector<string> vscore;
	vector<string> jumsu;
	ifstream fin("Record.txt"); // �б� ���� Record.txt ���� ����
	string line;
	int x = 0;
	string temp1, temp2;
	while (true) { // Record.txt ���Ͽ��� ���پ� vscore���Ϳ� �Է�
		getline(fin, line);
		if (fin.eof()) break;
		vscore.push_back(line);
	}
	if (vscore.size() > 1) {
		for (int i = 0; i < vscore.size(); i++) { // vscore���Ϳ��� ���ڸ� jumsu���ͷ� �Է�
			x = vscore[i].find(" ");
			jumsu.push_back(vscore[i].substr(0, x));
		}
		for (int i = vscore.size() - 2; i >= 0; i--) {
			if (atoi(jumsu[i].c_str()) < atoi(jumsu[i + 1].c_str())) { // jumsu���Ϳ� string�� int�� �ٲ㼭 ũ�� ��
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
		cout << "1��. " << vscore[0].substr(vscore[0].find(" ") + 1, -1) << "  " << "���� : " << jumsu[0] << endl;
		cout << "2��. " << vscore[1].substr(vscore[1].find(" ") + 1, -1) << "  " << "���� : " << jumsu[1] << endl;
		cout << "3��. " << vscore[2].substr(vscore[2].find(" ") + 1, -1) << "  " << "���� : " << jumsu[2] << endl;
		cout << "4��. " << vscore[3].substr(vscore[3].find(" ") + 1, -1) << "  " << "���� : " << jumsu[3] << endl;
		cout << "5��. " << vscore[4].substr(vscore[4].find(" ") + 1, -1) << "  " << "���� : " << jumsu[4] << endl;
	}
	else if (vscore.size() == 4) {
		cout << "1��. " << vscore[0].substr(vscore[0].find(" ") + 1, -1) << "  " << "���� : " << jumsu[0] << endl;
		cout << "2��. " << vscore[1].substr(vscore[1].find(" ") + 1, -1) << "  " << "���� : " << jumsu[1] << endl;
		cout << "3��. " << vscore[2].substr(vscore[2].find(" ") + 1, -1) << "  " << "���� : " << jumsu[2] << endl;
		cout << "4��. " << vscore[3].substr(vscore[3].find(" ") + 1, -1) << "  " << "���� : " << jumsu[3] << endl;
	}
	else if (vscore.size() == 3) {
		cout << "1��. " << vscore[0].substr(vscore[0].find(" ") + 1, -1) << "  " << "���� : " << jumsu[0] << endl;
		cout << "2��. " << vscore[1].substr(vscore[1].find(" ") + 1, -1) << "  " << "���� : " << jumsu[1] << endl;
		cout << "3��. " << vscore[2].substr(vscore[2].find(" ") + 1, -1) << "  " << "���� : " << jumsu[2] << endl;
	}
	else if (vscore.size() == 2) {
		cout << "1��. " << vscore[0].substr(vscore[0].find(" ") + 1, -1) << "  " << "���� : " << jumsu[0] << endl;
		cout << "2��. " << vscore[1].substr(vscore[1].find(" ") + 1, -1) << "  " << "���� : " << jumsu[1] << endl;
	}
	else {
		cout << "����� Ȯ���Ϸ��� �ѹ� �� �÷��� �ϼ���!" << endl;
	}
	cout << "0�� �Է��ϸ� �޴��� ���ư��ϴ�." << endl;
	fin.close(); // ���� �ݱ�
	cin.ignore();
	getline(cin, s, '0'); // 0�� �Է¹����� �޴���
}


void snake::menu() { // �޴� �Լ� ����
	system("cls");
	cout << endl << "     1. ���� ����" << endl << endl;
	cout << endl << "     2. ���� ���" << endl << endl;
	cout << endl << "     3. ���� ����" << endl << endl;
	cout << endl << "     4. ���� ����" << endl << endl;
}

void snake::start() { // ���� ������ ���� �Լ�
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

void snake::gameend() { // ���� �Լ� ����
	system("cls");
	exit(0);
}

void snake::setsnake() { // ���Ӽ����� ���� �Լ�
	system("cls");
	string name;
	int mapx;
	int mapy;
	int length;
	int speed;
	cout << "1. �÷��̾� �̸� : ";
	cin >> name;
	cout << "2. �÷��� �� ���� ũ�� : ";
	cin >> mapx;
	cin >> mapy;
	cout << "3. ���� ���� �� ������ũ�� ����(1~10) : ";
	cin >> length;
	cout << "4. ���� �ӵ�(1 = 0.1ms) : ";
	cin >> speed;
	snake a(name, mapx, mapy, length, speed);
	v.push_back(a);
}

void snake::makemap() { // ���� ����� ���� �Լ�
	system("cls");
	for (int i = 0; i < mapx; i++) {
		gotoxy(i, 0, "@");
		gotoxy(i, mapy, "@");
	}
	for (int i = 0; i < mapy; i++) {
		gotoxy(0, i, "@");
		gotoxy(mapx, i, "@");
	}
	posx.push_back(mapx / 2); // ó�� ��Ӹ��� x��ǥ
	posy.push_back(mapy / 2); // ó�� ��Ӹ��� y��ǥ
	posx.push_back(mapx / 2 - 1); // �Ӹ� ���� ���� x��ǥ
	posy.push_back(mapy / 2); // �Ӹ� ���� ���� y��ǥ
	posx.push_back(mapx / 2 - 2);
	posy.push_back(mapy / 2);
	for (int i = 0; i < 101; i++) { // �ִ� ���� 100��
		posx.push_back(0);
		posy.push_back(0);
	}
}

void snake::makefood() { // �� ������ ����� ���� �Լ�
	while (true) {
		srand((unsigned)time(NULL)); // ���� �Լ� ���
		foodx = (rand() % (mapx - 2)) + 1;
		foody = (rand() % (mapy - 2)) + 1;
		for (int i = 0; i < length; i++) {
			if (foodx == bamx + i && foody == bamy + i) { // ��� ������ ��ĥ��� �ٽ� while
				continue;
			}
			else { // �Ȱ�ĥ��� �ش� ��ǥ�� +����
				gotoxy(foodx, foody, "+");
			}
		}
		break;
	}
}

void snake::move() { // ���� �����̱� ���� �Լ�
	string s;
	while (true) {
		Sleep(speed * 100); //���� �ӵ�
		if (_kbhit()) {//Ű �Է��� �Ǿ��ִ°�
			if (_getch() == 224) { // Ű �Է�
				direction = _getch(); // �Է¹��� Ű�� ���� ������ ����
			}
		}
		gotoxy(posx[length - 1], posy[length - 1], " "); // ���� ������ ������ ����
		for (int i = length - 1; i >= 0; i--) { // ���� ��ǥ�� ��ĭ�� ����
			posx[i + 1] = posx[i];
			posy[i + 1] = posy[i];
		}
		if (length > 1) { // ������ ���
			gotoxy(posx[0], posy[0], "o");
		}
		if (direction == RIGHT) posx[0]++; // �Է¹��� ���⿡ ���� ��Ӹ��� ������ �̵�
		if (direction == LEFT) posx[0]--;
		if (direction == UP) posy[0]--;
		if (direction == DOWN) posy[0]++;

		if (posx[0] == 0 || posy[0] == 0 || posx[0] == mapx || posy[0] == mapy) { // �ʿ� �浹 �� ���
			end();
			return;
		}
		bamx = posx[0];
		bamy = posy[0];
		if (length > 1) {
			for (int i = 1; i < length; i++) {
				if ((posx[i] == bamx) && (posy[i] == bamy)) { // �Ӹ��� ���� �浹 �� ���
					end();
					return;
				}
			}
		}
		if (posx[0] == foodx && posy[0] == foody) { // ���� ������ ���� ���
			makefood();
			length++;
			score += 10;
		}
		gotoxy(posx[0], posy[0], "$"); // �� �Ӹ� ���
	}
}

void snake::end() { // ���� �׾��� ���
	string s;
	bamx = mapx / 2; // �� �Ӹ� ��ǥ �ʱ�ȭ
	bamy = mapy / 2;
	posx[0] = bamx;
	posy[0] = bamy;
	
	ofstream fout;
	fout.open("Record.txt", ios::app); // ���� ���� Record.txt���� Ŀ���� ������ ��ġ��


	if (!fout) { // fout ��Ʈ���� ���� ���Ⱑ ������ ���
		cout << "������ �����ϴ�." << endl;		 // ���� ���� ���и� ó���ϴ� �ڵ�
	}
	fout << score << " " << name << endl;
	system("cls");
	cout << "Score = " << score << endl;
	cout << "Press [Enter] to quit...";
	cin.ignore();
	getline(cin, s, '\n');

	fout.close(); // ���� �ݱ�
	score = 0; // ���� �ʱ�ȭ
}

int main() {
	snake a;
	int choice;
	while (true) {
		a.menu();
		cin >> choice;
		switch (choice) { // switch���� �̿��Ͽ� �޴��� �´� �Լ��� �̵�
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