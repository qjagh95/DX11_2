#pragma once
#include "stdafx.h"

JEONG_BEGIN

class JEONG_DLL Thread
{
public:
	bool Init();
	virtual void Run() = 0;

	static unsigned int ThreadFunc(void* Arg);

private:
	thread* m_Thread;

protected:
	Thread();
	virtual ~Thread() = 0;

public:
	friend class ThreadManager;
};

JEONG_END

