// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objective.h"
#include "GameFramework/Actor.h"
#include "Quests.generated.h"

class UObjective;
class AQuests;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnQuestStatusUpdated, AQuests* /*Objective*/);


UCLASS()
class QUESTSYSTEM_API AQuests : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQuests();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void OnObjectiveCompleted(UObjective * Objective);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void TakeQuest(AActor * Pawn);

	UFUNCTION(BlueprintCallable, CallInEditor)
	void UpdateLocation();
	
	UFUNCTION(BlueprintPure)
	const TArray <UObjective*> GetObjectives();
	

#if WITH_EDITOR
	UFUNCTION(BlueprintCallable, CallInEditor)
	void AddLocationObjective();
	
	UFUNCTION(BlueprintCallable, CallInEditor)
	void AddInteractObjective();
#endif
	
	public:
	FOnQuestStatusUpdated OnQuestStatusUpdated;

	
	UPROPERTY(EditAnywhere)
	FText Name;
	
	UPROPERTY(EditAnywhere)	
	FText Description;
	
	UPROPERTY(EditAnywhere)
	TArray <UObjective*> Objectives;
	
	UPROPERTY(EditAnywhere)
	bool bIsStoryQuest = true;
	
	UPROPERTY(EditAnywhere)
	bool bKeepObjectivesOrder = true;
	
	UPROPERTY(EditAnywhere)
	AQuests* PreviousQuest;
	
	UPROPERTY(VisibleAnywhere)
	bool bIsTaken;
	
	bool IsComplited() const;

	bool IsStoryQuest() const;
	

	
};
