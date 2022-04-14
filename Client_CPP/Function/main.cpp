#include <iostream>
using namespace std;

// 디폴트 인수
// 함수 선언때 가장 오른쪽에서 부터 순서대로 지정 할 수 있음
// 함수 호출시 디폴트 인수가 지정된 파라미터에 대입할 인자가 전달되지 않으면
// 지정한 디폴트 인수값을 대입한다.
// 함수 오버로딩과 충돌이 있을 수 있으므로 주의해서 쓴다. 
int Sum(int a, int b = 2);
int Sum(int a, int b, int c);
double Sum(double a, double b);
float Sum(float a, float b);

// 인라인 함수
// 원래 함수 호출순서가
// 스택영역에 함수 원형 복사해서 가져옴 ( 매개변수 + 반환형 + 반환 주소값 등 )
// 함수호출이 끝나면 쟤내 다 반환하고 스택영역에서 해제됨. 
// 
// 인라인함수는 함수 실행시간이 호출시간보다 짧을때를 위해서 만들어짐
// 함수 정의를 함수호출스택에 그대로 쌓아놓는 형태
inline int Sub(int a, int b)
{
	return a - b;
};


int main() {

	cout << Sum(1, 2) << endl;
	cout << Sum(1.3, 2.4) << endl;
	cout << Sum(1.3f, 2.4f) << endl;
	cout << Sum(1, 2, 3) << endl;
	return 0;
}

// 함수 오버로딩
// 객체지향에서 다형성을 구현하는 수단
// 동일한 이름을 가진 함수를 정의할수 있는 기능

 int Sum(int a, int b) {
	return a + b;
}

int Sum(int a, int b, int c) {
	return a + b + c;
}

double Sum(double a, double b) {
	return a + b;
}

float Sum(float a, float b) {
	return a + b;
}