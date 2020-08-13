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
#include "Platform.h"
#include "DemoBGM.h"
#include <AK/SoundEngine/Common/AkSoundEngine.h>    // Sound engine
#include "../WwiseProject/GeneratedSoundBanks/Wwise_IDs.h"		// IDs generated by Wwise

#define GAME_OBJECT_MUSIC 10

#if defined AK_XBOXONE || defined AK_PS4
#define INTEGRATIONDEMO_DVR_SUPPORTED
#endif

/// DemoBGMusic class constructor
DemoBGMusic::DemoBGMusic( Menu& in_ParentMenu ) : Page( in_ParentMenu, "Background Music Demo" )
{
	m_szHelp  = "This demo shows how to setup the background music so the DVR doesn't record it. "
		"This is necessary on platforms that support recording features (DVR) and have a TCR to enforce the proper use of licensed music. "
		"Both streams will be muted when the OS-provided music player starts.";
}

/// Initializes the demo.
/// \return True if successful and False otherwise.
bool DemoBGMusic::Init()
{
	AkBankID bankID; // Not used
	if ( AK::SoundEngine::LoadBank( "BGM.bnk", AK_DEFAULT_POOL_ID, bankID ) != AK_Success )
	{
		SetLoadFileErrorMessage( "BGM.bnk" );
		return false;
	}

	//Add a secondary output tied to the Non-recordable endpoint of the console.  Supported only on PS4 and XB1
#if defined INTEGRATIONDEMO_DVR_SUPPORTED
	AkOutputSettings outputSettings("DVR_Bypass");		
	AK::SoundEngine::AddOutput(outputSettings, &m_idBGMOutput);
#endif
	// In order to show the difference between a recordable sound and a non-recordable sound, let's set up 2 game objects.
	// Register the "Recordable music object" game object.  
	AK::SoundEngine::RegisterGameObj( GAME_OBJECT_MUSIC, "Recordable music" );	
	
	m_bPlayLicensed = false;
	m_bPlayCopyright = false;

	// Initialize the page
	return Page::Init();
}

/// Releases resources used by the demo.
void DemoBGMusic::Release()
{
	AK::SoundEngine::UnregisterGameObj(GAME_OBJECT_MUSIC);	
	AK::SoundEngine::UnloadBank("BGM.bnk", NULL);

#if defined INTEGRATIONDEMO_DVR_SUPPORTED
	AK::SoundEngine::RemoveOutput(m_idBGMOutput);
#endif
}

void DemoBGMusic::InitControls()
{
	//UI stuff.
	ButtonControl* newBtn;

	newBtn = new ButtonControl( *this );
	newBtn->SetLabel( "Play recordable music" );
	newBtn->SetDelegate( (PageMFP)&DemoBGMusic::Recordable_Pressed );
	m_Controls.push_back( newBtn );

	newBtn = new ButtonControl( *this );
	newBtn->SetLabel( "Play non-recordable music" );
	newBtn->SetDelegate( (PageMFP)&DemoBGMusic::NonRecordable_Pressed );
	m_Controls.push_back( newBtn );
}

void DemoBGMusic::Recordable_Pressed( void*sender, ControlEvent* )
{
	if (m_bPlayLicensed)
	{
		AK::SoundEngine::StopAll(GAME_OBJECT_MUSIC);
		m_bPlayLicensed = false;
		((ButtonControl*)sender)->SetLabel( "Play recordable music" );
	}
	else
	{
		// Plays the music on the game object linked to the main output.
		AK::SoundEngine::PostEvent("Play_RecordableMusic", GAME_OBJECT_MUSIC);
		m_bPlayLicensed = true;
		((ButtonControl*)sender)->SetLabel( "Stop" );
	}
}

void DemoBGMusic::NonRecordable_Pressed( void*sender, ControlEvent*)
{
	if (m_bPlayCopyright)
	{
		AK::SoundEngine::StopAll(GAME_OBJECT_MUSIC);
		m_bPlayCopyright = false;
		((ButtonControl*)sender)->SetLabel( "Play non-recordable music" );
	}
	else
	{
		// Plays the non-recordable music on the game object linked to the listener that outputs on the BGM end-point.
		AK::SoundEngine::PostEvent("Play_NonRecordableMusic", GAME_OBJECT_MUSIC);
		m_bPlayCopyright = true;
		((ButtonControl*)sender)->SetLabel( "Stop" );
	}
}

void DemoBGMusic::Draw()
{
	Page::Draw();
	DrawTextOnScreen(m_szHelp.c_str(), 70, 300, DrawStyle_Text);
}

