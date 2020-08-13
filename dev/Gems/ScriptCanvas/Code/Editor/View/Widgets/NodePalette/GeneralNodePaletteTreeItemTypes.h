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

#include <GraphCanvas/Widgets/NodePalette/TreeItems/DraggableNodePaletteTreeItem.h>

#include "CreateNodeMimeEvent.h"

namespace ScriptCanvasEditor
{
    // <ClassMethod>
    class CreateClassMethodMimeEvent
        : public CreateNodeMimeEvent
    {
    public:
        AZ_RTTI(CreateClassMethodMimeEvent, "{20641353-0513-4399-97D4-5509377BF0C8}", CreateNodeMimeEvent);
        AZ_CLASS_ALLOCATOR(CreateClassMethodMimeEvent, AZ::SystemAllocator, 0);
        
        static void Reflect(AZ::ReflectContext* reflectContext);
        
        CreateClassMethodMimeEvent() = default;
        CreateClassMethodMimeEvent(const QString& className, const QString& methodName);
        ~CreateClassMethodMimeEvent() = default;

    protected:
        ScriptCanvasEditor::NodeIdPair CreateNode(const AZ::EntityId& graphId) const override;

    private:
        AZStd::string m_className;
        AZStd::string m_methodName;
    };
    
    class ClassMethodEventPaletteTreeItem
        : public GraphCanvas::DraggableNodePaletteTreeItem
    {
    private:
        static const QString& GetDefaultIcon();
        
    public:
        AZ_CLASS_ALLOCATOR(ClassMethodEventPaletteTreeItem, AZ::SystemAllocator, 0);

        ClassMethodEventPaletteTreeItem(const QString& className, const QString& methodName);
        ~ClassMethodEventPaletteTreeItem() = default;
        
        GraphCanvas::GraphCanvasMimeEvent* CreateMimeEvent() const override;

    private:
        QString m_className;
        QString m_methodName;
    };    
    // </ClassMethod>
        
    // <CustomNode>
    class CreateCustomNodeMimeEvent
        : public CreateNodeMimeEvent
    {
    public:
        AZ_RTTI(CreateCustomNodeMimeEvent, "{7130C89B-2F2D-493F-AA5C-8B72968D4200}", CreateNodeMimeEvent);
        AZ_CLASS_ALLOCATOR(CreateCustomNodeMimeEvent, AZ::SystemAllocator, 0);
        
        static void Reflect(AZ::ReflectContext* reflectContext);
        
        CreateCustomNodeMimeEvent() = default;
        CreateCustomNodeMimeEvent(const AZ::Uuid& typeId);
        CreateCustomNodeMimeEvent(const AZ::Uuid& typeId, const AZStd::string& styleOverride, const AZStd::string& titlePalette);
        ~CreateCustomNodeMimeEvent() = default;

    protected:
        ScriptCanvasEditor::NodeIdPair CreateNode(const AZ::EntityId& graphId) const override;

    private:
        AZ::Uuid m_typeId;
        AZStd::string m_styleOverride;
        AZStd::string m_titlePalette;
    };
    
    class CustomNodePaletteTreeItem
        : public GraphCanvas::DraggableNodePaletteTreeItem
    {
    public:
        AZ_CLASS_ALLOCATOR(CustomNodePaletteTreeItem, AZ::SystemAllocator, 0);
        CustomNodePaletteTreeItem(const AZ::Uuid& typeId, const QString& nodeName, const QString& iconPath);
        ~CustomNodePaletteTreeItem() = default;
        
        GraphCanvas::GraphCanvasMimeEvent* CreateMimeEvent() const override;
        
    private:
        AZ::Uuid m_typeId;
    };
    
    // </CustomNode>
}