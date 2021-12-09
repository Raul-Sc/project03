// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include <Runtime\Core\Public\Misc\FileHelper.h>
#include "BPReadWrite.generated.h"

/**
 * 
 */
UCLASS()
class PROJ_03_API UBPReadWrite : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

		UFUNCTION(BlueprintCallable, Category = "File I/O")
			static FString LoadFileToString(FString Filename);

	UFUNCTION(BlueprintCallable, Category = "File I/O")
		static TArray<FString> LoadFileToStringArray(FString Filename);
	
};
