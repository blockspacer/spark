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

#include <AzCore/EBus/EBus.h>

namespace PhysXDebug
{
    class DebugRequests
        : public AZ::EBusTraits
    {
    public:
        // EBusTraits overrides
        static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static const AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;

        /// Toggle the PhysX debug gem visualization on/off.
        /// @param enabled to enable visualization or not.
        virtual void SetVisualization(bool enabled) = 0;

        /// Toggle between minimal physx::PxVisualizationParameter::eCOLLISION_SHAPES and eCOLLISION_EDGES
        /// and full visualization everything in physx::PxVisualizationParameter configuration.
        /// Will switch between minimal and full on call.
        virtual void ToggleVisualizationConfiguration() = 0;

        /// Toggle editor mode collider proximity debug visualization on/off (disabled by default)
        virtual void ToggleColliderProximityDebugVisualization() = 0;

        /// Enables PhysX debug visualization and also sets the culling box size.
        /// @param cullingBoxSize specifies the new culling box size to use. A value of 0 or less turns off culling.
        virtual void SetCullingBoxSize(float cullingBoxSize) = 0;

        /// Toggle the visual culling box.
        /// The visual culling box is disabled by default.
        virtual void ToggleCullingWireFrame() = 0;
    };
    using PhysXDebugRequestBus = AZ::EBus<DebugRequests>;
} // namespace PhysXDebug
