// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMarketplacePlugins_init() {}
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");	MARKETPLACEPLUGINS_API UFunction* Z_Construct_UDelegateFunction_MarketplacePlugins_OnAttributeChangedSignature__DelegateSignature();
	MARKETPLACEPLUGINS_API UFunction* Z_Construct_UDelegateFunction_MarketplacePlugins_OnDeathSignature__DelegateSignature();
	MARKETPLACEPLUGINS_API UFunction* Z_Construct_UDelegateFunction_MarketplacePlugins_OnStaminaChangedSignature__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_MarketplacePlugins;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_MarketplacePlugins()
	{
		if (!Z_Registration_Info_UPackage__Script_MarketplacePlugins.OuterSingleton)
		{
		static UObject* (*const SingletonFuncArray[])() = {
			(UObject* (*)())Z_Construct_UDelegateFunction_MarketplacePlugins_OnAttributeChangedSignature__DelegateSignature,
			(UObject* (*)())Z_Construct_UDelegateFunction_MarketplacePlugins_OnDeathSignature__DelegateSignature,
			(UObject* (*)())Z_Construct_UDelegateFunction_MarketplacePlugins_OnStaminaChangedSignature__DelegateSignature,
		};
		static const UECodeGen_Private::FPackageParams PackageParams = {
			"/Script/MarketplacePlugins",
			SingletonFuncArray,
			UE_ARRAY_COUNT(SingletonFuncArray),
			PKG_CompiledIn | 0x00000000,
			0x69E4D4CF,
			0x27AE9543,
			METADATA_PARAMS(0, nullptr)
		};
		UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_MarketplacePlugins.OuterSingleton, PackageParams);
	}
	return Z_Registration_Info_UPackage__Script_MarketplacePlugins.OuterSingleton;
}
static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_MarketplacePlugins(Z_Construct_UPackage__Script_MarketplacePlugins, TEXT("/Script/MarketplacePlugins"), Z_Registration_Info_UPackage__Script_MarketplacePlugins, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x69E4D4CF, 0x27AE9543));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
