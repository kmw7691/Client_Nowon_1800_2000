// api_ga_floodfill.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
//스택 자료구조를 사용하겠다(셀의 위치값 기억용도)
#include <stack>
using namespace std;

/*
* 플러드필 알고리즘
* 
* 색칠하기 알고리즘.
* 속도가 너무 느려 색칠하기알고리즘으로 쓰이지는 않고 
* 응용하여 보드게임의 여러 알고리즘으로 쓰인다
*/

#define MAX_ROW 6
#define MAX_COL 6


//행과 열(위치값)을 기억시켜두는 자료구조
stack<int> mIntStack;


// 6x6 board
//0: 빈곳, 1: 칠한곳, 2:벽(경계)
int mGrid[MAX_ROW][MAX_COL] =
{
    2,2,2,2,2,2,
    2,0,0,0,0,2,
    2,0,0,0,0,2,
    2,2,2,2,2,2,
    2,0,0,0,0,2,
    2,2,2,2,2,2,
};



void DoFloodFill(int tCol, int tRow);

void DoFloodFillNoRecursion(int tCol, int tRow);

void DisPlayGrid();

int main()
{
    cout << "before" << endl;
    DisPlayGrid();

    cout << endl;
    //DoFloodFill(2, 1);
    DoFloodFillNoRecursion(1, 4);

    cout << "after" << endl;
    DisPlayGrid();

    return 0;
}


void DoFloodFill(int tCol, int tRow)
{
    if (1 == mGrid[tRow][tCol] || 2 == mGrid[tRow][tCol])
    {
        //색을 칠하지않고 그냥둔다 (암것도 안한다)
        return;
    }

    else
    {
        //칠한다
        mGrid[tRow][tCol] = 1;

        DoFloodFill(tCol - 1, tRow); //좌
        DoFloodFill(tCol + 1, tRow); //우
        DoFloodFill(tCol, tRow - 1); //상
        DoFloodFill(tCol, tRow + 1); //하
    }
}


void DoFloodFillNoRecursion(int tCol, int tRow)
{
    while (!mIntStack.empty())
    {
        mIntStack.pop();
    }


    //floodfill
    //맨 처음 시드셀의 위치를 자료구조에 담는다
    mIntStack.push(tCol);
    mIntStack.push(tRow);


    while ( !mIntStack.empty())
    {
        tRow = mIntStack.top();
        mIntStack.pop();

        tCol = mIntStack.top();
        mIntStack.pop();

        if (1 == mGrid[tRow][tCol] || 2 == mGrid[tRow][tCol])
        {
            continue;
        }

        //칠한다
        mGrid[tRow][tCol] = 1;

        //좌
        mIntStack.push(tCol - 1);
        mIntStack.push(tRow);

        //우
        mIntStack.push(tCol + 1);
        mIntStack.push(tRow);


        //상
        mIntStack.push(tCol);
        mIntStack.push(tRow - 1);

        //하
        mIntStack.push(tCol);
        mIntStack.push(tRow + 1);
    }
}

void DisPlayGrid()
{
    int tRow = 0;
    int tCol = 0;

    string tString = "";
    char tszTemp[256] = {};

    for (tRow = 0; tRow < MAX_ROW; tRow++)
    {
        for (tCol = 0; tCol < MAX_COL; tCol++)
        {
            sprintf_s(tszTemp, "%d", mGrid[tRow][tCol]);

            tString = tString + tszTemp;
        }

        tString = tString + "\n";
    }

    cout << tString;
}

