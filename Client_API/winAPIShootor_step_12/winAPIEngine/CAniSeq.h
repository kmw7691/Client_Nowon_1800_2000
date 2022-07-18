#pragma once
#include <vector>
#include <string>
using namespace std;

class CTexture;

enum ANI_PO
{
    LOOP = 0,           //반복해서 플레이
    ONCE,               //한번만 플레이
};

enum ANI_SO
{
    FRAME_FILE = 0,     //스프라이트 프레임이 파일단위로 존재
    SHEET_FILE,         //스프라이트 프레임들이 하나의 스프라이트 시트파일에 존재
};



class CAniSeq
{
public:
    CAniSeq() :
        mId(""), mAniTime(0.0f), mTimeInterval(0.1f), mCurFrameIndex(0), mTotalFramesCount(0)
    {
        mTexs.clear();
    }
    CAniSeq(const CAniSeq& t)
    {
        *this = t;


        /*
        * vector<CTexture*>::iterator tItor;
        * for(tItor = mTexs.begin(); tItor != mTexs.end(); ++tItor)
        * {
        * 
        * }
        */
    };
    ~CAniSeq()
    {
        mTexs.clear();
    }

    void Update(float tDeltaTime);


    void SetSpriteFrameWH(int tRow = 1, int tCol = 1);





public:
    string mId = "";                //애니메이션 시퀀스의 식별자 키

    vector<CTexture*> mTexs;        //애니메이션 시퀀스의 각각의 프레임을 구성하는 이미지 정보

    float mTimeInterval = 0.1f;     //애니메이션 시퀀스의 프레임간 시간
    int mTotalFramesCount = 0;      //애니메이션 시퀀스의 총 프레임 갯수

    int mCurFrameIndex = 0;         //실행중에 현재 프레임 번호

    float mAniTime = 0.0f;          //애니메이션 진행 시간(틱)



    //
    ANI_PO mPlayOption = ANI_PO::LOOP;

    ANI_SO mSpriteOption = ANI_SO::FRAME_FILE;


    //프레임들의 너비, 높이
    int mSpriteWidth = 0;
    int mSpriteHeight = 0;

    int mRow = 0;
    int mCol = 0;

    int mFrameCOL = 0;
};

