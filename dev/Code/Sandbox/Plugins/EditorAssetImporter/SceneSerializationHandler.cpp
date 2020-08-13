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

#include "StdAfx.h"
#include <AzCore/IO/SystemFile.h>
#include <AzCore/std/algorithm.h>
#include <AzCore/std/string/conversions.h>
#include <AzFramework/StringFunc/StringFunc.h>
#include <AzToolsFramework/API/EditorAssetSystemAPI.h>
#include <AzToolsFramework/Debug/TraceContext.h>
#include <SceneAPI/SceneCore/Events/AssetImportRequest.h>
#include <SceneAPI/SceneCore/Utilities/Reporting.h>
#include <SceneSerializationHandler.h>

namespace AZ
{
    SceneSerializationHandler::~SceneSerializationHandler()
    {
        Deactivate();
    }

    void SceneSerializationHandler::Activate()
    {
        BusConnect();
    }

    void SceneSerializationHandler::Deactivate()
    {
        BusDisconnect();
    }

    AZStd::shared_ptr<SceneAPI::Containers::Scene> SceneSerializationHandler::LoadScene(
        const AZStd::string& filePath, Uuid sceneSourceGuid)
    {
        namespace Utilities = AZ::SceneAPI::Utilities;
        using AZ::SceneAPI::Events::AssetImportRequest;

        CleanSceneMap();

        AZ_TraceContext("File", filePath);
        if (!IsValidExtension(filePath))
        {
            return nullptr;
        }

        AZStd::string cleanPath = filePath;
        if (AzFramework::StringFunc::Path::IsRelative(filePath.c_str()))
        {
            const char* absolutePath = nullptr;
            AzToolsFramework::AssetSystemRequestBus::BroadcastResult(absolutePath, 
                &AzToolsFramework::AssetSystemRequestBus::Events::GetAbsoluteDevRootFolderPath);
            AZ_Assert(absolutePath, "Unable to retrieve the dev folder path");
            AzFramework::StringFunc::Path::Join(absolutePath, cleanPath.c_str(), cleanPath);
        }
        else
        {
            // Normalizing is not needed if the path is relative as Join(...) will also normalize.
            AzFramework::StringFunc::Path::Normalize(cleanPath);
        }
        AZStd::to_lower(cleanPath.begin(), cleanPath.end());

        auto sceneIt = m_scenes.find(cleanPath);
        if (sceneIt != m_scenes.end())
        {
            AZStd::shared_ptr<SceneAPI::Containers::Scene> scene = sceneIt->second.lock();
            if (scene)
            {
                return scene;
            }
            // There's a small window in between which the scene was closed after searching for
            //      it in the scene map. In this case continue and simply reload the scene.
        }

        if (!AZ::IO::SystemFile::Exists(cleanPath.c_str()))
        {
            AZ_TracePrintf(Utilities::ErrorWindow, "No file exists at given source path.");
            return nullptr;
        }

        if (sceneSourceGuid.IsNull())
        {
            bool result = false;
            AZ::Data::AssetInfo info;
            AZStd::string watchFolder;
            AzToolsFramework::AssetSystemRequestBus::BroadcastResult(result, &AzToolsFramework::AssetSystemRequestBus::Events::GetSourceInfoBySourcePath, cleanPath.c_str(), info, watchFolder);
            if (!result)
            {
                AZ_TracePrintf(Utilities::ErrorWindow, "Failed to retrieve file info needed to determine the uuid of the source file.");
                return nullptr;
            }
            sceneSourceGuid = info.m_assetId.m_guid;
        }

        AZStd::shared_ptr<SceneAPI::Containers::Scene> scene = 
            AssetImportRequest::LoadSceneFromVerifiedPath(cleanPath, sceneSourceGuid, AssetImportRequest::RequestingApplication::Editor);
        if (!scene)
        {
            AZ_TracePrintf(Utilities::ErrorWindow, "Failed to load the requested scene.");
            return nullptr;
        }

        m_scenes.emplace(AZStd::move(cleanPath), scene);
        
        return scene;
    }

    bool SceneSerializationHandler::IsValidExtension(const AZStd::string& filePath) const
    {
        namespace Utilities = AZ::SceneAPI::Utilities;

        if (AZ::SceneAPI::Events::AssetImportRequest::IsManifestExtension(filePath.c_str()))
        {
            AZ_TracePrintf(Utilities::ErrorWindow, "Provided path contains the manifest path, not the path to the source file.");
            return false;
        }

        if (!AZ::SceneAPI::Events::AssetImportRequest::IsSceneFileExtension(filePath.c_str()))
        {
            AZ_TracePrintf(Utilities::ErrorWindow, "Provided path doesn't contain an extension supported by the SceneAPI.");
            return false;
        }

        return true;
    }

    void SceneSerializationHandler::CleanSceneMap()
    {
        for (auto it = m_scenes.begin(); it != m_scenes.end(); )
        {
            if (it->second.expired())
            {
                it = m_scenes.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
} // namespace AZ