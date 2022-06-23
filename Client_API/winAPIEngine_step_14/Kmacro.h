#pragma once

#define SAFE_DELETE(p) if(nullptr != p) {delete p;p = nullptr;}



//#define SINGLETON_DECLARE(p) private:\
//	static p* mpInstance;\
//	p();\
//	~p();\
//public:\
//	static p* GetInst();\
//	static void ReleaseInst();\

#define SINGLETON_DECLARE(p) private:\
	static p* mpInstance;\
	p();\
	~p();\
public:\
	static p* GetInst();\
	static void ReleaseInst();



#define SINGLETON_DEFINITION(p) p* p::mpInstance = nullptr;\
p* p::GetInst()\
{\
	if (nullptr == mpInstance)\
	{\
		mpInstance = new p();\
	}\
	return mpInstance;\
}\
void p::ReleaseInst()\
{\
	if (nullptr != mpInstance)\
	{\
		delete mpInstance;\
	}\
}
