/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/
// Original file Copyright Crytek GMBH or its affiliates, used under license.

#include "pch.h"
#include "stdafx.h"
#include "FeatureTest.h"
#include "Serialization.h"
#include "CharacterDocument.h"
#include <ICryAnimation.h>

namespace CharacterTool {
    struct FeatureTestWeaponSwitch
        : IFeatureTest
    {
        string spineBone;
        string weaponBone;

        string leftWeaponAttachment;
        string rightWeaponAttachment;
        string weaponAttachment;

        FeatureTestWeaponSwitch()
            : spineBone("Bip01 Spine2")
            , weaponBone("weapon_bone")
            , leftWeaponAttachment("riflepos01")
            , rightWeaponAttachment("riflepos02")
            , weaponAttachment("weapon")
        {
        }

        void Serialize(IArchive& ar) override
        {
            ar(JointName(spineBone), "spineBone", "Spine Joint");
            ar(JointName(weaponBone), "weaponBone", "Weapon Bone");

            ar(AttachmentName(leftWeaponAttachment), "leftWeaponAttachment", "Left Weapon Attachment");
            ar(AttachmentName(rightWeaponAttachment), "rightWeaponAttachment", "Right Weapon Attachment");
            ar(AttachmentName(weaponAttachment), "weaponAttachment", "Weapon Attachment");
        }

        void Render(const SRenderContext& x, CharacterDocument* document) override
        {
        }

        bool AnimEvent(const AnimEventInstance& event, CharacterDocument* document) override
        {
            ICharacterInstance* pInstance = document->CompressedCharacter();
            if (!pInstance)
            {
                return false;
            }

            ISkeletonPose& skeletonPose = *pInstance->GetISkeletonPose();
            IDefaultSkeleton& defaultSkeleton = pInstance->GetIDefaultSkeleton();
            IAttachmentManager* pIAttachmentManager = pInstance->GetIAttachmentManager();
            IAttachment* pSAtt1 = pIAttachmentManager->GetInterfaceByName(leftWeaponAttachment.c_str());
            if (!pSAtt1)
            {
                return false;
            }
            IAttachment* pSAtt2 = pIAttachmentManager->GetInterfaceByName(rightWeaponAttachment.c_str());
            if (!pSAtt2)
            {
                return false;
            }
            IAttachment* pWAtt = pIAttachmentManager->GetInterfaceByName(weaponAttachment.c_str());
            if (!pWAtt)
            {
                return false;
            }

            int32 nWeaponIdx    =   defaultSkeleton.GetJointIDByName(weaponBone.c_str());
            int32 nSpine2Idx    =   defaultSkeleton.GetJointIDByName(spineBone.c_str());
            if (nWeaponIdx < 0)
            {
                return false;
            }
            if (nSpine2Idx < 0)
            {
                return false;
            }

            QuatT absWeaponBone         = skeletonPose.GetAbsJointByID(nWeaponIdx);
            QuatT absSpine2                 = skeletonPose.GetAbsJointByID(nSpine2Idx);
            QuatT defSpine2               = defaultSkeleton.GetDefaultAbsJointByID(nSpine2Idx);

            QuatT AttachmentLocation        = defSpine2 * (absSpine2.GetInverted() * absWeaponBone);

            if (event.m_EventName && azstricmp(event.m_EventName, "WeaponDrawRight") == 0)
            {
                pSAtt1->HideAttachment(1); //hide
                pSAtt2->HideAttachment(0); //show
                pWAtt->HideAttachment(0); //show
                return true;
            }
            else if (event.m_EventName && azstricmp(event.m_EventName, "WeaponDrawLeft") == 0)
            {
                pSAtt1->HideAttachment(0);
                pSAtt2->HideAttachment(1);
                pWAtt->HideAttachment(0); //show
                return true;
            }
            return false;
        }
    };

    SERIALIZATION_CLASS_NAME(IFeatureTest, FeatureTestWeaponSwitch, "WeaponSwitch", "Weapon Switch Example")
}
