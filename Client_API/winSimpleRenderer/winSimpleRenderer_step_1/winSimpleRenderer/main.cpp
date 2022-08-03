﻿// winAPITraning00.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//



#include "framework.h"
#include <stack>
#include <list>
#include <vector>

using namespace std;

#pragma comment(lib, "winAPIEngine.lib")


// 3차원 공간에서ㅏ의 벡터와 점(위치)를 다루기위해 정의
struct SRyuVector3
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

//삼각형, 정점 세개로 만든 도형, 모델의 최소 기본단위
struct SRyuTriangle
{
    SRyuVector3 p[3];
};

//메쉬
struct SRyuMesh
{
    std::vector<SRyuTriangle> tris; // 삼각형들의 모음
};


class CRyuEngine : public CAPIEngine
{

public:
    CRyuEngine() {};
    virtual ~CRyuEngine() {};


    virtual void OnCreate() override
    {
        CAPIEngine::OnCreate();

    }
    virtual void OnDestroy() override
    {
       
        CAPIEngine::OnDestroy();
    }
    virtual void OnUpdate(float tDeltaTime) override
    {
        CAPIEngine::OnUpdate(tDeltaTime);

        //render
        this->Clear(0.1f, 0.1f, 0.3f);       
        

        SRyuMesh tMesh;
        tMesh.tris =
        {
            //CCW로 나열하였지만 윈도우 좌표계를 사용하고 있으므로 데카르트 좌표계에서는 CW
            {0.0f,0.0f,0.0f,                0.0f,1.0f,0.0f,                 1.0f,0.0f,0.0f},
            {1.0f,0.0f,0.0f,                0.0f,1.0f,0.0f,                 1.0f,1.0f,0.0f}
        };
      

        //스케일행렬
        float tScaleScalar = 100.0f;
        float tMatScale[4][4] = { 0 };

        tMatScale[0][0] = 1.0f * tScaleScalar;
        tMatScale[1][1] = 1.0f * tScaleScalar;
        tMatScale[2][2] = 1.0f * tScaleScalar;
        tMatScale[3][3] = 1.0f;


        //사각형에 스케일적용
        SRyuMesh tMeshScale;
        tMeshScale.tris =
        {
            {0.0f,0.0f,0.0f,                0.0f,0.0f,0.0f,                 0.0f,0.0f,0.0f},
            {0.0f,0.0f,0.0f,                0.0f,0.0f,0.0f,                 0.0f,0.0f,0.0f}
        };
        
        
        //벡터와 스케일변환 행렬을 곱함
        for (int ti = 0; ti < 2; ++ti)
        {
            MultiplyMatrixVectorRyu(tMesh.tris[ti].p[0], tMeshScale.tris[ti].p[0], tMatScale);
            MultiplyMatrixVectorRyu(tMesh.tris[ti].p[1], tMeshScale.tris[ti].p[1], tMatScale);
            MultiplyMatrixVectorRyu(tMesh.tris[ti].p[2], tMeshScale.tris[ti].p[2], tMatScale);
        }


        float tMatProj[4][4] = { 0 };

        tMatProj[0][0] = 1.0f;
        tMatProj[1][1] = 1.0f;
        tMatProj[2][2] = 1.0f;
        tMatProj[3][3] = 1.0f;


        SRyuMesh tMeshProj;
        tMeshProj.tris =
        {
            {0.0f,0.0f,0.0f,                0.0f,0.0f,0.0f,                 0.0f,0.0f,0.0f},
            {0.0f,0.0f,0.0f,                0.0f,0.0f,0.0f,                 0.0f,0.0f,0.0f}
        };

        int ti = 0;
        for (auto t : tMeshScale.tris)
        {
            MultiplyMatrixVectorRyu(t.p[0], tMeshProj.tris[ti].p[0], tMatProj);
            MultiplyMatrixVectorRyu(t.p[1], tMeshProj.tris[ti].p[1], tMatProj);
            MultiplyMatrixVectorRyu(t.p[2], tMeshProj.tris[ti].p[2], tMatProj);

            ti++;
        }


        for (auto t : tMeshProj.tris)
        {
            DrawTriangle(t.p[0].x, t.p[0].y,
                        t.p[1].x, t.p[1].y,
                        t.p[2].x, t.p[2].y);
        }


        this->Present();
    }

    void MultiplyMatrixVectorRyu(SRyuVector3& tIn, SRyuVector3& tOut, float tM[][4])
    {
        tOut.x = tIn.x * tM[0][0] + tIn.y * tM[1][0] + tIn.z * tM[2][0] + 1.0f * tM[3][0];
        tOut.y = tIn.x * tM[0][1] + tIn.y * tM[1][1] + tIn.z * tM[2][1] + 1.0f * tM[3][0];
        tOut.z = tIn.x * tM[0][2] + tIn.y * tM[1][2] + tIn.z * tM[2][2] + 1.0f * tM[3][0];

        float tW = tIn.x * tM[0][3] + tIn.y * tM[1][3] + tIn.z * tM[2][3] + 1.0f * tM[3][3];

        if (tW != 0.0f)
        {
            tOut.x = tOut.x / tW;
            tOut.y = tOut.y / tW;
            tOut.z = tOut.z / tW;
        }
    }





private:
    CRyuEngine(const CRyuEngine&) {};
    CRyuEngine& operator=(const CRyuEngine&) {};
};




///////////////////////////////////////////////////





int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    CRyuEngine tEngine;
    tEngine.Create(hInstance, nCmdShow);


    MSG msg = { 0 };

    msg = tEngine.Run();

    return (int) msg.wParam;
}
