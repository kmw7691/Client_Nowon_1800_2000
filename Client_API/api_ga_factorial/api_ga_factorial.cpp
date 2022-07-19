// api_ga_factorial.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
using namespace std;

//팩토리얼을 재귀호출을 이용하여 작성

//int factorial(int n)
//{
//   
//    if (n == 1)      // n이 1일 때
//        return 1;    // 1을 반환하고 재귀호출을 끝냄
//
//    return n * factorial(n - 1);    // n과 factorial 함수에 n - 1을 넣어서 반환된 값을 곱함
//}
//
//int main()
//{
//    printf("%d\n", factorial(5));
//
//    return 0;
//}



unsigned int DoFactorial(unsigned int tN);

unsigned int DoFactorialNoRecursion(unsigned int tN);

int main()
{
    unsigned int tResult = 0;
    tResult = DoFactorial(4);

    cout << tResult << endl;


    tResult = 0;
    tResult = DoFactorialNoRecursion(4);

    cout << tResult << endl;


    return 0;
}


unsigned int DoFactorial(unsigned int tN)
{
    if (0 == tN)
    {
        return 1;
    }

    else
    {
        return tN* DoFactorial(tN - 1);
    }
}


unsigned int DoFactorialNoRecursion(unsigned int tN)
{
    unsigned int tResult;

    if (0 == tN)
    {
        tResult = 1;
    }

    else
    {
        int tTemp = 1;

        int ti = 0;
        for (ti = tN; ti > 0; --ti)
        {
            tTemp = tTemp * ti;
        }

        tResult = tTemp;
    }

    return tResult;
}
