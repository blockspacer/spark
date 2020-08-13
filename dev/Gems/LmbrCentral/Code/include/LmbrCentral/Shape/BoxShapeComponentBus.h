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

#include <AzCore/Component/ComponentBus.h>
#include <AzCore/Math/Vector3.h>

namespace LmbrCentral
{
    /**
     * Type ID for the BoxShapeComponent
     */
    static const AZ::Uuid BoxShapeComponentTypeId = "{5EDF4B9E-0D3D-40B8-8C91-5142BCFC30A6}";

    /**
     * Type ID for the EditorBoxShapeComponent
     */
    static const AZ::Uuid EditorBoxShapeComponentTypeId = "{2ADD9043-48E8-4263-859A-72E0024372BF}";

    /**
     * Configuration data for BoxShapeComponent
     */
    class BoxShapeConfig
        : public AZ::ComponentConfig
    {
    public:
        AZ_CLASS_ALLOCATOR(BoxShapeConfig, AZ::SystemAllocator, 0)
        AZ_RTTI(BoxShapeConfig, "{F034FBA2-AC2F-4E66-8152-14DFB90D6283}", AZ::ComponentConfig)

        static void Reflect(AZ::ReflectContext* context);

        BoxShapeConfig() = default;
        explicit BoxShapeConfig(const AZ::Vector3& dimensions) : m_dimensions(dimensions) {}

        void SetDimensions(const AZ::Vector3& dimensions)
        {
            AZ_WarningOnce("LmbrCentral", false, "SetDimensions Deprecated - Please use m_dimensions");
            m_dimensions = dimensions;
        }

        AZ::Vector3 GetDimensions() const
        {
            AZ_WarningOnce("LmbrCentral", false, "GetDimensions Deprecated - Please use m_dimensions");
            return m_dimensions;
        }

        AZ::Vector3 m_dimensions = AZ::Vector3::CreateOne(); ///< Stores the dimensions of the box along each axis.
    };

    using BoxShapeConfiguration = BoxShapeConfig; ///< @deprecated Use BoxShapeConfig instead

    /**
     * Services provided by the Box Shape Component
     */
    class BoxShapeComponentRequests
        : public AZ::ComponentBus
    {
    public:
        virtual BoxShapeConfig GetBoxConfiguration() = 0;

        /**
        * @brief Gets dimensions for the Box Shape
        * @return Vector3 indicating dimensions along the x,y & z axis
        */
        virtual AZ::Vector3 GetBoxDimensions() = 0;

        /**
        * @brief Sets new dimensions for the Box Shape
        * @param newDimensions Vector3 indicating new dimensions along the x,y & z axis
        */
        virtual void SetBoxDimensions(const AZ::Vector3& newDimensions) = 0;
    };

    // Bus to service the Box Shape component event group
    using BoxShapeComponentRequestsBus = AZ::EBus<BoxShapeComponentRequests>;

} // namespace LmbrCentral