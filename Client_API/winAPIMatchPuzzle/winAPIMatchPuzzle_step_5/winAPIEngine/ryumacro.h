#pragma once



#define SAFE_DELETE(p) if(nullptr != p) { delete p; p = nullptr; }

//매크로 함수 정의의 기본은 한 줄이지만 
//여러줄 표기하려면 \로 이어서 하면 한줄로 인식한다
#define SAFE_DELETE_RYU(p) \
    if(nullptr != p)\
    { \
        delete p;\
        p = nullptr; \
    }



#define SINGLETON_DECLARE(p) private:\
    static p* mpInstance;\
private:\
    p();\
    ~p();\
public:\
    static p* GetInstance();\
    static void ReleaseInstance();



#define SINGLETON_DEFINITION(p) p* p::mpInstance = nullptr;\
p* p::GetInstance()\
{\
if (nullptr == mpInstance)\
{\
	mpInstance = new p();\
}\
return mpInstance;\
}\
void p::ReleaseInstance()\
{\
	if (nullptr != mpInstance)\
	{\
		delete mpInstance;\
	}\
}




#define ROOT_PATH "root_path"
#define RESOUCES_PATH " resources_path"