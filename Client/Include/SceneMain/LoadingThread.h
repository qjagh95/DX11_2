#pragma once

#include "Thread.h"

JEONG_USING

class LoadingThread : public Thread
{
public:
	LoadingThread();
	~LoadingThread();

public:
	void Run() override;
};

