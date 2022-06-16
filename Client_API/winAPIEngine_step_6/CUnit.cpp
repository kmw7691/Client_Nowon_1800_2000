#include "CUnit.h"
#include "CAPIEngine.h"

// �ʱ�ȭ����� �̿��Ͽ� �ʱ�ȭ��
CUnit::CUnit() : mX(400.0f), mY(500.0f), mRadius(30.0f)
{

}

CUnit::~CUnit()
{

}

void CUnit::Render(CAPIEngine* tpEngine)
{
	tpEngine->DrawCircle(mX, mY, mRadius);
}
