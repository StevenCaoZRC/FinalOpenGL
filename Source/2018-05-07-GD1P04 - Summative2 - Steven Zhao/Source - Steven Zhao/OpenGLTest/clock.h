

#pragma once

#ifndef _CLOCK_H_
#define _CLOCK_H_

// Library Includes
#include <chrono>
#include <vector>

// Local Includes

// Types

// Constants

// Prototypes
class CClock
{
	// Member Functions
public:
	static CClock* InstanceGet();
	static void InstanceDestroy();

	bool Initialise();
	void Process();
	float GetDeltaTick();

protected:

private:
	CClock();
	~CClock();
	static CClock* pClock;
	CClock(const CClock&) = delete;
	CClock& operator= (const CClock&) = delete;

	// Member Variables
public:

protected:
	double m_fTimeElapsed;
	double m_fDeltaTime;
	std::chrono::high_resolution_clock::time_point m_fLastTime;
	std::chrono::high_resolution_clock::time_point m_fCurrentTime;

	std::vector<double> m_vecTimeHistory;

	long long m_llNumCounts;

private:

};
#endif // 
