#include "stdafx.h"
#include "Thread.h"

JEONG_USING

Thread::Thread()
{
}

Thread::~Thread()
{
	m_Thread.join();
}

bool Thread::Init()
{
	m_Start = CreateEvent(NULLPTR, FALSE, FALSE, NULLPTR);
	m_Thread = thread(&Thread::ThreadFunc, this);

	return true;
}

void Thread::Wait()
{
	//동기화 함수. 완료될때까지 무한대기.
	WaitForSingleObject(m_Start, INFINITE);
}

void Thread::Awake()
{
	SetEvent(m_Start);
}

unsigned int Thread::ThreadFunc(void * Arg)
{
	Thread* getThread = (Thread*)Arg;
	getThread->Wait();
	getThread->Run();

	return 0;
}
