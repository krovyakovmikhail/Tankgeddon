// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
//#include "CurrentObjectives.h"
#include "QuestListComponent.generated.h"


class UCurrentObjectives;
class AQuests;




UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class QUESTSYSTEM_API UQuestListComponent : public UActorComponent
{
	GENERATED_BODY()

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnQuestAction, AQuests *);
	
public:
	// Sets default values for this component's properties
	UQuestListComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray <AQuests*> AcceptedQuests;
	
	UPROPERTY()
	AQuests* ActiveQuest;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCurrentObjectives> CurrentObjectivesWidget;

	public:
	FOnQuestAction OnActiveQuestChanged;
	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddQuest(AQuests* Quest);
	
	const TArray<AQuests*>& GetQuests();

	AQuests* GetActiveQuest() const;
	
	void SetActiveQuest(AQuests* Quest);

	
};

