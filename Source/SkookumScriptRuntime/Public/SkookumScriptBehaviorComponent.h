//=======================================================================================
// Copyright (c) 2001-2017 Agog Labs Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//=======================================================================================

//=======================================================================================
// SkookumScript Plugin for Unreal Engine 4
//
// Component to associate a SkookumScript class and data members with a UE4 actor
// and allow SkookumScript ctors and dtors to be called when the actor (i.e. the component) gets created/destroyed
//=======================================================================================

#pragma once

//=======================================================================================
// Includes
//=======================================================================================

#include "Components/ActorComponent.h"

#include <AgogCore/AIdPtr.hpp>
#include <AgogCore/ASymbol.hpp>
#include <SkookumScript/SkInstance.hpp>

#include "SkookumScriptBehaviorComponent.generated.h"

//=======================================================================================
// Global Defines / Macros
//=======================================================================================

//=======================================================================================
// Global Structures
//=======================================================================================

//---------------------------------------------------------------------------------------
// Allows you to create a custom SkookumScript component by deriving from the SkookumScriptBehaviorComponent class. Dynamically attach and detach to/from any actor as you like via script.
UCLASS(classGroup=Scripting, editinlinenew, BlueprintType, meta=(BlueprintSpawnableComponent), hideCategories=(Object, ActorComponent))
class SKOOKUMSCRIPTRUNTIME_API USkookumScriptBehaviorComponent : public UActorComponent
  {

    GENERATED_UCLASS_BODY()

  public:

  // Public Data Members

    // SkookumScript subclass of this SkookumScriptBehaviorComponent - used to create appropriate SkookumScript component instance
    // Must not be blank if instantiated via Blueprints.
    UPROPERTY(Category = Script, EditAnywhere, BlueprintReadOnly)
    FString ScriptComponentClassName;

  // Methods

    // Static initialization/deinitialization
    static void initialize();
    static void deinitialize();

    // Attach/detach to/from Outer actor
    void attach(SkInstance * instance_p);
    void detach();

    // Gets our SkookumScript instance
    SkInstance * get_sk_component_instance() const { return m_component_instance_p; }

  protected:

    // UActorComponent interface
    virtual void OnRegister() override;
    virtual void InitializeComponent() override;
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type end_play_reason) override;
    virtual void UninitializeComponent() override;
    virtual void OnUnregister() override;

    // Creates/deletes our SkookumScript instance
    void        create_sk_instance();
    void        delete_sk_instance();
    void        set_sk_component_instance(SkInstance * instance_p); // Sets externally created SkookumScript instance

    // Keep the SkookumScript instance belonging to this component around
    AIdPtr<SkInstance> m_component_instance_p;

    // If someone else created our instance, not us
    bool m_is_instance_externally_owned;

    // Names of callback methods we need to call occasionally
    static ASymbol ms_symbol_on_attach;
    static ASymbol ms_symbol_on_detach;
    static ASymbol ms_symbol_on_begin_play;
    static ASymbol ms_symbol_on_end_play;

  };  // USkookumScriptBehaviorComponent


//=======================================================================================
// Inline Functions
//=======================================================================================

