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

#include "EditorCommon.h"

#include <AzToolsFramework/API/ToolsApplicationAPI.h>
#include <AzToolsFramework/ToolsMessaging/EntityHighlightBus.h>

#include <QTreeWidget>

class HierarchyWidget
    : public QTreeWidget
    , private AzToolsFramework::EditorPickModeRequests::Bus::Handler
    , private AzToolsFramework::EntityHighlightMessages::Bus::Handler
{
    Q_OBJECT

public:

    HierarchyWidget(EditorWindow* editorWindow);
    virtual ~HierarchyWidget();

    void SetIsDeleting(bool b);

    EntityHelpers::EntityToHierarchyItemMap& GetEntityItemMap();
    EditorWindow* GetEditorWindow();

    void ActiveCanvasChanged();
    void EntityContextChanged();

    void CreateItems(const LyShine::EntityArray& elements);
    void RecreateItems(const LyShine::EntityArray& elements);
    void ClearItems();

    AZ::Entity* CurrentSelectedElement() const;

    void SetUniqueSelectionHighlight(QTreeWidgetItem* item);
    void SetUniqueSelectionHighlight(AZ::Entity* element);

    void AddElement(const QTreeWidgetItemRawPtrQList& selectedItems, const QPoint* optionalPos);

    void SignalUserSelectionHasChanged(const QTreeWidgetItemRawPtrQList& selectedItems);

    void ReparentItems(bool onCreationOfElement,
        const QTreeWidgetItemRawPtrList& baseParentItems,
        const HierarchyItemRawPtrList& childItems);

    //! When we delete the Editor window we call this. It avoid the element Entities
    //! being deleted when the HierarchyItem is deleted
    void ClearAllHierarchyItemEntityIds();

    void ApplyElementIsExpanded();

    void ClearItemBeingHovered();

    //! Update the appearance of all hierarchy items to reflect their slice status
    void UpdateSliceInfo();

public slots:
    void DeleteSelectedItems();
    void Cut();
    void Copy();
    void PasteAsSibling();
    void PasteAsChild();
    void SetEditorOnlyForSelectedItems(bool editorOnly);

signals:

    void SetUserSelection(HierarchyItemRawPtrList* items);
    void editorOnlyStateChangedOnSelectedElements();

private slots:

    // This is used to detect the user changing the selection in the Hierarchy.
    void CurrentSelectionHasChanged(const QItemSelection& selected, const QItemSelection& deselected);
    void DataHasChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight, const QVector<int>& roles = QVector<int>());

    void HandleItemAdd(HierarchyItem* item);
    void HandleItemRemove(HierarchyItem* item);

protected:

    void mousePressEvent(QMouseEvent* ev) override;
    void mouseMoveEvent(QMouseEvent* ev) override;
    void mouseReleaseEvent(QMouseEvent* ev) override;
    void leaveEvent(QEvent* ev) override;
    void contextMenuEvent(QContextMenuEvent* ev) override;
    void mouseDoubleClickEvent(QMouseEvent* ev) override;
    void startDrag(Qt::DropActions supportedActions) override;
    void dragEnterEvent(QDragEnterEvent * event) override;
    void dragLeaveEvent(QDragLeaveEvent * event) override;
    void dropEvent(QDropEvent* ev) override;
    QStringList mimeTypes() const override;
    QMimeData *mimeData(const QList<QTreeWidgetItem*> items) const override;

private:

    // EditorPickModeRequests
    void StartObjectPickMode() override;
    void StopObjectPickMode() override;
    // ~EditorPickModeRequests

    // EntityHighlightMessages
    void EntityHighlightRequested(AZ::EntityId entityId) override;
    void EntityStrongHighlightRequested(AZ::EntityId entityId) override;
    // ~EntityHighlightMessages

    void PickItem(HierarchyItem* item);

    bool IsEntityInEntityContext(AZ::EntityId entityId);

    void ToggleVisibility(HierarchyItem* hierarchyItem);
    void DeleteSelectedItems(const QTreeWidgetItemRawPtrQList& selectedItems);
    bool AcceptsMimeData(const QMimeData *mimeData);

    bool m_isDeleting;

    EditorWindow* m_editorWindow;

    EntityHelpers::EntityToHierarchyItemMap m_entityItemMap;

    HierarchyItem* m_itemBeingHovered;

    QTreeWidgetItemRawPtrQList m_beforeDragSelection;
    QTreeWidgetItemRawPtrQList m_dragSelection;
    bool m_inDragStartState;
    bool m_selectionChangedBeforeDrag;
    bool m_signalSelectionChange;

    bool m_inObjectPickMode;

    // Used to restore the normal hierarchy mode after pick mode is complete
    QAbstractItemView::SelectionMode m_selectionModeBeforePickMode;
    EditTriggers m_editTriggersBeforePickMode;
    QModelIndex m_currentItemBeforePickMode;

    bool m_inited;
};
