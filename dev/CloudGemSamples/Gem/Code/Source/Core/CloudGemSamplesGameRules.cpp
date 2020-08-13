/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates, or 
* a third party where indicated.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,  
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  
*
*/

#include "StdAfx.h"
#include "CloudGemSamplesGameRules.h"
#include "IActorSystem.h"

namespace LYGame
{
    DECLARE_DEFAULT_COMPONENT_FACTORY(CloudGemSamplesGameRules, IGameRules)

    bool CloudGemSamplesGameRules::Init(IGameObject* pGameObject)
    {
        SetGameObject(pGameObject);
        if (!pGameObject->BindToNetwork())
        {
            return false;
        }

        if (gEnv == nullptr ||
            gEnv->pGame == nullptr ||
            gEnv->pGame->GetIGameFramework() == nullptr ||
            gEnv->pGame->GetIGameFramework()->GetIGameRulesSystem() == nullptr)
        {
            return false;
        }
        gEnv->pGame->GetIGameFramework()->GetIGameRulesSystem()->SetCurrentGameRules(this);

        return true;
    }

    void CloudGemSamplesGameRules::PostInit(IGameObject* pGameObject)
    {
        if (pGameObject != nullptr)
        {
            pGameObject->EnableUpdateSlot(this, 0);
            pGameObject->EnablePostUpdates(this);
        }
    }

    CloudGemSamplesGameRules::~CloudGemSamplesGameRules()
    {
        if (gEnv->pGame->GetIGameFramework()->GetIGameRulesSystem())
        {
            gEnv->pGame->GetIGameFramework()->GetIGameRulesSystem()->SetCurrentGameRules(nullptr);
        }
    }

    bool CloudGemSamplesGameRules::OnClientConnect(ChannelId channelId, bool isReset)
    {
        // This is where the actor for a player is created on starting / connecting to the game.
        Vec3 position(0, -5, 34); // Set position because rendering doesn't start until the camera leaves 0,0,0.
        auto pPlayerActor = gEnv->pGame->GetIGameFramework()->GetIActorSystem()->CreateActor(channelId, "Character", "Actor", position, Quat(Ang3(0, 0, 0)), Vec3(1, 1, 1));

        return true;
    }
}
