#include "CObjectRyu.h"

#include "CAPIEngine.h"

CObjectRyu::CObjectRyu() :
	CRef(), mPosition()//,  mVelocity()
{

}
CObjectRyu::~CObjectRyu()
{

}

void CObjectRyu::SetEngine(CAPIEngine* tpEngine)
{
	mpEngine = tpEngine;
}
