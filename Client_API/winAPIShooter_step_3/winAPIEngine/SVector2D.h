#pragma once
#include <math.h>
#include <cfloat> // 앱실론(극히 작은 수)을 위해서 사용
using namespace std;

struct SVector2D
{
	// 2차원

	float mX = 0.0f;
	float mY = 0.0f;

	SVector2D():mX(0.0f),mY(0.0f)
	{
	}
	~SVector2D()
	{
	}

	SVector2D(float tX, float tY) :mX(tX), mY(tY)
	{
	}

	SVector2D(const SVector2D& tVector2D) :mX(0.0f), mY(0.0f)
	{
		mX = tVector2D.mX;
		mY = tVector2D.mY;
	}

	//벡터의 연산

	/*void operator=(const SVector2D& tVector2D)
	{
		mX = tVector2D.mX;
		mY = tVector2D.mY;
	}*/

	//벡터끼리의 덧셈
	const SVector2D operator+(const SVector2D& tVector2D) const
	{
		SVector2D tResult;

		tResult.mX = mX + tVector2D.mX;
		tResult.mY = mY + tVector2D.mY;

		return tResult;
	}

	//벡터끼리의 뺄셈
	const SVector2D operator-(const SVector2D& tVector2D) const
	{
		SVector2D tResult;

		tResult.mX = mX - tVector2D.mX;
		tResult.mY = mY - tVector2D.mY;

		return tResult;
	}

	//리턴타입 앞에 const : 반환값 read only, 매개변수의 const매개변수 read only, 맨뒤에 멤버변수 read only
	//벡터의 스칼라곱
	const SVector2D operator*(const float tScalar) const
	{
		SVector2D tResult;

		tResult.mX = mX * tScalar;
		tResult.mY = mY * tScalar;

		return tResult;
	}


	//벡터의 스칼라곱(편의상 / 기호도 연산자 오버로딩)
	const SVector2D operator/(const float tScalar) const
	{
		SVector2D tResult;

		tResult.mX = mX / tScalar;
		tResult.mY = mY / tScalar;

		return tResult;
	}

	// 반대방향
	const SVector2D operator-() const
	{
		return SVector2D(-mX, -mY);
	}


	/////////////////////////////////////////////

	SVector2D& operator+=(const SVector2D& tOther)
	{
		return *this = *this + tOther;
	}


	SVector2D& operator-=(const SVector2D& tOther)
	{
		return *this = *this - tOther;
	}


	SVector2D& operator *= (float tScalar)
	{
		return *this = *this * tScalar;
	}


	SVector2D& operator /= (float tScalar)
	{
		return *this = *this / tScalar;
	}

	
	/////////////////////////////////////////



	//비교연산자
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


	//Dot product 내적
	float Dot(const SVector2D& tOther) const
	{
		return (mX * tOther.mX) + (mY * tOther.mY);
	}


	//Cross Product 외적
	//책에는 이렇게 외적이라고 나오지만, 정확히 얘기하면 틀린얘기임
	// 임의의 스칼라값(2x2 행렬의 행렬식값과 같을것) 정도가 적당함
	float Determinent(const SVector2D& tOther) const
	{
		return (mX * tOther.mY) - (mY * tOther.mX);
	}


	float Length() const
	{
		// return sqrt(Dot(*this));
		//for windows os
		return sqrt(Dot(*this));
	}


	float Distance(const SVector2D& tOther) const
	{
		return (*this - tOther).Length();
	}


	//정규화 : 크기가 1인 벡터로 만든다
	SVector2D Normalize() const
	{
		const float tLength = Length();

		//for windows os
		if (tLength < FLT_EPSILON)
		{
			//return SVector2D::ZERO;
		}

		return *this / tLength; //크기분의 1을 스칼라곱 하였다
	}


	
	static const SVector2D ZERO;
	static const SVector2D LEFT;
	static const SVector2D RIGHT;
	static const SVector2D DOWN;
	static const SVector2D UP;
};

