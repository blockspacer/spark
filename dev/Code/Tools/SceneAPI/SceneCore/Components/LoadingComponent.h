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

#include <AzCore/Component/Component.h>
#include <SceneAPI/SceneCore/SceneCoreConfiguration.h>
#include <SceneAPI/SceneCore/Events/CallProcessorBinder.h>

namespace AZ
{
    namespace SceneAPI
    {
        namespace SceneCore
        {
            // Loading components are small logic units that exist only during loading. Each of
            //      these components take care of a small piece of the loading process, allowing
            //      multiple components to use the same sources to collect data.
            //      Use the BindToCall from the CallProcessorBinder to be able to react to specific
            //      loading contexts/events.
            class SCENE_CORE_CLASS LoadingComponent
                : public AZ::Component
                , public Events::CallProcessorBinder
            {
            public:
                AZ_COMPONENT(LoadingComponent, "{335A696D-38DA-4A4F-B3F3-DBAD1FE86888}", Events::CallProcessorBinder);

                LoadingComponent() = default;
                ~LoadingComponent() override = default;

                SCENE_CORE_API void Activate() override;
                SCENE_CORE_API void Deactivate() override;

                static void Reflect(ReflectContext* context);
            protected:
#if defined(AZ_COMPILER_MSVC) && AZ_COMPILER_MSVC <= 1800
                // Workaround for VS2013 - Delete the copy constructor and make it private
                // https://connect.microsoft.com/VisualStudio/feedback/details/800328/std-is-copy-constructible-is-broken
                LoadingComponent(const LoadingComponent&) = delete;
#endif
            };
        } // namespace SceneCore
    } // namespace SceneAPI
} // namespace AZ