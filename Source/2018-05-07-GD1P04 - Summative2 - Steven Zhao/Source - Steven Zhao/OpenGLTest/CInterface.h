 //
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2017 Media Design School
//
// File Name	:	CInterface.h
// Description	:	header file outlining the CInterface
// Author		:	Steven Zhao
// Mail			:	steven.zha7447@mediadesign.school.nz
//

#pragma once

#ifndef _CINTERFACE_H__
#define _CINTERFACE_H__

// Library Includes //

// Local Includes //
#include <time.h>
#include "TextLabel.h"

// Types //

// Constants //

// Prototypes //
class TextLabel;
class CInterface 
{
    // Member Functions //
        public:
			static CInterface* InstanceGet();
			static void InstanceDestroy();
			int FPSInSecond();
			void update();
			void render();
			bool bWon = false;
			TextLabel label;
			TextLabel WinText;
			TextLabel LostText;
			int FPSCounter = 0;
        private:
			CInterface();
			~CInterface();
			static CInterface* pInterface;
			CInterface(CInterface const&) = delete; //Deletes copy constructor
			void operator = (CInterface const&) = delete; //Deletes the operator assigned to the copy constructor
};

#endif // _CINTERFACE_H__

