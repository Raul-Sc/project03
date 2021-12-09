// Fill out your copyright notice in the Description page of Project Settings.


#include "BPReadWrite.h"
#include <Runtime\Core\Public\Misc\Paths.h>
#include <Runtime\Core\Public\HAL\PlatformFilemanager.h>

FString UBPReadWrite::LoadFileToString(FString Filename)
{
	FString directory = FPaths::GameSourceDir();
	FString result;

	IPlatformFile& file = FPlatformFileManager::Get().GetPlatformFile();

	if (file.CreateDirectory(*directory)) {
		FString myFile = directory + "/" + Filename;
		FFileHelper::LoadFileToString(result, *myFile);
	}
	return result;
}

TArray<FString> UBPReadWrite::LoadFileToStringArray(FString Filename)
{
	FString directory = FPaths::GameSourceDir();
	TArray<FString> result;

	IPlatformFile& file = FPlatformFileManager::Get().GetPlatformFile();

	if (file.CreateDirectory(*directory)) {
		FString myFile = directory + "/" + Filename;
		FFileHelper::LoadFileToStringArray(result, *myFile);
	}
	return result;

}
