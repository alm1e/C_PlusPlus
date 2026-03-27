// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MarketplacePlugins/HealthComponent.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeHealthComponent() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
MARKETPLACEPLUGINS_API UClass* Z_Construct_UClass_UHealthComponent();
MARKETPLACEPLUGINS_API UClass* Z_Construct_UClass_UHealthComponent_NoRegister();
MARKETPLACEPLUGINS_API UFunction* Z_Construct_UDelegateFunction_MarketplacePlugins_OnAttributeChangedSignature__DelegateSignature();
MARKETPLACEPLUGINS_API UFunction* Z_Construct_UDelegateFunction_MarketplacePlugins_OnDeathSignature__DelegateSignature();
MARKETPLACEPLUGINS_API UFunction* Z_Construct_UDelegateFunction_MarketplacePlugins_OnStaminaChangedSignature__DelegateSignature();
UPackage* Z_Construct_UPackage__Script_MarketplacePlugins();
// ********** End Cross Module References **********************************************************

// ********** Begin Delegate FOnDeathSignature *****************************************************
struct Z_Construct_UDelegateFunction_MarketplacePlugins_OnDeathSignature__DelegateSignature_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "HealthComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FOnDeathSignature constinit property declarations *********************
// ********** End Delegate FOnDeathSignature constinit property declarations ***********************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_MarketplacePlugins_OnDeathSignature__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_MarketplacePlugins, nullptr, "OnDeathSignature__DelegateSignature", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_MarketplacePlugins_OnDeathSignature__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_MarketplacePlugins_OnDeathSignature__DelegateSignature_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UDelegateFunction_MarketplacePlugins_OnDeathSignature__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_MarketplacePlugins_OnDeathSignature__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnDeathSignature_DelegateWrapper(const FMulticastScriptDelegate& OnDeathSignature)
{
	OnDeathSignature.ProcessMulticastDelegate<UObject>(NULL);
}
// ********** End Delegate FOnDeathSignature *******************************************************

