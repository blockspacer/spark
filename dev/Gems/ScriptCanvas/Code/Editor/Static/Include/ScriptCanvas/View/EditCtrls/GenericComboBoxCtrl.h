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

#include <AzCore/Memory/SystemAllocator.h>
#include <QtWidgets/QWidget>
#include <AzToolsFramework/UI/PropertyEditor/PropertyEditorAPI.h>
#include <ScriptCanvas/Core/Attributes.h>

class QComboBox;

namespace ScriptCanvasEditor
{
    template<typename T>
    class GenericComboBoxHandler;

    class GenericComboBoxCtrlBase
        : public QWidget
    {
        Q_OBJECT
    public:
        AZ_RTTI(GenericComboBoxCtrlBase, "{879D010E-743F-45FB-9D97-2DAD2C25ACBA}");
        AZ_CLASS_ALLOCATOR(GenericComboBoxCtrlBase, AZ::SystemAllocator, 0);

        GenericComboBoxCtrlBase(QWidget* pParent = nullptr);
        ~GenericComboBoxCtrlBase() override = default;

    signals:
        void valueChanged(AZStd::string& newValue);

    protected:
        virtual void onChildComboBoxValueChange(int comboBoxIndex) = 0;

    public:
        virtual QWidget* GetFirstInTabOrder() = 0;
        virtual QWidget* GetLastInTabOrder() = 0;
        virtual void UpdateTabOrder() = 0;
    };

    template<typename T>
    class GenericComboBoxCtrl
        : public GenericComboBoxCtrlBase
    {
        friend class GenericComboBoxHandler<T>;
    public:
        AZ_RTTI(((GenericComboBoxCtrl<T>), "{FA7EC12F-1DA3-4734-ABDE-CBFD99450571}", T), GenericComboBoxCtrlBase);
        AZ_CLASS_ALLOCATOR(GenericComboBoxCtrl, AZ::SystemAllocator, 0);

        using GenericType = T;

        GenericComboBoxCtrl(QWidget* pParent = nullptr);
        ~GenericComboBoxCtrl() override = default;

    protected:
        QWidget* GetFirstInTabOrder() override;
        QWidget* GetLastInTabOrder() override;
        void UpdateTabOrder() override;

        const T& value() const;
        void setValue(const T& value);
        void addGenericValuesItems(const AZStd::vector<AZStd::pair<T, AZStd::string>>& genericValues);
        void setGenericValuesItems(const AZStd::vector<AZStd::pair<T, AZStd::string>>& genericValues);

        void onChildComboBoxValueChange(int comboBoxIndex) override;

    private:
        QComboBox* m_pComboBox;
        AZStd::vector<AZStd::pair<T, AZStd::string>> m_values;
        AZ::AttributeFunction <void(const T&)>* m_postChangeNotifyCB{};
    };

    template<typename T>
    class GenericComboBoxHandler
        : QObject
        , public AzToolsFramework::PropertyHandler<T, GenericComboBoxCtrlBase>
    {
    public:
        AZ_CLASS_ALLOCATOR(GenericComboBoxHandler, AZ::SystemAllocator, 0);

        using ComboBoxCtrl = GenericComboBoxCtrlBase;
        GenericComboBoxHandler() = default;

        AZ::u32 GetHandlerName(void) const override { return ScriptCanvas::Attributes::UIHandlers::GenericComboBox; }
        QWidget* GetFirstInTabOrder(ComboBoxCtrl* widget) override { return widget->GetFirstInTabOrder(); }
        QWidget* GetLastInTabOrder(ComboBoxCtrl* widget) override { return widget->GetLastInTabOrder(); }
        void UpdateWidgetInternalTabbing(ComboBoxCtrl* widget) override { widget->UpdateTabOrder(); }

        QWidget* CreateGUI(QWidget* pParent) override;
        void ConsumeAttribute(ComboBoxCtrl* GUI, AZ::u32 attrib, AzToolsFramework::PropertyAttributeReader* attrValue, const char* debugName) override;
        void WriteGUIValuesIntoProperty(size_t index, ComboBoxCtrl* GUI, typename GenericComboBoxHandler::property_t& instance, AzToolsFramework::InstanceDataNode* node) override;
        bool ReadValuesIntoGUI(size_t index, ComboBoxCtrl* GUI, const typename GenericComboBoxHandler::property_t& instance, AzToolsFramework::InstanceDataNode* node)  override;

        bool AutoDelete() const override { return false; }

    private:
        void InvokePostChangeNotify(size_t index, GenericComboBoxCtrl<T>* genericGUI, const typename GenericComboBoxHandler::property_t& oldValue, AzToolsFramework::InstanceDataNode* node) const;
    };

    template<typename T>
    AzToolsFramework::PropertyHandlerBase* RegisterGenericComboBoxHandler()
    {
        auto propertyHandler = aznew GenericComboBoxHandler<T>();
        AzToolsFramework::PropertyTypeRegistrationMessages::Bus::Broadcast(&AzToolsFramework::PropertyTypeRegistrationMessages::RegisterPropertyType, propertyHandler);
        return propertyHandler;
    }
}

#include <ScriptCanvas/View/EditCtrls/GenericComboBoxCtrl.inl>