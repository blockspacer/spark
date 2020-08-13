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

#include <AzCore/Component/TransformBus.h>
#include <LmbrCentral/Shape/ShapeComponentBus.h>
#include <LmbrCentral/Shape/SphereShapeComponentBus.h>

namespace AzFramework
{
    class EntityDebugDisplayRequests;
}

namespace LmbrCentral
{
    struct ShapeDrawParams;

    class SphereShape
        : public ShapeComponentRequestsBus::Handler
        , public SphereShapeComponentRequestsBus::Handler
        , public AZ::TransformNotificationBus::Handler
    {
    public:
        AZ_CLASS_ALLOCATOR(SphereShape, AZ::SystemAllocator, 0)
        AZ_RTTI(SphereShape, "{FC63856F-318C-406A-AF3A-FDFF448D850A}")

        static void Reflect(AZ::ReflectContext* context);

        void Activate(AZ::EntityId entityId);
        void Deactivate();
        void InvalidateCache(InvalidateShapeCacheReason reason);

        // ShapeComponentRequestsBus::Handler
        AZ::Crc32 GetShapeType() override { return AZ_CRC("Sphere", 0x55f96687); }
        AZ::Aabb GetEncompassingAabb() override;
        bool IsPointInside(const AZ::Vector3& point)  override;
        float DistanceSquaredFromPoint(const AZ::Vector3& point) override;
        bool IntersectRay(const AZ::Vector3& src, const AZ::Vector3& dir, AZ::VectorFloat& distance) override;

        // SphereShapeComponentRequestsBus::Handler
        SphereShapeConfig GetSphereConfiguration() override { return m_sphereShapeConfig; }
        void SetRadius(float radius) override;
        float GetRadius() override;

        // AZ::TransformNotificationBus::Handler
        void OnTransformChanged(const AZ::Transform& local, const AZ::Transform& world) override;

        const SphereShapeConfig& GetSphereConfiguration() const { return m_sphereShapeConfig; }
        void SetSphereConfiguration(const SphereShapeConfig& sphereShapeConfig) { m_sphereShapeConfig = sphereShapeConfig; }
        const AZ::Transform& GetCurrentTransform() const { return m_currentTransform; }

    private:
        /**
         * Runtime data - cache potentially expensive operations.
         */
        class SphereIntersectionDataCache
            : public IntersectionTestDataCache<SphereShapeConfig>
        {
            void UpdateIntersectionParamsImpl(
                const AZ::Transform& currentTransform, const SphereShapeConfig& configuration) override;

            friend class SphereShape;
            
            AZ::Vector3 m_position; ///< Position of the center of the sphere.
            float m_radius = 0.0f; ///< Radius of the sphere (including entity scale).
        };

        SphereShapeConfig m_sphereShapeConfig; ///< Underlying sphere configuration.
        SphereIntersectionDataCache m_intersectionDataCache; ///< Caches transient intersection data.
        AZ::Transform m_currentTransform; ///< Caches the current world transform.
        AZ::EntityId m_entityId; ///< The Id of the entity the shape is attached to.
    };

    void DrawSphereShape(
        const ShapeDrawParams& shapeDrawParams, const SphereShapeConfig& sphereShapeConfig,
        AzFramework::EntityDebugDisplayRequests& displayContext);

} // namespace LmbrCentral