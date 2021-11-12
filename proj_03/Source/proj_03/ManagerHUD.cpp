// Fill out your copyright notice in the Description page of Project Settings.



#include "ManagerHUD.h"
#include "Blueprint/WidgetTree.h"
void AManagerHUD::BeginPlay() {

	Super::BeginPlay();
   
    elements.Add("Coordinates");
    elements.Add("Mission");
    elements.Add("Battery");
    if (StartingWidgetClass != nullptr)
    {
        CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), StartingWidgetClass);
        if (CurrentWidget != nullptr)
        {
            CurrentWidget->AddToViewport();
           
            hud = CurrentWidget->WidgetTree;
            
            for (int i = 0; i < elements.Num(); i++) {
               // turnWidgetOff(elements[i]);
            }

       
             //   GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Found")  ));
           
        }
    }
}
void AManagerHUD::turnWidgetOn(const FName& Name) {

    UWidget* temp = hud->FindWidget(Name);

    if (temp)
        temp->SetVisibility(ESlateVisibility::Visible);

}
void AManagerHUD::turnWidgetOff(const FName& Name) {

    UWidget* temp = hud->FindWidget(Name);

    if (temp)
        temp->SetVisibility(ESlateVisibility::Hidden);

}
void AManagerHUD::removeWidget(const FName& Name) {
    UWidget* temp = hud->FindWidget(Name);

    if (temp)
        hud->RemoveWidget(temp);
}