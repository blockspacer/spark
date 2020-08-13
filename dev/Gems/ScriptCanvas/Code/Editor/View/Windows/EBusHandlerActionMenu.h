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

#include <QAbstractListModel>
#include <QAbstractItemView>
#include <QMenu>
#include <qregexp.h>
#include <QSortFilterProxyModel>

#include <AzCore/Component/Entity.h>

namespace Ui
{
    class EBusHandlerActionListWidget;
}

namespace ScriptCanvasEditor
{
    struct EBusHandlerActionItem
    {
    public:
    
        int m_index = -1;
        QString m_name;
        QString m_displayName;
        bool m_active = false;
    };
    
    class EBusHandlerActionSourceModel
        : public QAbstractListModel
    {
        Q_OBJECT
    public:
        AZ_CLASS_ALLOCATOR(EBusHandlerActionSourceModel, AZ::SystemAllocator, 0);

        EBusHandlerActionSourceModel(QObject* parent = nullptr);
        ~EBusHandlerActionSourceModel();

        int rowCount(const QModelIndex& parent) const override;
        
        QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
        QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
        
        Qt::ItemFlags flags(const QModelIndex &index) const override;

        void OnItemClicked(const QModelIndex& index);
        
        void SetEBusNodeSource(const AZ::EntityId& ebusNode);
        
        EBusHandlerActionItem& GetActionItemForRow(int row);
        const EBusHandlerActionItem& GetActionItemForRow(int row) const;
        
    private:

        void UpdateEBusItem(EBusHandlerActionItem& actionItem);
    
        AZStd::vector< EBusHandlerActionItem > m_actionItems;
    
        AZ::EntityId m_ebusNode;
        AZStd::string m_busName;
    };
    
    class EBusHandlerActionFilterProxyModel
        : public QSortFilterProxyModel
    {
        Q_OBJECT
    public:
        AZ_CLASS_ALLOCATOR(EBusHandlerActionFilterProxyModel, AZ::SystemAllocator, 0);
        
        EBusHandlerActionFilterProxyModel(QObject* parent = nullptr);
        ~EBusHandlerActionFilterProxyModel() = default;

        void SetFilterSource(QLineEdit* lineEdit);
        
        bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;    
        
    public slots:
        void OnFilterChanged(const QString& text);
        
    private:
        QString m_filter;

        QRegExp m_regex;
    };

    class EBusHandlerActionMenu
        : public QMenu
    {
        Q_OBJECT
    public:
        AZ_CLASS_ALLOCATOR(EBusHandlerActionMenu, AZ::SystemAllocator, 0);
        EBusHandlerActionMenu(QWidget* parent = nullptr);
        ~EBusHandlerActionMenu() = default;
        
        void SetEbusHandlerNode(const AZ::EntityId& ebusWrapperNode);
        
    public slots:
        void ResetFilter();
        void ItemClicked(const QModelIndex& modelIndex);
        
    protected:    
        void keyPressEvent(QKeyEvent* keyEvent) override;   
        
    private:    
        
        EBusHandlerActionFilterProxyModel* m_proxyModel;
        EBusHandlerActionSourceModel* m_model;
        Ui::EBusHandlerActionListWidget* m_listWidget;
    };
}