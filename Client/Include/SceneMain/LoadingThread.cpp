#include "LoadingThread.h"

LoadingThread::LoadingThread()
{
}

LoadingThread::~LoadingThread()
{
}

void LoadingThread::Run()
{
	MessageBox(NULLPTR, L"LoadThread", L"LoadThread", MB_OK);
}	
