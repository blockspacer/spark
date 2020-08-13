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

// Description : Definition of the DXGL wrapper for IDXGIAdapter


#include "StdAfx.h"
#include "CCryDXGLGIAdapter.hpp"
#include "CCryDXGLGIFactory.hpp"
#include "CCryDXGLGIOutput.hpp"
#include "../Implementation/GLDevice.hpp"
#include "UnicodeFunctions.h"
#include "../../../Common/RenderCapabilities.h"

CCryDXGLGIAdapter::CCryDXGLGIAdapter(CCryDXGLGIFactory* pFactory, NCryOpenGL::SAdapter* pGLAdapter)
    : m_spGLAdapter(pGLAdapter)
    , m_spFactory(pFactory)
{
    DXGL_INITIALIZE_INTERFACE(DXGIAdapter)
    DXGL_INITIALIZE_INTERFACE(DXGIAdapter1)
}

CCryDXGLGIAdapter::~CCryDXGLGIAdapter()
{
}

bool CCryDXGLGIAdapter::Initialize()
{
    memset(&m_kDesc1, 0, sizeof(m_kDesc1));
    Unicode::Convert(m_kDesc.Description, m_spGLAdapter->m_strRenderer);
    memcpy(m_kDesc1.Description, m_kDesc.Description, sizeof(m_kDesc1.Description));
    m_kDesc1.VendorId = m_spGLAdapter->m_eDriverVendor;
    std::vector<NCryOpenGL::SOutputPtr> kGLOutputs;
    if (!NCryOpenGL::DetectOutputs(*m_spGLAdapter, m_spGLAdapter->m_kOutputs))
    {
        return false;
    }

    m_kOutputs.reserve(m_spGLAdapter->m_kOutputs.size());

    std::vector<NCryOpenGL::SOutputPtr>::const_iterator kGLOutputIter(m_spGLAdapter->m_kOutputs.begin());
    const std::vector<NCryOpenGL::SOutputPtr>::const_iterator kGLOutputEnd(m_spGLAdapter->m_kOutputs.end());
    for (; kGLOutputIter !=  kGLOutputEnd; ++kGLOutputIter)
    {
        _smart_ptr<CCryDXGLGIOutput> spOutput(new CCryDXGLGIOutput(*kGLOutputIter));
        if (!spOutput->Initialize())
        {
            return false;
        }
        m_kOutputs.push_back(spOutput);
    }

    DXGL_TODO("Detect from available extensions")
    m_eSupportedFeatureLevel = D3D_FEATURE_LEVEL_11_0;

    m_kDesc1.DedicatedVideoMemory = m_spGLAdapter->m_uVRAMBytes;

    return true;
}

D3D_FEATURE_LEVEL CCryDXGLGIAdapter::GetSupportedFeatureLevel()
{
    return m_eSupportedFeatureLevel;
}

NCryOpenGL::SAdapter* CCryDXGLGIAdapter::GetGLAdapter()
{
    return m_spGLAdapter.get();
}


////////////////////////////////////////////////////////////////////////////////
// IDXGIObject overrides
////////////////////////////////////////////////////////////////////////////////

HRESULT CCryDXGLGIAdapter::GetParent(REFIID riid, void** ppParent)
{
    IUnknown* pFactoryInterface;
    CCryDXGLBase::ToInterface(&pFactoryInterface, m_spFactory);
    if (pFactoryInterface->QueryInterface(riid, ppParent) == S_OK && ppParent != NULL)
    {
        return S_OK;
    }
    return CCryDXGLGIObject::GetParent(riid, ppParent);
}


////////////////////////////////////////////////////////////////////////////////
// IDXGIAdapter implementation
////////////////////////////////////////////////////////////////////////////////

HRESULT CCryDXGLGIAdapter::EnumOutputs(UINT Output, IDXGIOutput** ppOutput)
{
    if (Output >= m_kOutputs.size())
    {
        ppOutput = NULL;
        return DXGI_ERROR_NOT_FOUND;
    }

    CCryDXGLGIOutput::ToInterface(ppOutput, m_kOutputs.at(Output));
    (*ppOutput)->AddRef();

    return S_OK;
}

HRESULT CCryDXGLGIAdapter::GetDesc(DXGI_ADAPTER_DESC* pDesc)
{
    *pDesc = m_kDesc;
    return S_OK;
}

HRESULT CCryDXGLGIAdapter::CheckInterfaceSupport(REFGUID InterfaceName, LARGE_INTEGER* pUMDVersion)
{
    if (InterfaceName == __uuidof(ID3D10Device)
        || InterfaceName == __uuidof(ID3D11Device)
#if !DXGL_FULL_EMULATION
        || InterfaceName == __uuidof(CCryDXGLDevice)
#endif //!DXGL_FULL_EMULATION
        )
    {
        if (pUMDVersion != NULL)
        {
            DXGL_TODO("Put useful data here");
            pUMDVersion->HighPart = 0;
            pUMDVersion->LowPart = 0;
        }
        return S_OK;
    }
    return E_FAIL;
}


////////////////////////////////////////////////////////////////////////////////
// IDXGIAdapter1 implementation
////////////////////////////////////////////////////////////////////////////////

HRESULT CCryDXGLGIAdapter::GetDesc1(DXGI_ADAPTER_DESC1* pDesc)
{
    *pDesc = m_kDesc1;
    return S_OK;
}
