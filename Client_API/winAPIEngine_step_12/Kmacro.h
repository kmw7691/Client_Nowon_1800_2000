#pragma once

#define SAFE_DELETE(p) if(nullptr != p) {delete p;p = nullptr;}



//#define SINGLETON_DECLARE(p) private:\
//	static CInputMgr* mpInstance;\
//	CInputMgr();\
//	~CInputMgr();\
//public:\
//	static CInputMgr* GetInst();\
//	static void ReleaseInst();\

#define SINGLETON_DECLARE(p) private:\
	static CInputMgr* mpInstance;\
	CInputMgr();\
	~CInputMgr();\
public:\
	static CInputMgr* GetInst();\
	static void ReleaseInst();