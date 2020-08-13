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

#include <AzQtComponents/AzQtComponentsAPI.h>
#include <QWidget>
#include <QVector>
#include <QString>
#include <QPushButton>


class QComboBox;
class QVBoxLayout;

namespace AzQtComponents
{
    class AZ_QT_COMPONENTS_API TagWidget
        : public QPushButton
    {
        Q_OBJECT
    public:
        TagWidget(const QString& text, QWidget* parent = nullptr);

    signals:
        void DeleteClicked();

    private slots:
        void OnClicked();

    private:
        bool IsOverCloseButton(int localX, int localY);
        void mouseMoveEvent(QMouseEvent* event);

        int m_lastMouseX;
        int m_lastMouseY;
    };


    class AZ_QT_COMPONENTS_API TagWidgetContainer
        : public QWidget
    {
        Q_OBJECT
    public:
        TagWidgetContainer(QWidget* parent = nullptr);
        void SetWrapWidth(int width);

        void AddTag(const QString& tag);
        void AddTags(const QVector<QString>& selectedTags);
        void RemoveTag(const QString& tag);
        void Reinit(const QVector<QString>& tags);

        int GetNumTags() const;
        const QString& GetTag(int index) const;
        const QVector<QString>& GetTags() const;
        bool Contains(const QString& tag) const;

    signals:
        void TagsChanged();

    private:
        QVector<QString>    m_tags;     //! List of tags that shall be displayed.
        QWidget*            m_widget;
        QVBoxLayout*        m_layout;
        int                 m_width;
    };


    class AZ_QT_COMPONENTS_API TagSelector
        : public QWidget
    {
        Q_OBJECT
    public:
        TagSelector(QWidget* parent = nullptr);
        TagSelector(const QVector<QString>& availableTags, QWidget* parent = nullptr);

        void Reinit(const QVector<QString>& availableTags);
        void Reinit();

        bool IsTagSelected(const QString& tag) const;

        void SelectTag(const QString& tag);

        /*!
         * Create tag widgets for all given tags. The tag widgets represent the current tag selection.
         * @param[in] selectedTags A list of tags that should be selected. Make sure the there are no duplicated tags in the given tag list.
         */
        void SelectTags(const QVector<QString>& selectedTags);

        void GetSelectedTagStrings(QVector<QString>& outTags) const;

    signals:
        void TagsChanged();

    private slots:
        void OnComboActivated(int index);

    private:
        void Init();

        QVector<QString>    m_availableTags;    //!  List of available tags to choose from.
        TagWidgetContainer* m_tagWidgets;       //!  List of tag widgets. Each tag widget represents one selected tag.
        QComboBox*          m_combo;
    };
} // namespace AzQtComponents