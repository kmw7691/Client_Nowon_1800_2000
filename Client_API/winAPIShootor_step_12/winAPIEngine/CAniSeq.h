#pragma once
#include <vector>
#include <string>
using namespace std;

class CTexture;

enum ANI_PO
{
    LOOP = 0,           //�ݺ��ؼ� �÷���
    ONCE,               //�ѹ��� �÷���
};

enum ANI_SO
{
    FRAME_FILE = 0,     //��������Ʈ �������� ���ϴ����� ����
    SHEET_FILE,         //��������Ʈ �����ӵ��� �ϳ��� ��������Ʈ ��Ʈ���Ͽ� ����
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
    string mId = "";                //�ִϸ��̼� �������� �ĺ��� Ű

    vector<CTexture*> mTexs;        //�ִϸ��̼� �������� ������ �������� �����ϴ� �̹��� ����

    float mTimeInterval = 0.1f;     //�ִϸ��̼� �������� �����Ӱ� �ð�
    int mTotalFramesCount = 0;      //�ִϸ��̼� �������� �� ������ ����

    int mCurFrameIndex = 0;         //�����߿� ���� ������ ��ȣ

    float mAniTime = 0.0f;          //�ִϸ��̼� ���� �ð�(ƽ)



    //
    ANI_PO mPlayOption = ANI_PO::LOOP;

    ANI_SO mSpriteOption = ANI_SO::FRAME_FILE;


    //�����ӵ��� �ʺ�, ����
    int mSpriteWidth = 0;
    int mSpriteHeight = 0;

    int mRow = 0;
    int mCol = 0;

    int mFrameCOL = 0;
};

