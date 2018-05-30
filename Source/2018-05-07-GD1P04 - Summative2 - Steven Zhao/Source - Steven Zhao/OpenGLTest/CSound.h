//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2017 Media Design School
//
// File Name	:	CSound.h
// Description	:	header file outlining the CSound
// Author		:	Steven Zhao
// Mail			:	steven.zha7447@mediadesign.school.nz
//

#pragma once

#ifndef _CSOUND_H__
#define _CSOUND_H__

// Library Includes //
#include "FMOD\fmod.hpp"
#include <memory>
// Local Includes //

// Types //

// Constants //

// Prototypes //

class CSound
{
    // Member Functions //
public:
	static CSound* GetInstance();
	static void DestroyInstance();
	bool init();
	const bool addSound();
	FMOD::System * soundMgr;
	//Spliting different Channels
	FMOD::Sound* bgMusic;
	FMOD::Sound* sfx;
	FMOD::Channel* BgMusicChannel;
	FMOD::Channel* soundEffects;
private:
	

	CSound();
	~CSound();
	static CSound* pSound;
	CSound(CSound const&) = delete; //Deletes copy constructor
	void operator = (CSound const&) = delete; //Deletes the operator assgined to the copy constructor

};

#endif // _CSOUND_H__

