#ifndef _FRAMEPERSECOND_H_
#define _FRAMEPERSECOND_H_

#include <ctime>

class FramePerSecond
{
public:
	FramePerSecond();
	~FramePerSecond();

	double GetFPS();

private:
	float fFrames;
	float fCurrentTime;
	float fLastUpdateTime;
	float fElapsedTime;

	double dTime;

private:
	void Calculate();

};

#endif