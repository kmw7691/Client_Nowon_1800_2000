#pragma once
class Creature
{
public:
	int mass;
	int height;
	int age;

public:
	// virtual : 가상함수 키워드
	// 가상함수로 정의된 함 수는 호출되었을때 자식객체가 해당 멤버함수를 override하고 있다면
	// override 된 함수를 호출한다
	virtual void Breath();

	// 순수 가상함수
	// 가상함수인데 정의가 없는 친구
	// 정의가 없기때문에 해당 클래스를 상속받는 자식클래스는
	// 반드시 이 순수 가상함수들을 재정의해서 사용해야한다
	// 쓰는 이유:
	// 반드시 있어야하는 기능인데, 부모클래스에서는 해당기능을 정의하기가 애매할때
	// 디폴드로 기능을 사용하는것이 넌센스일때 사용
	// 인터페이스처럼 특정 기능으로 객체들을 묶어서 사용하고자 할때 씀
	virtual void Grow();
};

