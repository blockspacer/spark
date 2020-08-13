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

#include <AzCore/Component/ComponentBus.h>
#include <LyShine/Bus/UiLayoutBus.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
class UiLayoutColumnInterface
    : public AZ::ComponentBus
{
public: // member functions

    virtual ~UiLayoutColumnInterface() {}

    //! Get the padding (in pixels) inside the edges of the element
    virtual UiLayoutInterface::Padding GetPadding() = 0;

    //! Set the padding (in pixels) inside the edges of the element
    virtual void SetPadding(UiLayoutInterface::Padding padding) = 0;

    //! Get the spacing (in pixels) between child elements
    virtual float GetSpacing() = 0;

    //! Set the spacing (in pixels) between child elements
    virtual void SetSpacing(float spacing) = 0;

    //! Get the vertical order for this layout
    virtual UiLayoutInterface::VerticalOrder GetOrder() = 0;

    //! Set the vertical order for this layout
    virtual void SetOrder(UiLayoutInterface::VerticalOrder order) = 0;

public: // static member data

    //! Only one component on a entity can implement the events
    static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
};

typedef AZ::EBus<UiLayoutColumnInterface> UiLayoutColumnBus;

