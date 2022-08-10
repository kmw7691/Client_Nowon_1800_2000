#pragma once


#include <math.h>
#include <cfloat> //앱실론 을 위해서
using namespace std;


/*
	2D Vector

	벡터의 덧셈(뺄셈)
	벡터의 스칼라곱

*/

//class SVector2D
struct SVector2D
{
	float mX = 0.0f;
	float mY = 0.0f;

	//생성자
	SVector2D() :
		mX(0.0f),
		mY(0.0f)
	{

	}
	//매개변수 있는 생성자
	SVector2D(float tX, float tY) :
		mX(tX),
		mY(tY)
	{

	}
	//복사 생성자
	SVector2D(const SVector2D& tVector2D)
	{
		mX = tVector2D.mX;
		mY = tVector2D.mY;
	}



	//연산자 오버로딩

	////복사 대입 연산자
	//void operator=(const SVector2D& tVector2D)
	//{
	//	mX = tVector2D.mX;
	//	mY = tVector2D.mY;
	//}
	////벡터의 덧셈
	//SVector2D operator+(const SVector2D& tVector2D)
	//{
	//	SVector2D tResult;

	//	tResult.mX = mX + tVector2D.mX;
	//	tResult.mY = mY + tVector2D.mY;

	//	return tResult;
	//}
	//SVector2D operator-(const SVector2D& tVector2D)
	//{
	//	SVector2D tResult;

	//	tResult.mX = mX - tVector2D.mX;
	//	tResult.mY = mY - tVector2D.mY;

	//	return tResult;
	//}

	////벡터의 스칼라곱
	//SVector2D operator*(const float tScalar)
	//{
	//	SVector2D tResult;

	//	tResult.mX = mX * tScalar;
	//	tResult.mY = mY * tScalar;

	//	return tResult;
	//}
    
    // 
    //DOT PRODUCT 내적
    float Dot(const SVector2D& tOther) const
    {
        return (mX * tOther.mX) + (mY * tOther.mY);
    }

    //CROSS PRODUCT 외적
    //책에는 이렇게 외적이라고 나오지만,  정확히 얘기하면 이것은 틀린 얘기이다.
    //임의의 스칼라 값(2by2 행렬의 행렬식의 값과 같을 것이다) 정도가 적당하겠다.
    float Determinent(const SVector2D& tOther) const
    {
        return (mX * tOther.mY) - (mY * tOther.mX);
    }

    float Length() const
    {
        return sqrt(Dot(*this));
        //for windows os
        //return std::sqrt(Dot(*this));
    }

    float Distance(const SVector2D& tOther) const
    {
        return (*this - tOther).Length();
    }


    SVector2D Normalize() const
    {
        const float tLength = Length();

        //for windows os
        if (tLength < FLT_EPSILON)
        //if (tLength < __FLT_EPSILON__)
        {
            return SVector2D::ZERO;
        }

        return *this / tLength;
    }

    bool IsZero() const
    {
        return *this == SVector2D::ZERO;
    }

    SVector2D& operator+=(const SVector2D& tOther)
    {
        return *this = *this + tOther;
    }

    SVector2D& operator-=(const SVector2D& tOther)
    {
        return *this = *this - tOther;
    }

    SVector2D& operator*=(float tScalar)
    {
        return *this = *this * tScalar;
    }

    SVector2D& operator/=(float tScalar)
    {
        return *this = *this / tScalar;
    }

    const SVector2D operator+(const SVector2D& tOther) const
    {
        return SVector2D(mX + tOther.mX, mY + tOther.mY);
    }

    const SVector2D operator-(const SVector2D& tOther) const
    {
        return SVector2D(mX - tOther.mX, mY - tOther.mY);
    }

    const SVector2D operator*(float tScalar) const
    {
        return SVector2D(mX * tScalar, mY * tScalar);
    }
    const SVector2D operator/(float tScalar) const
    {
        return SVector2D(mX / tScalar, mY / tScalar);
    }

    const SVector2D operator-() const
    {
        return SVector2D(-mX, -mY);
    }

    bool operator==(const SVector2D& tOther) const
    {
        return (mX == tOther.mX) && (mY == tOther.mY);
    }

    bool operator!=(const SVector2D& tOther) const
    {
        return !(*this == tOther);
    }

    bool operator<(const SVector2D& tOther) const
    {
        if (mX != tOther.mX)
        {
            return mX < tOther.mX;
        }

        if (mY != tOther.mY)
        {
            return mY < tOther.mY;
        }

        return false;
    }


    static const SVector2D ZERO;
    static const SVector2D LEFT;
    static const SVector2D RIGHT;
    static const SVector2D DOWN;
    static const SVector2D UP;

};

