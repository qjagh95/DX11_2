#pragma once

#include "Thread.h"

JEONG_USING

class LoadingThread : public Thread
{
public:
	void Run() override;

	void SetLoadingMaxCount(int Value) { m_LoadingMaxCount = Value; }
	void AddLoadingCount();
	int GetLoadingCount() const;
	int GetLoadingMaxCount() const { return m_LoadingMaxCount; }

	float GetPersent() const;

private:
	int m_LoadingCount;
	int m_LoadingMaxCount;

public:
	LoadingThread();
	~LoadingThread();
};

