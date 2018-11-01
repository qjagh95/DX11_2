#include "Thread.h"

JEONG_USING

Thread::Thread()
{
}

Thread::~Thread()
{
	SAFE_DELETE(m_Thread);
}

bool Thread::Init()
{
	m_Thread = new thread(Thread::ThreadFunc, this);

	return true;
}

unsigned int Thread::ThreadFunc(void * Arg)
{
	Thread* getThread = (Thread*)Arg;
	getThread->Run();

	return 0;
}
