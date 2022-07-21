#pragma once

#include <vector>
#include <string>
using namespace std;

class CTexture;


//애니메이션 플레이 옵션 
enum ANI_PO
{
	LOOP = 0,		//반복해서 플레이 
	ONCE,			//한번만 플레이
};

//스프라이트 옵션
enum ANI_SO
{
	FRAME_FILE = 0,		//스프라이트 프레임이 파일 단위로 존재
	SHEET_FILE,			//스프라이트 프레임들이 하나의 스프라이트 시트 파일에 존재 
};

class CAniSeq
{
public:
	CAniSeq(): 
		mId(""), mAniTime(0.0f), mTimeInterval(0.1f), mCurFrameIndex(0), mTotalFramesCount(0)
	{
		mTexs.clear();
	};
	CAniSeq(const CAniSeq& t)
	{
		*this = t;

		//텍스쳐는 공유자원이다.
		/*vector<CTexture*>::iterator tItor;
		for (tItor = mTexs.begin(); tItor != mTexs.end(); ++tItor)
		{
			
		}*/
	};
	~CAniSeq()
	{
	};


	void Update(float fElapsedTime);

	void SetSpriteFrameWH(int tRow = 1, int tCol = 1);
	


public:

	string mId = "";
	vector<CTexture*> mTexs;
	float mTimeInterval = 0.1f;
	int mTotalFramesCount = 0;

	int mCurFrameIndex = 0;
	float mAniTime = 0.0f;


	ANI_PO mPlayOption = ANI_PO::LOOP;

	//ryu_ani_spritesheet_i
	ANI_SO mSpriteOption = ANI_SO::FRAME_FILE;




	//ryu_ani_spritesheet_i
	int mSpriteWidth = 0;
	int mSpriteHeight = 0;

	int mRow = 0;	//행
	int mCol = 0;	//열
	int mFrameCOL = 0;		//스프라이트 프레임의 너비
};

