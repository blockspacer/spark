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

#include <AzCore/std/string/string.h>
#include <AzCore/Component/EntityUtils.h>

#include <GraphCanvas/Styling/Selector.h>

#include <QDebug>

namespace GraphCanvas
{
    namespace Styling
    {

        class BasicSelector
            : public SelectorImplementation
        {
        public:
            AZ_RTTI(BasicSelector, "{4DB9CEB8-F996-4106-A6C9-15034651F494}", SelectorImplementation);
            AZ_CLASS_ALLOCATOR(BasicSelector, AZ::SystemAllocator, 0);

            static void Reflect(AZ::ReflectContext* context);

            BasicSelector(const AZStd::string& value = AZStd::string());
            virtual ~BasicSelector() = default;

            int GetComplexity() const override { return 1; }
            bool Matches(const AZ::EntityId& object) const override;
            AZStd::string ToString() const override { return m_value; }

            bool operator==(const SelectorImplementation& other) const override
            {
                const BasicSelector* down = azrtti_cast<const BasicSelector*>(&other);
                return down && m_hash == down->m_hash && m_value == down->m_value;
            };

            SelectorImplementation* Clone() const override { return aznew BasicSelector(m_value); }

        private:
            AZStd::string m_value;
            AZStd::hash<AZStd::string>::result_type m_hash;

            friend class BasicSelectorEventHandler;
        };

        class DefaultSelector
            : public SelectorImplementation
        {
        public:
            AZ_RTTI(DefaultSelector, "{71234315-6975-4A03-8EDF-F5C7E5639781}", SelectorImplementation);
            AZ_CLASS_ALLOCATOR(DefaultSelector, AZ::SystemAllocator, 0);

            static void Reflect(AZ::ReflectContext* context);

            DefaultSelector() = default;
            DefaultSelector(SelectorImplementation* value);
			DefaultSelector(const DefaultSelector& other)
			: m_actual(other.Clone())
			, m_value(other.m_value)
			{}

            virtual ~DefaultSelector() = default;

            int GetComplexity() const override { return -m_actual->GetComplexity(); }
            bool Matches(const AZ::EntityId& object) const override { return m_actual->Matches(object); }
            AZStd::string ToString() const override { return m_value; }

            bool operator==(const SelectorImplementation& other) const override
            {
                const DefaultSelector* down = azrtti_cast<const DefaultSelector*>(&other);
                return down && *m_actual == *down->m_actual;
            };

            SelectorImplementation* Clone() const override { return aznew DefaultSelector(m_actual->Clone()); }

        private:
            AZStd::unique_ptr<SelectorImplementation> m_actual;
            AZStd::string m_value;
        };

        class CompoundSelector
            : public SelectorImplementation
        {
        public:
            AZ_RTTI(CompoundSelector, "{09063F80-E4FB-4A43-AF09-DA55D2E6B261}", SelectorImplementation);
            AZ_CLASS_ALLOCATOR(CompoundSelector, AZ::SystemAllocator, 0);

            static void Reflect(AZ::ReflectContext* context);

            CompoundSelector() = default;
            CompoundSelector(const CompoundSelector& other) = default;
            CompoundSelector(SelectorVector&& parts);
            CompoundSelector& operator=(const CompoundSelector&) = delete;
            virtual ~CompoundSelector() = default;

            int GetComplexity() const override { return m_complexity; }
            bool Matches(const AZ::EntityId& object) const override;
            AZStd::string ToString() const override { return m_value; }

            bool operator==(const SelectorImplementation& other) const override
            {
                const CompoundSelector* down = azrtti_cast<const CompoundSelector*>(&other);
                return down && m_parts == down->m_parts;
            };

            SelectorImplementation* Clone() const override { return aznew CompoundSelector(*this); }

        private:
            SelectorVector m_parts;
            int m_complexity;
            AZStd::string m_value;
        };

        class NestedSelector
            : public SelectorImplementation
        {
        public:
            AZ_RTTI(NestedSelector, "{5D728275-A59C-4A22-9B28-FCECF169EF31}", SelectorImplementation);
            AZ_CLASS_ALLOCATOR(NestedSelector, AZ::SystemAllocator, 0);

            static void Reflect(AZ::ReflectContext* context);

            NestedSelector() = default;
            NestedSelector(const NestedSelector& other) = default;
            NestedSelector(SelectorVector&& parts);
            NestedSelector& operator=(const NestedSelector&) = delete;
            virtual ~NestedSelector() = default;

            int GetComplexity() const override { return m_complexity; }
            bool Matches(const AZ::EntityId& object) const override;
            AZStd::string ToString() const override { return m_value; }

            bool operator==(const SelectorImplementation& other) const override
            {
                const NestedSelector* down = azrtti_cast<const NestedSelector*>(&other);
                return down && m_parts == down->m_parts;
            };

            SelectorImplementation* Clone() const override { return aznew NestedSelector(*this); }

        private:
            SelectorVector m_parts;
            int m_complexity;
            AZStd::string m_value;
        };

    }
}