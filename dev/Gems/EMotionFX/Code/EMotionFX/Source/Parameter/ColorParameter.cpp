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

#include "ColorParameter.h"

#include <AzCore/Serialization/EditContext.h>
#include <AzCore/Serialization/SerializeContext.h>
#include <MCore/Source/AttributeColor.h>
#include <EMotionFX/Source/Allocators.h>


namespace EMotionFX
{
    AZ_CLASS_ALLOCATOR_IMPL(ColorParameter, AnimGraphAllocator, 0)


    void ColorParameter::Reflect(AZ::ReflectContext* context)
    {
        // This method calls Reflect() on it's parent class, which is uncommon
        // in the LY reflection framework.  This is because the parent class is
        // a template, and is unique to each type that subclasses it, as it
        // uses the Curiously Recursive Template Pattern.
        BaseType::Reflect(context);

        AZ::SerializeContext* serializeContext = azrtti_cast<AZ::SerializeContext*>(context);
        if (!serializeContext)
        {
            return;
        }

        serializeContext->Class<ColorParameter, BaseType>()
            ->Version(1)
        ;

        AZ::EditContext* editContext = serializeContext->GetEditContext();
        if (!editContext)
        {
            return;
        }

        editContext->Class<ColorParameter>("Color parameter", "")
            ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                ->Attribute(AZ::Edit::Attributes::Visibility, AZ::Edit::PropertyVisibility::ShowChildrenOnly)
        ;
    }

    const AZStd::string& ColorParameter::GetTypeDisplayName() const
    {
        static const AZStd::string typeDisplayName = "Color";
        return typeDisplayName;
    }

    MCore::Attribute* ColorParameter::ConstructDefaultValueAsAttribute() const
    {
        return MCore::AttributeColor::Create(MCore::RGBAColor(m_defaultValue.GetR(), m_defaultValue.GetG(), m_defaultValue.GetB(), m_defaultValue.GetA()));
    }

    uint32 ColorParameter::GetType() const
    {
        return MCore::AttributeColor::TYPE_ID;
    }

    bool ColorParameter::AssignDefaultValueToAttribute(MCore::Attribute* attribute) const
    {
        if (attribute->GetType() == MCore::AttributeColor::TYPE_ID)
        {
            static_cast<MCore::AttributeColor*>(attribute)->SetValue(GetDefaultValue());
            return true;
        }
        else
        {
            return false;
        }
    }

    bool ColorParameter::SetDefaultValueFromAttribute(MCore::Attribute* attribute)
    {
        if (attribute->GetType() == MCore::AttributeColor::TYPE_ID)
        {
            SetDefaultValue(static_cast<MCore::AttributeColor*>(attribute)->GetValue());
            return true;
        }
        else
        {
            return false;
        }
    }

    bool ColorParameter::SetMinValueFromAttribute(MCore::Attribute* attribute)
    {
        if (attribute->GetType() == MCore::AttributeColor::TYPE_ID)
        {
            SetMinValue(static_cast<MCore::AttributeColor*>(attribute)->GetValue());
            return true;
        }
        else
        {
            return false;
        }
    }

    bool ColorParameter::SetMaxValueFromAttribute(MCore::Attribute* attribute)
    {
        if (attribute->GetType() == MCore::AttributeColor::TYPE_ID)
        {
            SetMaxValue(static_cast<MCore::AttributeColor*>(attribute)->GetValue());
            return true;
        }
        else
        {
            return false;
        }
    }

    AZ::Color ColorParameter::GetUnboundedMinValue()
    {
        return AZ::Color(0.0f, 0.0f, 0.0f, 1.0f);
    }

    AZ::Color ColorParameter::GetUnboundedMaxValue()
    {
        return AZ::Color(1.0f, 1.0f, 1.0f, 1.0f);
    }
}
