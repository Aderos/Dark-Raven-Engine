#include "FramePerSecond.h"

FramePerSecond::FramePerSecond()
{
	this->fCurrentTime = 0;
	this->fElapsedTime = 0;
	this->fFrames = 0;
	this->fLastUpdateTime = 0;
	this->dTime = 0;
}

FramePerSecond::~FramePerSecond()
{

}

double FramePerSecond::GetFPS()
{
	Calculate();
	return this->dTime;
}

void FramePerSecond::Calculate()
{
	this->fFrames++;
	this->fCurrentTime = (float)clock();
	this->fElapsedTime = fCurrentTime - fLastUpdateTime;

	if (fElapsedTime >= 1000)
	{
		this->dTime = (fFrames * 1000.0) / fElapsedTime;
		this->fFrames = 0;
		this->fLastUpdateTime = fCurrentTime;
	}
}