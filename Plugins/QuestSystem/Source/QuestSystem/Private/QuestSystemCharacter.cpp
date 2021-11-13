// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestSystemCharacter.h"

#include "QuestDialog.h"
#include "QuestList.h"
#include "QuestListComponent.h"
#include "Quests.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AQuestSystemCharacter::AQuestSystemCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AQuestSystemCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AQuestSystemCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AQuestSystemCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AQuestSystemCharacter::Interact_Implementation(AActor* ActorInteractedWithObject)
{
	if (ActorInteractedWithObject == nullptr)
	{
		return;
	}
	
	UQuestListComponent * QuestList = Cast<UQuestListComponent>(ActorInteractedWithObject->GetComponentByClass(UQuestListComponent::StaticClass()));

	if (QuestList == nullptr)
	{
		return;
	}

	
	TArray<AActor *> AttachedActors;
	
	 GetAttachedActors(AttachedActors);

	

	for (auto & Actor : AttachedActors)
	{
		AQuests * Quest = Cast<AQuests>(Actor);
		if (Quest == nullptr) continue;

		if (Quest->bIsTaken || (Quest->PreviousQuest && !Quest->PreviousQuest->IsComplited()))
		{
			continue;
		}

		if (QuestDialogClass)
		{
			UQuestDialog  * QuestDialog = CreateWidget<UQuestDialog>(GetWorld(), QuestDialogClass);
			QuestDialog->Init(Quest);
			QuestDialog->OnQuestAccepted.BindUObject(QuestList, &UQuestListComponent::AddQuest, Quest);
			QuestDialog->OnQuestQuited.BindLambda([this, ActorInteractedWithObject]()
			{
				NotifyInteractionFinished(this, ActorInteractedWithObject);
			});
			QuestDialog->AddToViewport();
			return;
		}
	}
	NotifyInteractionFinished(this, ActorInteractedWithObject);
}

void AQuestSystemCharacter::ToggleQuestListVisibility()
{
	
		APlayerController * PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		
		if (PC==nullptr)
		{
			return;
		}

		if (QuestLists)
		{
			QuestLists->RemoveFromParent();
			QuestLists = nullptr;
			UWidgetBlueprintLibrary::SetInputMode_GameOnly(PC);
			PC->bShowMouseCursor = false;
		}
		else
		{
			if (QuestListClass)
			{
				UQuestListComponent * QuestListComp = nullptr;
				
				QuestLists = CreateWidget<UQuestList>(GetWorld(), QuestListClass);
				QuestLists->Init(QuestListComp);
				QuestLists->AddToViewport();
				UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PC);
				PC->bShowMouseCursor = true;
			}
		}
	
}

TArray<AQuests*>  AQuestSystemCharacter::AttachedQuests() const  // эта функция должна вернуть массив прикрепленных квестов к нашему инстансу квестЧарактер
{
	TArray<AQuests*> AttachedQuests; // это будет коллекция Прикрепленных квестов к NPC квестЧарактер
	TArray<AActor *> AttachedActors;
	
	GetAttachedActors(AttachedActors); //получаем прикрепленных акторов
	
	for (auto & Actor :AttachedActors) // Перебирем коррекцию 
	{
		AQuests * Quest = Cast<AQuests>(Actor); // Приведемся к AQuests

		if (Quest) //если есть Quest, тогда.. 
		{
			AttachedQuests.AddUnique(Quest);		 //..Добавляем в коллекцию прикрепленные квесты
		}
		

	
	}
	return  AttachedQuests; // вернем TArray указателей на  прикрепленные квесты.
}


