#pragma once

// 인터페이스
// 기능에대한 정의는 없으면서
// 자식클래스가 해당기능을 추가하도록 해주는 기능을 구현한것을 인터페이스라고 한다
class ITwoLeggedWalker
{
public:
	virtual void TwoLeggedWalk() = 0;
};

