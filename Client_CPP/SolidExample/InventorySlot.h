#pragma once

#include "IPointerHandler.h"

class InventorySlot:
	public IPointerHandler
{
private:
	void Pick();
	void Dragging();
	void Drop();

	void OnPointerDown();
	void OnPointerUp();
	void OnPointerClick();
	void OnPointerDrag();
};
