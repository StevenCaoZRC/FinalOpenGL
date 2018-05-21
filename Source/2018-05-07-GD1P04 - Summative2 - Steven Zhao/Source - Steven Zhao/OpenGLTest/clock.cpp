//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name     : clock.cpp
// Author        : Steven Zhao
// Mail          : steven.zha7447mediadesign.school.nz
//
// Library Includes
#include <chrono>


// Local Includes

// This Includes
#include "clock.h"

// Static Variables

// Static Function Prototypes

// Implementation
//****************************************************
// CClock: CClock Class Constructor
// @author: 
// @parameter: No parameters
//
// @return: none
//*****************************************************
CClock::CClock()
	: m_fTimeElapsed(0.0f)
	, m_fDeltaTime(0.0f)
{

}

//****************************************************
// ~CClock: CClock Class Destructor
// @author: 
// @parameter: No parameters
//
// @return: none
//*****************************************************
CClock::~CClock()
{

}

CClock * CClock::InstanceGet()
{
	if (!pClock) // If this does not exist
	{
		pClock = new CClock(); //Create an instance of SceneManager
	}
	return pClock;
}

void CClock::InstanceDestroy()
{
	if (pClock) //If the instance exists
	{
		delete pClock;	//Delete instance
		pClock = nullptr;//Set the pointer to nullptr
	}
}

//****************************************************
// Initialise: CClock Class Initialiser - sets the first time values
// @author: 
// @parameter: No parameters
//
// @return: true if initialisation is successful, false if not
//*****************************************************
bool CClock::Initialise()
{
	m_fCurrentTime = std::chrono::high_resolution_clock::now();
	return (true);
}

//****************************************************
// Process: processes the change in time since it was last called
// @author:
// @parameter: No parameters
//
// @return: void
//*****************************************************
void
CClock::Process()
{
	m_fLastTime = m_fCurrentTime;

	m_fCurrentTime = std::chrono::high_resolution_clock::now();

	
	m_fDeltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(m_fCurrentTime - m_fLastTime).count();

	m_fTimeElapsed += m_fDeltaTime;
}

//****************************************************
// GetDeltaTick: gets the current delta tick value
// @author: 
// @parameter: No parameters
//
// @return: the current delta tick value
//*****************************************************
float CClock::GetDeltaTick()
{
	return (m_fDeltaTime);
}