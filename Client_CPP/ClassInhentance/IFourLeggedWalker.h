#pragma once
// abstract : 가상클래스라는것을 명시하는 키워드
// 순수가상함수가 하나이상 있으면 해당 키워드 안붙여도 가상클래스가 됨
class IFourLeggedWalker abstract
{
public:
	virtual void FourLeggedWalk() = 0;
};

