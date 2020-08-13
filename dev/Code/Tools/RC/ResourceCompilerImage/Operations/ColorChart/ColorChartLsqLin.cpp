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
// Original file Copyright Crytek GMBH or its affiliates, used under license.

#include "stdafx.h"

#include "../../ImageObject.h"

#include "ColorChartBase.h"

//////////////////////////////////////////////////////////////////////////
// helper

struct SSolverInput
{
    double x, y;
};


static void LsqSolveLinear(const SSolverInput* pInput, size_t numElements, double& a, double& b)
{
    double sumx = 0;
    double sumy = 0;
    double sumxy = 0;
    double sumxx = 0;

    for (size_t i = 0; i < numElements; ++i)
    {
        sumx += pInput[i].x;
        sumy += pInput[i].y;
        sumxy += pInput[i].x * pInput[i].y;
        sumxx += pInput[i].x * pInput[i].x;
    }

    double slope = (sumx * sumy - (double) numElements * sumxy) / (sumx * sumx - (double) numElements * sumxx);
    double yintercept = (sumy - slope * sumx) / (double) numElements;

    a = slope;
    b = yintercept;
}

//////////////////////////////////////////////////////////////////////////
// CLsqLinColorChart impl

class CLsqLinColorChart
    : public CColorChartBase
{
public:
    CLsqLinColorChart();
    virtual ~CLsqLinColorChart();

    virtual void Release();
    virtual void GenerateDefault();
    virtual ImageObject* GenerateChartImage();

protected:
    virtual bool ExtractFromImageAt(ImageObject* pImg, uint32 x, uint32 y);

private:
    double m_aRed, m_bRed;
    double m_aGreen, m_bGreen;
    double m_aBlue, m_bBlue;
};


CLsqLinColorChart::CLsqLinColorChart()
    : CColorChartBase()
    , m_aRed(1)
    , m_bRed(0)
    , m_aGreen(1)
    , m_bGreen(0)
    , m_aBlue(1)
    , m_bBlue(0)
{
}


CLsqLinColorChart::~CLsqLinColorChart()
{
}


void CLsqLinColorChart::Release()
{
    delete this;
}


void CLsqLinColorChart::GenerateDefault()
{
    m_aRed = m_aGreen = m_aBlue = -1;
    m_bRed = m_bGreen = m_bBlue = 1;
}


ImageObject* CLsqLinColorChart::GenerateChartImage()
{
    // not supported by this chart extraction method, need to serialize coefficients to XML
    return 0;
}


bool CLsqLinColorChart::ExtractFromImageAt(ImageObject* pImg, uint32 x, uint32 y)
{
    assert(pImg);

    x += 65;
    y += 1;

    char* pData;
    uint32 pitch;
    pImg->GetImagePointer(0, pData, pitch);

    const int INSIZE = 256;
    SSolverInput input[INSIZE];

    for (int i = 0; i < INSIZE; ++i)
    {
        input[i].x = i;
    }

    // solve least min squares for red channel
    for (int a = 0, idx = 0; a < 64; ++a)
    {
        for (int i = 0; i < 4; ++i, ++idx)
        {
            uint32 c = GetAt(x + i, y + a, pData, pitch);
            input[idx].y = (double)((c >> 16) & 0xFF);
        }
    }
    LsqSolveLinear(input, INSIZE, m_aRed, m_bRed);

    x += 4;
    // solve least min squares for green channel
    for (int a = 0, idx = 0; a < 64; ++a)
    {
        for (int i = 0; i < 4; ++i, ++idx)
        {
            uint32 c = GetAt(x + i, y + a, pData, pitch);
            input[idx].y = (double)((c >> 8) & 0xFF);
        }
    }
    LsqSolveLinear(input, INSIZE, m_aGreen, m_bGreen);

    x += 4;
    // solve least min squares for blue channel
    for (int a = 0, idx = 0; a < 64; ++a)
    {
        for (int i = 0; i < 4; ++i, ++idx)
        {
            uint32 c = GetAt(x + i, y + a, pData, pitch);
            input[idx].y = (double)(c & 0xFF);
        }
    }
    LsqSolveLinear(input, INSIZE, m_aBlue, m_bBlue);

    return true;
}

//////////////////////////////////////////////////////////////////////////
// CLsqLinColorChart factory

IColorChart* CreateLeastSquaresLinColorChart()
{
    return new CLsqLinColorChart();
}
