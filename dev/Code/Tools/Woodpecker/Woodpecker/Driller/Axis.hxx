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

#ifndef CHART_AXIS_H
#define CHART_AXIS_H

#include <AzCore/base.h>
#include <AzCore/Memory/SystemAllocator.h>
#include <AzCore/std/containers/vector.h>

#include <QObject>
#include <Woodpecker/Driller/ChartTypes.hxx>

class QPainter;

#pragma once

namespace Charts
{
    // the Axis represents one axis on a chart.  its float-based
    // it contains information about window range and domain range.
    class Axis : public QObject
    {
        Q_OBJECT;
    public:
        AZ_CLASS_ALLOCATOR(Axis,AZ::SystemAllocator,0);
        Axis(QObject* pParent = NULL);
        ~Axis();  // not virtual

    public:
        bool GetValid() const;
        bool GetAutoWindow() const;
        QString GetLabel() const;
        float GetWindowMin() const; 
        float GetWindowMax() const;
        float GetRangeMin()  const;
        float GetRangeMax() const;
        float GetWindowRange() const;
        float GetRange() const;
        bool GetLockedZoom() const;
        bool GetLockedRange() const;
        bool GetLockedRight() const;
        void Zoom(float focusPoint, float steps, float zoomLimit );
        void ZoomToRange(float windowMin, float windowMax, bool clamp);

        void PaintAxis(AxisType axisType, QPainter* painter, const QRect& widgetBounds, const QRect& graphBounds, QAbstractAxisFormatter* formatter);

        float ComputeAxisDivisions(float pixelWidth, AZStd::vector<float>& domainPointsOut, float minPixels, float maxPixels, bool allowFractions = true);

signals:
        void Invalidated(); // something has happened which should cause anyone using this axis to update themselves.

public slots:
        void SetAxisRange( float minimum, float maximum );
        void AddAxisRange( float value );
        void SetViewFull();
        void SetLabel(QString newLabel);
        void SetLockedRight(bool lockRight); 
        void SetLockedRange(bool locked); // cannot pan
        void SetLockedZoom(bool locked); // cannot zoom.
        void Clear();
        void SetAutoWindow( bool autoWindow );
        void SetWindowMin(float newValue);
        void SetWindowMax(float newValue);
        void UpdateWindowRange(float delta);
        void SetRangeMax(float rangemax);
        void SetRangeMin(float rangemin);
        void Drag(float delta);

    private:

        void PaintAsVerticalAxis(QPainter* painter, const QRect& widgetBounds, const QRect& graphBounds, QAbstractAxisFormatter* formatter);
        void PaintAsHorizontalAxis(QPainter* painter, const QRect& widgetBounds, const QRect& graphBounds, QAbstractAxisFormatter* formatter);
        void DrawRotatedText(QString text, QPainter *painter, float degrees, int x, int y, float scale);

        QString m_label;
        float m_rangeMin;
        float m_rangeMax;
        float m_windowMin;
        float m_windowMax;
        bool m_lockZoom; // zoom is always to the range
        bool m_lockRange; // you may only pan
        bool m_lockRight; 
        bool m_autoWindow;
        bool m_rangeMinInitialized;
        bool m_rangeMaxInitialized; // these are false until you init them, and the axis is invalid until such a time.
    };
}


#endif