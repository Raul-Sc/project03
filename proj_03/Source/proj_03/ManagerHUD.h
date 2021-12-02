// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Components/Widget.h"
#include "ManagerHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROJ_03_API AManagerHUD : public AHUD
{
	GENERATED_BODY()
		virtual void BeginPlay() override;
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> StartingWidgetClass;
	UPROPERTY()
		UUserWidget* CurrentWidget;

	UWidgetTree* hud;
	TArray<FName > elements;

public:
	void turnWidgetOn(const FName& Name);
	void turnWidgetOff(const FName& Name);
	void removeWidget(const FName& Name);

	void bpSetDirection();
	void bpSetWaypoint();
};
