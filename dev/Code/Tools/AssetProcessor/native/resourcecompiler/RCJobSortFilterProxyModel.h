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

#include <QSortFilterProxyModel>

namespace AssetProcessor
{
    class JobSortFilterProxyModel
        : public QSortFilterProxyModel
    {
        Q_OBJECT

    public:
        explicit JobSortFilterProxyModel(QObject* parent = nullptr);
        void OnFilterRegexExpChanged(QRegExp regExp, bool isFilterRegexExpEmpty);


    protected:
        bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;
    private:
        bool m_filterRegexExpEmpty = true;
    };
} // namespace AssetProcessor