// ********** Begin Delegate FOnAttributeChangedSignature ******************************************
struct Z_Construct_UDelegateFunction_MarketplacePlugins_OnAttributeChangedSignature__DelegateSignature_Statics
{
	struct _Script_MarketplacePlugins_eventOnAttributeChangedSignature_Parms
	{
		float CurrentValue;
		float MaxValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "HealthComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FOnAttributeChangedSignature constinit property declarations **********
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CurrentValue;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FOnAttributeChangedSignature constinit property declarations ************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FOnAttributeChangedSignature Property Definitions *********************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UDelegateFunction_MarketplacePlugins_OnAttributeChangedSignature__DelegateSignature_Statics::NewProp_CurrentValue = { "CurrentValue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_MarketplacePlugins_eventOnAttributeChangedSignature_Parms, CurrentValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UDelegateFunction_MarketplacePlugins_OnAttributeChangedSignature__DelegateSignature_Statics::NewProp_MaxValue = { "MaxValue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_MarketplacePlugins_eventOnAttributeChangedSignature_Parms, MaxValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_MarketplacePlugins_OnAttributeChangedSignature__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_MarketplacePlugins_OnAttributeChangedSignature__DelegateSignature_Statics::NewProp_CurrentValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_MarketplacePlugins_OnAttributeChangedSignature__DelegateSignature_Statics::NewProp_MaxValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_MarketplacePlugins_OnAttributeChangedSignature__DelegateSignature_Statics::PropPointers) < 2048);
// ********** End Delegate FOnAttributeChangedSignature Property Definitions ***********************
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_MarketplacePlugins_OnAttributeChangedSignature__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_MarketplacePlugins, nullptr, "OnAttributeChangedSignature__DelegateSignature", 	Z_Construct_UDelegateFunction_MarketplacePlugins_OnAttributeChangedSignature__DelegateSignature_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_MarketplacePlugins_OnAttributeChangedSignature__DelegateSignature_Statics::PropPointers), 
sizeof(Z_Construct_UDelegateFunction_MarketplacePlugins_OnAttributeChangedSignature__DelegateSignature_Statics::_Script_MarketplacePlugins_eventOnAttributeChangedSignature_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_MarketplacePlugins_OnAttributeChangedSignature__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_MarketplacePlugins_OnAttributeChangedSignature__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_MarketplacePlugins_OnAttributeChangedSignature__DelegateSignature_Statics::_Script_MarketplacePlugins_eventOnAttributeChangedSignature_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_MarketplacePlugins_OnAttributeChangedSignature__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_MarketplacePlugins_OnAttributeChangedSignature__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnAttributeChangedSignature_DelegateWrapper(const FMulticastScriptDelegate& OnAttributeChangedSignature, float CurrentValue, float MaxValue)
{
	struct _Script_MarketplacePlugins_eventOnAttributeChangedSignature_Parms
	{
		float CurrentValue;
		float MaxValue;
	};
	_Script_MarketplacePlugins_eventOnAttributeChangedSignature_Parms Parms;
	Parms.CurrentValue=CurrentValue;
	Parms.MaxValue=MaxValue;
	OnAttributeChangedSignature.ProcessMulticastDelegate<UObject>(&Parms);
}
// ********** End Delegate FOnAttributeChangedSignature ********************************************

// ********** Begin Delegate FOnStaminaChangedSignature ********************************************
struct Z_Construct_UDelegateFunction_MarketplacePlugins_OnStaminaChangedSignature__DelegateSignature_Statics
{
	struct _Script_MarketplacePlugins_eventOnStaminaChangedSignature_Parms
	{
		float CurrentStamina;
		float MaxStamina;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "HealthComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FOnStaminaChangedSignature constinit property declarations ************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CurrentStamina;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxStamina;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FOnStaminaChangedSignature constinit property declarations **************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FOnStaminaChangedSignature Property Definitions ***********************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UDelegateFunction_MarketplacePlugins_OnStaminaChangedSignature__DelegateSignature_Statics::NewProp_CurrentStamina = { "CurrentStamina", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_MarketplacePlugins_eventOnStaminaChangedSignature_Parms, CurrentStamina), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UDelegateFunction_MarketplacePlugins_OnStaminaChangedSignature__DelegateSignature_Statics::NewProp_MaxStamina = { "MaxStamina", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_MarketplacePlugins_eventOnStaminaChangedSignature_Parms, MaxStamina), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_MarketplacePlugins_OnStaminaChangedSignature__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_MarketplacePlugins_OnStaminaChangedSignature__DelegateSignature_Statics::NewProp_CurrentStamina,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_MarketplacePlugins_OnStaminaChangedSignature__DelegateSignature_Statics::NewProp_MaxStamina,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_MarketplacePlugins_OnStaminaChangedSignature__DelegateSignature_Statics::PropPointers) < 2048);
// ********** End Delegate FOnStaminaChangedSignature Property Definitions *************************
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_MarketplacePlugins_OnStaminaChangedSignature__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_MarketplacePlugins, nullptr, "OnStaminaChangedSignature__DelegateSignature", 	Z_Construct_UDelegateFunction_MarketplacePlugins_OnStaminaChangedSignature__DelegateSignature_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_MarketplacePlugins_OnStaminaChangedSignature__DelegateSignature_Statics::PropPointers), 
sizeof(Z_Construct_UDelegateFunction_MarketplacePlugins_OnStaminaChangedSignature__DelegateSignature_Statics::_Script_MarketplacePlugins_eventOnStaminaChangedSignature_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_MarketplacePlugins_OnStaminaChangedSignature__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_MarketplacePlugins_OnStaminaChangedSignature__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_MarketplacePlugins_OnStaminaChangedSignature__DelegateSignature_Statics::_Script_MarketplacePlugins_eventOnStaminaChangedSignature_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_MarketplacePlugins_OnStaminaChangedSignature__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_MarketplacePlugins_OnStaminaChangedSignature__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnStaminaChangedSignature_DelegateWrapper(const FMulticastScriptDelegate& OnStaminaChangedSignature, float CurrentStamina, float MaxStamina)
{
	struct _Script_MarketplacePlugins_eventOnStaminaChangedSignature_Parms
	{
		float CurrentStamina;
		float MaxStamina;
	};
	_Script_MarketplacePlugins_eventOnStaminaChangedSignature_Parms Parms;
	Parms.CurrentStamina=CurrentStamina;
	Parms.MaxStamina=MaxStamina;
	OnStaminaChangedSignature.ProcessMulticastDelegate<UObject>(&Parms);
}
// ********** End Delegate FOnStaminaChangedSignature **********************************************

// ********** Begin Class UHealthComponent Function TakeDamage *************************************
struct Z_Construct_UFunction_UHealthComponent_TakeDamage_Statics
{
	struct HealthComponent_eventTakeDamage_Parms
	{
		float DamageAmount;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Health System" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// TakeDamage\n" },
#endif
		{ "ModuleRelativePath", "HealthComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "TakeDamage" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function TakeDamage constinit property declarations ****************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DamageAmount;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function TakeDamage constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function TakeDamage Property Definitions ***************************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UHealthComponent_TakeDamage_Statics::NewProp_DamageAmount = { "DamageAmount", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(HealthComponent_eventTakeDamage_Parms, DamageAmount), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHealthComponent_TakeDamage_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHealthComponent_TakeDamage_Statics::NewProp_DamageAmount,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UHealthComponent_TakeDamage_Statics::PropPointers) < 2048);
// ********** End Function TakeDamage Property Definitions *****************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UHealthComponent_TakeDamage_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UHealthComponent, nullptr, "TakeDamage", 	Z_Construct_UFunction_UHealthComponent_TakeDamage_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UHealthComponent_TakeDamage_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UHealthComponent_TakeDamage_Statics::HealthComponent_eventTakeDamage_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UHealthComponent_TakeDamage_Statics::Function_MetaDataParams), Z_Construct_UFunction_UHealthComponent_TakeDamage_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UHealthComponent_TakeDamage_Statics::HealthComponent_eventTakeDamage_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UHealthComponent_TakeDamage()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UHealthComponent_TakeDamage_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UHealthComponent::execTakeDamage)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_DamageAmount);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->TakeDamage(Z_Param_DamageAmount);
	P_NATIVE_END;
}
// ********** End Class UHealthComponent Function TakeDamage ***************************************

// ********** Begin Class UHealthComponent Function UseStamina *************************************
struct Z_Construct_UFunction_UHealthComponent_UseStamina_Statics
{
	struct HealthComponent_eventUseStamina_Parms
	{
		float Amount;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Stamina" },
		{ "ModuleRelativePath", "HealthComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function UseStamina constinit property declarations ****************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Amount;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function UseStamina constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function UseStamina Property Definitions ***************************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UHealthComponent_UseStamina_Statics::NewProp_Amount = { "Amount", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(HealthComponent_eventUseStamina_Parms, Amount), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHealthComponent_UseStamina_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHealthComponent_UseStamina_Statics::NewProp_Amount,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UHealthComponent_UseStamina_Statics::PropPointers) < 2048);
// ********** End Function UseStamina Property Definitions *****************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UHealthComponent_UseStamina_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UHealthComponent, nullptr, "UseStamina", 	Z_Construct_UFunction_UHealthComponent_UseStamina_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UHealthComponent_UseStamina_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UHealthComponent_UseStamina_Statics::HealthComponent_eventUseStamina_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UHealthComponent_UseStamina_Statics::Function_MetaDataParams), Z_Construct_UFunction_UHealthComponent_UseStamina_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UHealthComponent_UseStamina_Statics::HealthComponent_eventUseStamina_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UHealthComponent_UseStamina()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UHealthComponent_UseStamina_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UHealthComponent::execUseStamina)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_Amount);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->UseStamina(Z_Param_Amount);
	P_NATIVE_END;
}
// ********** End Class UHealthComponent Function UseStamina ***************************************

// ********** Begin Class UHealthComponent *********************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UHealthComponent;
UClass* UHealthComponent::GetPrivateStaticClass()
{
	using TClass = UHealthComponent;
	if (!Z_Registration_Info_UClass_UHealthComponent.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("HealthComponent"),
			Z_Registration_Info_UClass_UHealthComponent.InnerSingleton,
			StaticRegisterNativesUHealthComponent,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_UHealthComponent.InnerSingleton;
}
UClass* Z_Construct_UClass_UHealthComponent_NoRegister()
{
	return UHealthComponent::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UHealthComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "HealthComponent.h" },
		{ "ModuleRelativePath", "HealthComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxHealth_MetaData[] = {
		{ "Category", "Health System" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//HP\n" },
#endif
		{ "ModuleRelativePath", "HealthComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "HP" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentHealth_MetaData[] = {
		{ "Category", "Health System" },
		{ "ModuleRelativePath", "HealthComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnDeath_MetaData[] = {
		{ "Category", "Health System" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//Death\n" },
#endif
		{ "ModuleRelativePath", "HealthComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Death" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnHealthChanged_MetaData[] = {
		{ "Category", "Health System" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Optimization for Tick UI\n" },
#endif
		{ "ModuleRelativePath", "HealthComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Optimization for Tick UI" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bCanRegenerate_MetaData[] = {
		{ "Category", "Health System" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// HP Regeneration\n" },
#endif
		{ "ModuleRelativePath", "HealthComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "HP Regeneration" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RegenRate_MetaData[] = {
		{ "Category", "Health System" },
		{ "ModuleRelativePath", "HealthComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxStamina_MetaData[] = {
		{ "Category", "Stamina" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//Stamina\n" },
#endif
		{ "ModuleRelativePath", "HealthComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Stamina" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentStamina_MetaData[] = {
		{ "Category", "Stamina" },
		{ "ModuleRelativePath", "HealthComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StaminaRegenRate_MetaData[] = {
		{ "Category", "Stamina" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//Stamina Regeneration\n" },
#endif
		{ "ModuleRelativePath", "HealthComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Stamina Regeneration" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnStaminaChanged_MetaData[] = {
		{ "Category", "Stamina" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Optimization for Tick UI\n" },
#endif
		{ "ModuleRelativePath", "HealthComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Optimization for Tick UI" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UHealthComponent constinit property declarations *************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxHealth;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CurrentHealth;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnDeath;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnHealthChanged;
	static void NewProp_bCanRegenerate_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bCanRegenerate;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_RegenRate;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxStamina;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CurrentStamina;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_StaminaRegenRate;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnStaminaChanged;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UHealthComponent constinit property declarations ***************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("TakeDamage"), .Pointer = &UHealthComponent::execTakeDamage },
		{ .NameUTF8 = UTF8TEXT("UseStamina"), .Pointer = &UHealthComponent::execUseStamina },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UHealthComponent_TakeDamage, "TakeDamage" }, // 3927035587
		{ &Z_Construct_UFunction_UHealthComponent_UseStamina, "UseStamina" }, // 1269407141
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UHealthComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UHealthComponent_Statics

// ********** Begin Class UHealthComponent Property Definitions ************************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UHealthComponent_Statics::NewProp_MaxHealth = { "MaxHealth", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthComponent, MaxHealth), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxHealth_MetaData), NewProp_MaxHealth_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UHealthComponent_Statics::NewProp_CurrentHealth = { "CurrentHealth", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthComponent, CurrentHealth), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentHealth_MetaData), NewProp_CurrentHealth_MetaData) };
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UHealthComponent_Statics::NewProp_OnDeath = { "OnDeath", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthComponent, OnDeath), Z_Construct_UDelegateFunction_MarketplacePlugins_OnDeathSignature__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnDeath_MetaData), NewProp_OnDeath_MetaData) }; // 2158370693
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UHealthComponent_Statics::NewProp_OnHealthChanged = { "OnHealthChanged", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthComponent, OnHealthChanged), Z_Construct_UDelegateFunction_MarketplacePlugins_OnAttributeChangedSignature__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnHealthChanged_MetaData), NewProp_OnHealthChanged_MetaData) }; // 1317928188
void Z_Construct_UClass_UHealthComponent_Statics::NewProp_bCanRegenerate_SetBit(void* Obj)
{
	((UHealthComponent*)Obj)->bCanRegenerate = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UHealthComponent_Statics::NewProp_bCanRegenerate = { "bCanRegenerate", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UHealthComponent), &Z_Construct_UClass_UHealthComponent_Statics::NewProp_bCanRegenerate_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bCanRegenerate_MetaData), NewProp_bCanRegenerate_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UHealthComponent_Statics::NewProp_RegenRate = { "RegenRate", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthComponent, RegenRate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RegenRate_MetaData), NewProp_RegenRate_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UHealthComponent_Statics::NewProp_MaxStamina = { "MaxStamina", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthComponent, MaxStamina), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxStamina_MetaData), NewProp_MaxStamina_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UHealthComponent_Statics::NewProp_CurrentStamina = { "CurrentStamina", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthComponent, CurrentStamina), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentStamina_MetaData), NewProp_CurrentStamina_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UHealthComponent_Statics::NewProp_StaminaRegenRate = { "StaminaRegenRate", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthComponent, StaminaRegenRate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StaminaRegenRate_MetaData), NewProp_StaminaRegenRate_MetaData) };
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UHealthComponent_Statics::NewProp_OnStaminaChanged = { "OnStaminaChanged", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthComponent, OnStaminaChanged), Z_Construct_UDelegateFunction_MarketplacePlugins_OnStaminaChangedSignature__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnStaminaChanged_MetaData), NewProp_OnStaminaChanged_MetaData) }; // 1864644512
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UHealthComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthComponent_Statics::NewProp_MaxHealth,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthComponent_Statics::NewProp_CurrentHealth,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthComponent_Statics::NewProp_OnDeath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthComponent_Statics::NewProp_OnHealthChanged,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthComponent_Statics::NewProp_bCanRegenerate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthComponent_Statics::NewProp_RegenRate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthComponent_Statics::NewProp_MaxStamina,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthComponent_Statics::NewProp_CurrentStamina,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthComponent_Statics::NewProp_StaminaRegenRate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthComponent_Statics::NewProp_OnStaminaChanged,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UHealthComponent_Statics::PropPointers) < 2048);
// ********** End Class UHealthComponent Property Definitions **************************************
UObject* (*const Z_Construct_UClass_UHealthComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UActorComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_MarketplacePlugins,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UHealthComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UHealthComponent_Statics::ClassParams = {
	&UHealthComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UHealthComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UHealthComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UHealthComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UHealthComponent_Statics::Class_MetaDataParams)
};
void UHealthComponent::StaticRegisterNativesUHealthComponent()
{
	UClass* Class = UHealthComponent::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UHealthComponent_Statics::Funcs));
}
UClass* Z_Construct_UClass_UHealthComponent()
{
	if (!Z_Registration_Info_UClass_UHealthComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UHealthComponent.OuterSingleton, Z_Construct_UClass_UHealthComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UHealthComponent.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UHealthComponent);
UHealthComponent::~UHealthComponent() {}
// ********** End Class UHealthComponent ***********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_MarketplacePlugins_Source_MarketplacePlugins_HealthComponent_h__Script_MarketplacePlugins_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UHealthComponent, UHealthComponent::StaticClass, TEXT("UHealthComponent"), &Z_Registration_Info_UClass_UHealthComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UHealthComponent), 4190331088U) },
	};
}; // Z_CompiledInDeferFile_FID_MarketplacePlugins_Source_MarketplacePlugins_HealthComponent_h__Script_MarketplacePlugins_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_MarketplacePlugins_Source_MarketplacePlugins_HealthComponent_h__Script_MarketplacePlugins_1048662060{
	TEXT("/Script/MarketplacePlugins"),
	Z_CompiledInDeferFile_FID_MarketplacePlugins_Source_MarketplacePlugins_HealthComponent_h__Script_MarketplacePlugins_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_MarketplacePlugins_Source_MarketplacePlugins_HealthComponent_h__Script_MarketplacePlugins_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
