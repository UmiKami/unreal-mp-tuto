// Fill out your copyright notice in the Description page of Project Settings.


#include "MP_LanMenu.h"

#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"

void UMP_LanMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	FInputModeUIOnly InputMode;

	APlayerController* PC = GetOwningPlayer();
	
	PC->SetInputMode(InputMode);
	PC->SetShowMouseCursor(true);
	
	Button_Host->OnClicked.AddDynamic(this, &ThisClass::HostButtonClicked);
	Button_Join->OnClicked.AddDynamic(this, &ThisClass::JoinButtonClicked);
}

void UMP_LanMenu::DisableUIOnlyInputMode() const
{
	FInputModeGameOnly InputMode;
	
	APlayerController* PC = GetOwningPlayer();
	
	PC->SetInputMode(InputMode);
	PC->SetShowMouseCursor(false);
}

void UMP_LanMenu::HostButtonClicked()
{
	DisableUIOnlyInputMode();
	
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, HostingLevel, true, "listen");
}

void UMP_LanMenu::JoinButtonClicked()
{
	DisableUIOnlyInputMode();
	
	const FString Address = TextBox_IpAddress->GetText().ToString();
	
	UGameplayStatics::OpenLevel(this, *Address);
}
