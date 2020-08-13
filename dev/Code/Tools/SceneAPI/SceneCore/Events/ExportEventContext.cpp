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

#include <SceneAPI/SceneCore/Events/ExportEventContext.h>

namespace AZ
{
    namespace SceneAPI
    {
        namespace Events
        {
            /////////////
            // PreExportEventContext
            /////////////

            PreExportEventContext::PreExportEventContext(ExportProductList& productList, const AZStd::string& outputDirectory, const Containers::Scene& scene, const char* platformIdentifier)
                : m_outputDirectory(outputDirectory)
                , m_productList(productList)
                , m_scene(scene)
                , m_platformIdentifier(platformIdentifier)
            {
            }

            PreExportEventContext::PreExportEventContext(ExportProductList& productList, AZStd::string&& outputDirectory, const Containers::Scene& scene, const char* platformIdentifier)
                : m_outputDirectory(AZStd::move(outputDirectory))
                , m_productList(productList)
                , m_scene(scene)
                , m_platformIdentifier(platformIdentifier)
            {
            }

            const AZStd::string& PreExportEventContext::GetOutputDirectory() const
            {
                return m_outputDirectory;
            }

            ExportProductList& PreExportEventContext::GetProductList()
            {
                return m_productList;
            }

            const ExportProductList& PreExportEventContext::GetProductList() const
            {
                return m_productList;
            }

            const Containers::Scene& PreExportEventContext::GetScene() const
            {
                return m_scene;
            }

            const char* PreExportEventContext::GetPlatformIdentifier() const
            {
                return m_platformIdentifier;
            }

            /////////////
            // ExportEventContext
            /////////////

            ExportEventContext::ExportEventContext(ExportProductList& productList, const AZStd::string& outputDirectory, const Containers::Scene& scene, const char* platformIdentifier)
                : m_outputDirectory(outputDirectory)
                , m_productList(productList)
                , m_scene(scene)
                , m_platformIdentifier(platformIdentifier)
            {
            }

            ExportEventContext::ExportEventContext(ExportProductList& productList, AZStd::string&& outputDirectory, const Containers::Scene& scene, const char* platformIdentifier)
                : m_outputDirectory(AZStd::move(outputDirectory))
                , m_productList(productList)
                , m_scene(scene)
                , m_platformIdentifier(platformIdentifier)
            {
            }

            const AZStd::string& ExportEventContext::GetOutputDirectory() const
            {
                return m_outputDirectory;
            }

            ExportProductList& ExportEventContext::GetProductList()
            {
                return m_productList;
            }

            const ExportProductList& ExportEventContext::GetProductList() const
            {
                return m_productList;
            }

            const Containers::Scene& ExportEventContext::GetScene() const
            {
                return m_scene;
            }

            const char* ExportEventContext::GetPlatformIdentifier() const
            {
                return m_platformIdentifier;
            }

            /////////////
            // PostExportEventContext
            /////////////

            PostExportEventContext::PostExportEventContext(ExportProductList& productList, const AZStd::string& outputDirectory, const char* platformIdentifier)
                : m_outputDirectory(outputDirectory)
                , m_productList(productList)
                , m_platformIdentifier(platformIdentifier)
            {
            }

            PostExportEventContext::PostExportEventContext(ExportProductList& productList, AZStd::string&& outputDirectory, const char* platformIdentifier)
                : m_outputDirectory(AZStd::move(outputDirectory))
                , m_platformIdentifier(platformIdentifier)
                , m_productList(productList)
            {
            }

            const AZStd::string PostExportEventContext::GetOutputDirectory() const
            {
                return m_outputDirectory;
            }

            ExportProductList& PostExportEventContext::GetProductList()
            {
                return m_productList;
            }

            const ExportProductList& PostExportEventContext::GetProductList() const
            {
                return m_productList;
            }

            const char* PostExportEventContext::GetPlatformIdentifier() const
            {
                return m_platformIdentifier;
            }
        } // Events
    } // SceneAPI
} // AZ