#pragma once
#include "SVector2D.h"
#include "CRef.h"

class CObjectK:public CRef
{
public:
	CObjectK();
	virtual ~CObjectK();

public:
	virtual CObjectK* clone() = 0;



//public:
protected:
	//위치정보
	SVector2D mPosition;

	/*

	// 참조 카운팅 변수
	//int mRef = 0;

	//void AddRef()
	//{
	//	// 참조카운트를 하나씩 증가한다
	//	++mRef;
	//}
	//
	//int Release()
	//{
	//	//참조를 하나씩 줄여준다
	//	--mRef;

	//	//최종적으로 참조카운트가 0이되면 메모리를 해제하고 참조카운트0을 리턴한다
	//	if (0 == mRef)
	//	{
	//		delete this;
	//		return 0;
	//	}

	//	return mRef;
	//}
	*/

	// OOP프로그래밍의 4가지 특징
	/*
		OOP프로그래밍의 4가지 특징

		추상화	abstraction		: 코드의 추상화 + 데이터의 추상화 -> 데이터의 추상화
		은닉화	encapsulation	: Data Hiding
		상속성	inheritance		: 공통된 특성을	부모클래스에 두고 이를 이어받아 자식클래스를 작성하는 것, 효율적인 재사용
		다형성	polymorphysm	: 같은 메시지에 다른 반응.
									override + virtual + 부모클래스타입의 포인터
	*/
};

