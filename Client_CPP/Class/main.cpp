#include <iostream>
using namespace std;

// 접근제한자
// public : 외부에서 접근 가능한 키워드
// private : 외부에서 접근 불가능한 키워드
// protected : 자식객체만 접근가능한 키워드

class Coord {
//public:
//	int x, y;

private:
	int _x, _y;

public:
	// 객체지향컨셉에서는
	// 되도록 객체가 다른 객체의 멤버변수를 직접 접근해서 수정하지 않도록 지향함
	// 보통 접근할수있는 함수를 제공하도록함
	void SetCoord(int x, int y) {
		_x = x;
		_y = y;
	}

	int GetCoordX() {
		return _x;
	}

	int GetCoordY() {
		return _y;
	}

	// 생성자 (얘는 함수)
	Coord() {	};

	Coord(int x, int y) {
		SetCoord(x, y);
	}

	// 소멸자 (얘도 함수)
	~Coord() {};

	const Coord& operator = (const Coord& _other) {
		this->_x = _other._x;
		this->_y = _other._y;
		// this 포인터 
		// 현재 객체 자기 자신을 가리키는 포인터
		// 클래스안에서 멤버에 접근할때는 this포인터가 생략되어있다.
	}

	// 연산자 정의
	const Coord& operator + (const Coord& _other) {
		Coord tmpCoord;
		tmpCoord.SetCoord(_x + _other._x,
						  _y + _other._y); 
		return tmpCoord;
	}
};

int main() {

	Coord coord1;

	cout << "(" << coord1.GetCoordX() << "," << coord1.GetCoordY() << ")" << endl;
	coord1.SetCoord(1, 2);
	cout << "(" << coord1.GetCoordX() << "," << coord1.GetCoordY() << ")" << endl;

	// 객체를 힙영역에 동적할당 할 시
	// new 생성자
	// 형태로 할당함.
	Coord* coord2ptr = new Coord(5,2);
	cout << "(" << coord2ptr -> GetCoordX() << "," << coord2ptr -> GetCoordY() << ")" << endl;
	
	// 클래스간의 대입연산 가능
	coord1 = *coord2ptr;
	Coord coord3 = (coord1 + *coord2ptr);

	cout << "(" << coord1.GetCoordX() << "," << coord1.GetCoordY() << ")" << endl;

	delete coord2ptr;


	return 0;
}