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

// Description : Manages one-off reader/writer usages for Xml serialization


#ifndef CRYINCLUDE_CRYACTION_SERIALIZATION_XMLSERIALIZEHELPER_H
#define CRYINCLUDE_CRYACTION_SERIALIZATION_XMLSERIALIZEHELPER_H
#pragma once

#include "ISerializeHelper.h"

class CXmlSerializedObject
    : public ISerializedObject
{
public:
    CXmlSerializedObject(const char* szSection);
    virtual ~CXmlSerializedObject() {}

    enum
    {
        GUID = 0xD6BEE847
    };
    virtual uint32 GetGUID() const { return GUID; }
    virtual void GetMemoryUsage(ICrySizer* pSizer) const;

    virtual void AddRef() { ++m_nRefCount; }
    virtual void Release()
    {
        if (--m_nRefCount <= 0)
        {
            delete this;
        }
    }

    virtual bool IsEmpty() const;
    virtual void Reset();
    virtual void Serialize(TSerialize& serialize);

    void CreateRootNode();

    XmlNodeRef& GetXmlNode() { return m_XmlNode; }
    const XmlNodeRef& GetXmlNode() const { return m_XmlNode; }

private:
    string m_sTag;
    XmlNodeRef m_XmlNode;
    int m_nRefCount;
};

class CXmlSerializeHelper
    : public ISerializeHelper
{
public:
    CXmlSerializeHelper();
    virtual ~CXmlSerializeHelper();

    virtual void GetMemoryUsage(ICrySizer* pSizer) const;

    virtual void AddRef() { ++m_nRefCount; }
    virtual void Release()
    {
        if (--m_nRefCount <= 0)
        {
            delete this;
        }
    }

    virtual _smart_ptr<ISerializedObject> CreateSerializedObject(const char* szSection);
    virtual bool Write(ISerializedObject* pObject, TSerializeFunc serializeFunc, void* pArgument = NULL);
    virtual bool Read(ISerializedObject* pObject, TSerializeFunc serializeFunc, void* pArgument = NULL);

    // Local versions which work with XmlNodes directly
    ISerialize* GetWriter(XmlNodeRef& node);
    ISerialize* GetReader(XmlNodeRef& node);

private:
    static CXmlSerializedObject* GetXmlSerializedObject(ISerializedObject* pObject);

private:
    int m_nRefCount;
    _smart_ptr<IXmlSerializer> m_pSerializer;
};

#endif // CRYINCLUDE_CRYACTION_SERIALIZATION_XMLSERIALIZEHELPER_H
