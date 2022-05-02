#pragma once

class IPointerHandler
{
public:
	virtual void OnPointerDown() = 0;
	virtual void OnPointerUp() = 0;
	virtual void OnPointerClick() = 0;
	virtual void OnPointerDrag() = 0;
};