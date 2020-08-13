/*******************************************************************************
The content of this file includes portions of the AUDIOKINETIC Wwise Technology
released in source code form as part of the SDK installer package.

Commercial License Usage

Licensees holding valid commercial licenses to the AUDIOKINETIC Wwise Technology
may use this file in accordance with the end user license agreement provided 
with the software or, alternatively, in accordance with the terms contained in a
written agreement between you and Audiokinetic Inc.

  Version: v2017.2.9  Build: 6726
  Copyright (c) 2006-2019 Audiokinetic Inc.
*******************************************************************************/

#include "stdafx.h"
#include "SoundInputMgr.h"
#include "SoundInput.h"

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// SoundInputMgr implementation
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
SoundInputMgrBase& SoundInputMgr::Instance()
{
	static SoundInputMgr Singleton;
	return Singleton;
}

bool SoundInputMgr::Initialize()
{
	return SoundInputMgrBase::Initialize();
}

void SoundInputMgr::Term()
{
	SoundInputMgrBase::Term();
}
