// 
// Online Game Cheats Client.dll hook
// Copyright (c) system   2001-2002
// Copyright (c) bunny771 2001-2002
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
// 
// NOTE:
// GNU license doesn't cover Engine directory.
// Content of Engine directory is copyrighted (c) 1999, 2000, by Valve LLC
// and it is licensed under Valve's proprietary license (see original HL SDK).
// 

#include "stdafx.h"
#include "timehandling.h"
//#include "units/antidebug.h"
#include <Windows.h>

//========================================================================================
float  ClientTime::mapTime    = 1;
double ClientTime::current    = 1;
unsigned int ClientTime::current_ms = 1;

//===========================================================
void ClientTime::reportMapTime(float mapTimeNew)
{
	// map change detection
	if( mapTimeNew < mapTime-10 ) // time decreased (looks like a mapchange)
	{
		//void AtMapChange();
		//AtMapChange();
	}
	mapTime = mapTimeNew;
	updateCurrentTime();
}

//========================================================================================
void ClientTime::updateCurrentTime()
{
	// timer update
	current_ms = timeGetTime();

	//void Con_Echo(const char *fmt, ... );
	current = (double)current_ms / 1000.0;
	//Con_Echo("cur_ms:%d cur:%f",current_ms,current);
}
