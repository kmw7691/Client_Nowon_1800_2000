#pragma once



// 싱글톤 패턴

/*
	싱글톤 패턴의 목적 : 객체의 최대 생성갯수를 1개로 제한
						  (부가적으로 전역적인 성격의 데이터들의 관리의 목적으로도 쓰임)

	다음의 세가지 구성으로 이루어진다.
		- 해당 클래스 포인터 타입의 mpInstance 변수가 static으로 선언된다
		- 생성자는 public이 아니다
		- GetInstance() 함수의 정의에는 객체의 최대 생성갯수를 1개로 제한하는 판단제어구조가 위치한다
*/

//step 0

//class CInputMgr
//{
//private:
//	//static 키워드로 선언한 변수는 데이터메모리영역에 위치한다
//	//클래스의 멤버가 아니므로? 클래스의 멤버 초기화 형식을 취할 수 없다
//
//	static CInputMgr* mpInstance; //= nullptr;
//
//	CInputMgr();
//	~CInputMgr();
//
//public:
//	static CInputMgr* GetInst();
//	static void ReleaseInst();
//};

#include "Kmacro.h"

class CInputMgr
{
	SINGLETON_DECLARE(CInputMgr)
};
