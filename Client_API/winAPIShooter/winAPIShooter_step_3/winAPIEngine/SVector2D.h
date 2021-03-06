#pragma once
#include <math.h>
#include <cfloat> // ?۽Ƿ?(???? ???? ??)?? ???ؼ? ????
using namespace std;

struct SVector2D
{
	// 2????

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

	//?????? ????

	/*void operator=(const SVector2D& tVector2D)
	{
		mX = tVector2D.mX;
		mY = tVector2D.mY;
	}*/

	//???ͳ????? ????
	const SVector2D operator+(const SVector2D& tVector2D) const
	{
		SVector2D tResult;

		tResult.mX = mX + tVector2D.mX;
		tResult.mY = mY + tVector2D.mY;

		return tResult;
	}

	//???ͳ????? ????
	const SVector2D operator-(const SVector2D& tVector2D) const
	{
		SVector2D tResult;

		tResult.mX = mX - tVector2D.mX;
		tResult.mY = mY - tVector2D.mY;

		return tResult;
	}

	//????Ÿ?? ?տ? const : ??ȯ?? read only, ?Ű??????? const?Ű????? read only, ?ǵڿ? ???????? read only
	//?????? ??Į????
	const SVector2D operator*(const float tScalar) const
	{
		SVector2D tResult;

		tResult.mX = mX * tScalar;
		tResult.mY = mY * tScalar;

		return tResult;
	}


	//?????? ??Į????(???ǻ? / ??ȣ?? ?????? ?????ε?)
	const SVector2D operator/(const float tScalar) const
	{
		SVector2D tResult;

		tResult.mX = mX / tScalar;
		tResult.mY = mY / tScalar;

		return tResult;
	}

	// ?ݴ?????
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



	//?񱳿?????
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


	//Dot product ????
	float Dot(const SVector2D& tOther) const
	{
		return (mX * tOther.mX) + (mY * tOther.mY);
	}


	//Cross Product ????
	//å???? ?̷??? ?????̶??? ????????, ??Ȯ?? ?????ϸ? Ʋ????????
	// ?????? ??Į????(2x2 ?????? ???Ľİ??? ??????) ?????? ??????
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


	//????ȭ : ũ?Ⱑ 1?? ???ͷ? ??????
	SVector2D Normalize() const
	{
		const float tLength = Length();

		//for windows os
		if (tLength < FLT_EPSILON)
		{
			//return SVector2D::ZERO;
		}

		return *this / tLength; //ũ?????? 1?? ??Į???? ?Ͽ???
	}


	
	static const SVector2D ZERO;
	static const SVector2D LEFT;
	static const SVector2D RIGHT;
	static const SVector2D DOWN;
	static const SVector2D UP;
};

