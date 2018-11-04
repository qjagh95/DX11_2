#pragma once
#include "stdafx.h"

JEONG_BEGIN

class JEONG_DLL Thread
{
public:
	bool Init();
	void Wait();
	void Awake();
	virtual void Run() = 0;

	static unsigned int ThreadFunc(void* Arg);

private:
	//stl쓰레드로 바꿈.
	thread m_Thread;
	HANDLE m_Start;

protected:
	Thread();

public:
	virtual ~Thread() = 0;

public:
	friend class ThreadManager;
};

JEONG_END

