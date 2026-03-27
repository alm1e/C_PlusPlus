// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "HealthComponent.h"

#ifdef MARKETPLACEPLUGINS_HealthComponent_generated_h
#error "HealthComponent.generated.h already included, missing '#pragma once' in HealthComponent.h"
#endif
#define MARKETPLACEPLUGINS_HealthComponent_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Delegate FOnDeathSignature *****************************************************
#define FID_MarketplacePlugins_Source_MarketplacePlugins_HealthComponent_h_9_DELEGATE \
MARKETPLACEPLUGINS_API void FOnDeathSignature_DelegateWrapper(const FMulticastScriptDelegate& OnDeathSignature);


// ********** End Delegate FOnDeathSignature *******************************************************

// ********** Begin Delegate FOnAttributeChangedSignature ******************************************
#define FID_MarketplacePlugins_Source_MarketplacePlugins_HealthComponent_h_10_DELEGATE \
MARKETPLACEPLUGINS_API void FOnAttributeChangedSignature_DelegateWrapper(const FMulticastScriptDelegate& OnAttributeChangedSignature, float CurrentValue, float MaxValue);


// ********** End Delegate FOnAttributeChangedSignature ********************************************

// ********** Begin Delegate FOnStaminaChangedSignature ********************************************
#define FID_MarketplacePlugins_Source_MarketplacePlugins_HealthComponent_h_11_DELEGATE \
MARKETPLACEPLUGINS_API void FOnStaminaChangedSignature_DelegateWrapper(const FMulticastScriptDelegate& OnStaminaChangedSignature, float CurrentStamina, float MaxStamina);


// ********** End Delegate FOnStaminaChangedSignature **********************************************

// ********** Begin Class UHealthComponent *********************************************************
#define FID_MarketplacePlugins_Source_MarketplacePlugins_HealthComponent_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execUseStamina); \
	DECLARE_FUNCTION(execTakeDamage);


struct Z_Construct_UClass_UHealthComponent_Statics;
MARKETPLACEPLUGINS_API UClass* Z_Construct_UClass_UHealthComponent_NoRegister();

#define FID_MarketplacePlugins_Source_MarketplacePlugins_HealthComponent_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUHealthComponent(); \
	friend struct ::Z_Construct_UClass_UHealthComponent_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend MARKETPLACEPLUGINS_API UClass* ::Z_Construct_UClass_UHealthComponent_NoRegister(); \
public: \
	DECLARE_CLASS2(UHealthComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/MarketplacePlugins"), Z_Construct_UClass_UHealthComponent_NoRegister) \
	DECLARE_SERIALIZER(UHealthComponent)


#define FID_MarketplacePlugins_Source_MarketplacePlugins_HealthComponent_h_16_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UHealthComponent(UHealthComponent&&) = delete; \
	UHealthComponent(const UHealthComponent&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UHealthComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UHealthComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UHealthComponent) \
	NO_API virtual ~UHealthComponent();


#define FID_MarketplacePlugins_Source_MarketplacePlugins_HealthComponent_h_13_PROLOG
#define FID_MarketplacePlugins_Source_MarketplacePlugins_HealthComponent_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_MarketplacePlugins_Source_MarketplacePlugins_HealthComponent_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_MarketplacePlugins_Source_MarketplacePlugins_HealthComponent_h_16_INCLASS_NO_PURE_DECLS \
	FID_MarketplacePlugins_Source_MarketplacePlugins_HealthComponent_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UHealthComponent;

// ********** End Class UHealthComponent ***********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_MarketplacePlugins_Source_MarketplacePlugins_HealthComponent_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
