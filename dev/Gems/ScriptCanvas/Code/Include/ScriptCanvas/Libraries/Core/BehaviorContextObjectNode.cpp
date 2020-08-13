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

#include "precompiled.h"

#include "BehaviorContextObjectNode.h"

#include <AzCore/RTTI/BehaviorContext.h>
#include <AzCore/std/string/string_view.h>
#include <ScriptCanvas/Data/PropertyTraits.h>

namespace ScriptCanvas
{
    namespace Nodes
    {
        namespace Core
        {
            namespace Internal
            {
                static const AZ::u32 k_thisParamIndex(0);
                static const AZ::u32 k_setValueParamIndex(1);
                static const AZ::u32 k_firstFirstPropertyDataSlotIndex(2);
                static const AZ::u32 k_valueArgumentIndex(1);
            } // namespace Internal

            AZStd::string BehaviorContextObjectNode::GetDebugName() const
            {
                if (auto input = GetInput(GetSlotId(k_setThis)))
                {
                    return AZStd::string::format("%s", Data::GetName(input->GetType()));
                }

                return "Invalid";
            }

            void BehaviorContextObjectNode::InitializeObject(const AZ::Uuid& azType)
            {
                // \todo this works with basic types, and it probably shouldn't
                if (auto bcClass = AZ::BehaviorContextHelper::GetClass(azType))
                {
                    InitializeObject(*bcClass);
                }
                else
                {
                    const void* defaultValue = nullptr;
                    if (Data::IsEntityID(azType))
                    {
                        defaultValue = &ScriptCanvas::SelfReferenceId;
                    }
                    AddInputAndOutputTypeSlot(Data::FromAZType(azType), defaultValue);
                }
            }

            void BehaviorContextObjectNode::InitializeObject(const AZStd::string& classNameString)
            {
                if (auto bcClass = AZ::BehaviorContextHelper::GetClass(classNameString))
                {
                    InitializeObject(*bcClass);
                }
            }

            void BehaviorContextObjectNode::InitializeObject(const AZ::BehaviorClass& behaviorClass)
            {
                m_className = behaviorClass.m_name;
                const void* defaultValue = nullptr;
                if (Data::IsEntityID(behaviorClass.m_typeId))
                {
                    defaultValue = &ScriptCanvas::SelfReferenceId;
                }
                AddInputAndOutputTypeSlot(Data::FromAZType(behaviorClass.m_typeId), defaultValue);
                ConfigureProperties(behaviorClass);
            }

            void BehaviorContextObjectNode::InitializeObject(const Data::Type& type)
            {
                if (auto bcClass = AZ::BehaviorContextHelper::GetClass(type.GetAZType()))
                {
                    InitializeObject(*bcClass);
                }
            }

            void BehaviorContextObjectNode::ConfigureSetters(const AZ::BehaviorClass& behaviorClass)
            {
                Data::SetterContainer setterWrappers = Data::ExplodeToSetters(Data::FromAZType(behaviorClass.m_typeId));
                for (const auto& setterWrapperPair : setterWrappers)
                {
                    SlotId setterSlotId;
                    auto propertyIt = behaviorClass.m_properties.find(setterWrapperPair.first);
                    if (propertyIt != behaviorClass.m_properties.end())
                    {
                        const Data::SetterWrapper& setterWrapper = setterWrapperPair.second;
                        const AZStd::string argName = AZStd::string::format("%s: %s", Data::GetName(setterWrapper.m_propertyType), setterWrapper.m_propertyName.data());
                        const AZStd::string* argumentTooltipPtr = propertyIt->second->m_setter->GetArgumentToolTip(Internal::k_setValueParamIndex);
                        AZStd::string_view argumentTooltip = argumentTooltipPtr ? AZStd::string_view(*argumentTooltipPtr) : AZStd::string_view{};
                        // Add the slot if it doesn't exist
                        if (!SlotExists(argName, SlotType::DataIn, setterSlotId))
                        {
                            setterSlotId = AddInputTypeSlot(argName, argumentTooltip, setterWrapper.m_propertyType, InputTypeContract::DatumType);
                        }

                    }
                    if (setterSlotId.IsValid())
                    {
                        m_propertyAccount.m_getterSetterIdPairs[setterWrapperPair.first].second = setterSlotId;
                        m_propertyAccount.m_settersByInputSlot.emplace(setterSlotId, setterWrapperPair.second);
                    }
                }
            }

            void BehaviorContextObjectNode::ConfigureGetters(const AZ::BehaviorClass& behaviorClass)
            {
                Data::GetterContainer getterWrappers = Data::ExplodeToGetters(Data::FromAZType(behaviorClass.m_typeId));
                for (const auto& getterWrapperPair : getterWrappers)
                {
                    SlotId getterSlotId;
                    auto propertyIt = behaviorClass.m_properties.find(getterWrapperPair.first);
                    if (propertyIt != behaviorClass.m_properties.end())
                    {
                        const Data::GetterWrapper& getterWrapper = getterWrapperPair.second;
                        const AZStd::string resultSlotName(AZStd::string::format("%s: %s", getterWrapper.m_propertyName.data(), Data::GetName(getterWrapper.m_propertyType)));
                        // Add the slot if it doesn't exist
                        if (!SlotExists(resultSlotName, SlotType::DataOut, getterSlotId))
                        {
                            getterSlotId = AddOutputTypeSlot(resultSlotName, {}, getterWrapper.m_propertyType, OutputStorage::Optional);
                        }

                    }
                    if (getterSlotId.IsValid())
                    {
                        m_propertyAccount.m_getterSetterIdPairs[getterWrapperPair.first].first = getterSlotId;
                        m_propertyAccount.m_gettersByInputSlot.emplace(getterSlotId, getterWrapperPair.second);
                    }
                }
            }

            void BehaviorContextObjectNode::ConfigureProperties(const AZ::BehaviorClass& behaviorClass)
            {
                if (IsConfigured())
                {
                    return;
                }

                ConfigureGetters(behaviorClass);
                ConfigureSetters(behaviorClass);
                m_configured = true;
            }

            void BehaviorContextObjectNode::OnInit()
            {
                if (auto input = GetInput(GetSlotId(k_setThis)))
                {
                    if (!input->Empty())
                    {
                        AddInputTypeAndOutputTypeSlot(input->GetType());
                    }
                }
            }

            void BehaviorContextObjectNode::OnWriteEnd()
            {
                AZStd::lock_guard<AZStd::recursive_mutex> lock(m_mutex);

                auto bcClass = !m_className.empty() ? AZ::BehaviorContextHelper::GetClass(m_className) : nullptr;

                if (bcClass)
                {
                    ConfigureProperties(*bcClass);
                }
            }


            void BehaviorContextObjectNode::Reflect(AZ::ReflectContext* reflectContext)
            {
                if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(reflectContext))
                {
                    serializeContext->Class<BehaviorContextObjectNode, Node>()
                        ->Version(1)
                        ->EventHandler<SerializeContextEventHandlerDefault<BehaviorContextObjectNode>>()
                        ->Field("m_className", &BehaviorContextObjectNode::m_className)
                        ;

                    if (AZ::EditContext* editContext = serializeContext->GetEditContext())
                    {
                        editContext->Class<BehaviorContextObjectNode>("BehaviorContextObjectNode", "BehaviorContextObjectNode")
                            ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                            ->Attribute(AZ::Script::Attributes::ExcludeFrom, AZ::Script::Attributes::ExcludeFlags::List)
                            ;
                    }
                }
            }

        } // namespace Core
    } // namespace Nodes
} // namespace ScriptCanvas
