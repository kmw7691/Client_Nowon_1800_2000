#pragma once


/*
	싱글톤 패턴

	싱글톤 패턴의 목적: 
	
		객체의 최대 생성갯수를 1개로 제한 
		( 부가적으로 전역적인 성격의 데이터들의 관리의 목적으로도 쓰인다. )
		
	다음의 세가지 구성으로 이루어진다.
	
	i) 해당 클래스 포인터 타입의 mpInstance 변수가 static으로 선언된다.
	ii) 생성자는 public 이 아니다.
	iii) GetInstance() 함수의 정의에는 객체의 최대 생성 갯수를 1개로 제한하는 판단제어구조가 위치한다.

*/

//step_0
//class CInputMgr
//{
//private:
////static키워드로 선언한 변수는 데이터메모리영역에 위치한다. 
////클래스의 멤버가 아니므로? 클래스의 멤버 초기화 형식을 취할 수 없다.
//	static CInputMgr* mpInstance;// = nullptr;
//
//private:
//	CInputMgr();
//	~CInputMgr();
//
//public:
//	static CInputMgr* GetInst();
//	static void ReleaseInst();
//
//};

//step_1
#include "ryumacro.h"



//typeid를 위해 
#include <typeinfo>


#include <windows.h>
#include <string>
#include <unordered_map>		//해쉬테이블 자료구조를 컨테이너로 만들어놓은 것. 검색속도는 O(1)
#include <vector>
using namespace std;



//키 정보를 표현하기 위한 구조체
struct SKeyInfo
{
	string mStrName = "";			//키
	vector<DWORD> mKeyInputs;		//데이터
	//DWORD mKeyInput = 0;			//데이터


	bool mIsDown = false;
	bool mIsPress = false;
	bool mIsUp = false;

	SKeyInfo()
		:mIsDown(false), mIsPress(false), mIsUp(false)
	{
		mKeyInputs.clear();
	}
};






class CInputMgr
{
	SINGLETON_DECLARE(CInputMgr)


private:
	HWND mhWnd;

	//해쉬테이블을 만든 것이다. O(1)의 접근이 가능
	unordered_map<string, SKeyInfo*> mMapKeys;

	SKeyInfo* mpKeyInfo = nullptr;

public:
	virtual void Create(HWND hWnd);
	void Update();			//키보드 입력 상태를 점검하기 위해 게임루프상에서 계속 갱신되는 함수

	SKeyInfo* FindKey(const string& tStrKey) const;			//원하는 키입력을 검색하는 함수


	bool KeyDown(const string& tStrKey) const;				//Down눌린다 여부
	bool KeyPress(const string& tStrKey) const;				//Press눌리고 있다 여부
	bool KeyUp(const string& tStrKey) const;				//Up떼어진다 여부


	//추상화된 입력 이름과 실제 키입력정보를 매핑시켜서 등록하는 함수
	//	(  char 타입과 int타입을 모두 처리하기 위해 템플릿함수로 작성  )
	//template<typename T>
	//bool AddKey(const string& tInputName, const T& tData)
	//{
	//	if (!mpKeyInfo)
	//	{
	//		mpKeyInfo = new SKeyInfo();		//새로운 키보드입력정보 객체 하나를 생성한다
	//	}


	//	//typeid 타입에 정보를 알아오는 연산자
	//	//
	//	const char* tpType = typeid(T).name();	//타입의 이름을 얻어온다

	//	if (strcmp(tpType, "char") == 0 ||
	//		strcmp(tpType, "int") == 0)
	//	{
	//		mpKeyInfo->mKeyInput = (DWORD)tData;			//키보드입력정보객체의 키입력을 설정
	//	}
	//	else
	//	{
	//		return false;
	//	}

	//	//추상화 이름 등록 
	//	//키
	//	mpKeyInfo->mStrName = tInputName;
	//	//추상화 이름을 키로, 실제 키입력을 데이터로 등록 
	//	mMapKeys.insert(
	//		make_pair(mpKeyInfo->mStrName, mpKeyInfo)		//키, 값(실제데이터) 쌍의 데이터(키보드입력정보객체)를 해쉬테이블에 추가 
	//	);



	//	if (mpKeyInfo)
	//	{
	//		mpKeyInfo = nullptr;
	//	}


	//	return true;
	//}




	//base case
	// 재귀적으로 호출될 것의 종료조건 함수
	template<typename T>
	bool AddKey(const T& tData)
	{
		const char* tpType = typeid(T).name();

		if (strcmp(tpType, "char") == 0 ||
			strcmp(tpType, "int") == 0)
		{
			//키 등록
			//DWORD로 변환
			mpKeyInfo->mKeyInputs.push_back((DWORD)tData);
		}
		else
		{
			//추상화 이름 등록 
			mpKeyInfo->mStrName = tData;

			mMapKeys.insert(
				make_pair(mpKeyInfo->mStrName, mpKeyInfo)
			);
		}

		return true;
	}







	//가변인자 템플릿: 매개변수(타입)의 갯수를 가변적으로 입력받는 템플릿 문법 
	template<typename T, typename... Types>
	bool AddKey(const T& tData, const Types&... arg)
	{
		if (!mpKeyInfo)
		{
			mpKeyInfo = new SKeyInfo();		//새로운 키보드입력정보 객체 하나를 생성한다
		}


		//typeid 타입에 정보를 알아오는 연산자
		//
		const char* tpType = typeid(T).name();	//타입의 이름을 얻어온다

		if (strcmp(tpType, "char") == 0 ||
			strcmp(tpType, "int") == 0)
		{
			mpKeyInfo->mKeyInputs.push_back((DWORD)tData);			//키보드입력정보객체의 키입력을 설정
		}
		else
		{
			//추상화 이름 등록 
			mpKeyInfo->mStrName = tData;

			mMapKeys.insert(
				make_pair(mpKeyInfo->mStrName, mpKeyInfo)
			);
		}

		//재귀적으로 호출 recursive case
		AddKey(arg...);


		//여기까지 오면 재귀호출이 모두 끝난 것이다.
		if (mpKeyInfo)
		{
			mpKeyInfo = nullptr;
		}


		return true;
	}
};

