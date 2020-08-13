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

#pragma once

#include <AzCore/std/string/string_view.h>

namespace AZ
{
    class ReflectContext;
}

namespace GraphicsReflectContext
{
    //! Provides reflection for environment controls
    class TimeOfDay
    {
    public:
        AZ_TYPE_INFO(TimeOfDay, "{4DBE4E73-196D-4DD6-8627-0693BD3072CE}");

        static void Reflect(AZ::ReflectContext* context);

    private:
        static void SetTime(float time, bool forceUpdate);
        static float GetTime();
        static void SetSpeed(float speed);
        static float GetSpeed();
        static bool LoadDefinitionFile(AZStd::string_view fileName);

    };
}
