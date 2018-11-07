#pragma once
#include "stdafx.h"

JEONG_BEGIN
class UICon_Com;
class IconSlot_Com;
class JEONG_DLL SlotManager
{
private:
	vector<IconSlot_Com*> m_SlotVector;

public:
	void PushSlotVector(IconSlot_Com* _pSlot);
	void ReleaseFromIndex(int _index);
	void SetFromIndex(int _index , UICon_Com* _pIcon);
	IconSlot_Com* GetIndexFromslot(int _index) const;
public:
	CLASS_IN_SINGLE(SlotManager)
};

JEONG_END