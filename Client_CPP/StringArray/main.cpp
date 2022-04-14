#include <iostream>
#include <string>
// #include <cstring>
using namespace std;

int main() {

	const int DEFAULT_SIZE = 4;
	// 기존 C 문자열
	//char firstName[DEFAULT_SIZE];
	//char lastName[DEFAULT_SIZE]; // 한문자를 1byte로 사용함
	//wchar_t ct = L'아'; //　한문자를　２ｂｙｔｅ로 사용함.

	// C++ 문자열
	string firstName, lastName;

	cout << "성을 입력하세요";
	//cin >> firstName;
	//cin.get(firstName, DEFAULT_SIZE).get();
	//cin.get(firstName, DEFAULT_SIZE).ignore(DEFAULT_SIZE, '\n');
	getline(cin, firstName);

	cout << "이름을 입력하세요";
	//cin >> lastName;
	//cin.get(lastName, DEFAULT_SIZE).get();
	//cin.get(lastName, DEFAULT_SIZE).ignore(DEFAULT_SIZE, '\n');
	getline(cin, lastName);

	cout << "성은" << firstName << "이요, 이름은" << lastName << "이다" << endl;

	// 문자열 클래스의 활용

	// 기존 C 문자열처럼 인덱스접근이 가능하다
	cout << firstName[0];

	// 문자열 클래스의 함수들
	//=============================================================
	// 인덱스접근을 활용한 for문도 가능하다
	for (int i = 0; i < firstName.length(); i++)
		cout << firstName[i];

	cout << firstName.length() << endl;
	cout << firstName.size() << endl;

	// append()
	// 문자열을 추가하는 메소드 
	string str1, str2, str3;
	str1.append("Hello World!");
	str2.append("Hello World!", 6, 5);
	str3.append(4, '!');

	cout << str1 << endl;
	cout << str2 << endl;
	cout << str3 << endl;

	// find()
	// 현재 문자열 객체에서 특정 문자열을 찾는 메소드
	// 문자열을 찾는데 실패하면 string::npos;

	if (str1.find("Hello", 0) != string::npos)
		cout << "Hello 찾는데 성공" << endl;
	else
		cout << "Hello 찾는데 실패" << endl;

	// compare()
	// 두 문자열을 비교하는 메소드
	// 같은경우 0 , 인자보다 사전순으로 앞에있을경우 음수, 뒤에있을경우양수
	cout << (str1.compare(str2) == 0) << endl;
	cout << (str1.compare(str2) < 0) << endl;
	cout << (str1.compare(str2) > 0) << endl;

	// replace()
	// 인자로 넣어준 문자열로 대체하는 메소드
	// 문자열.replace(대체문자열시작위치, 대체문자열길이, 새로운 문자열);

	str1.replace(0, str2.length(), str3);
	cout << str1 << endl;

	string str = "123456678901234567890";
	cout << str.capacity() << endl;
	cout << str.max_size() << endl;

	return 0;
}