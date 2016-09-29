// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "DialogueNode.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PROJETOJAM_API UDialogueNode : public UObject
{
	GENERATED_BODY()
	
private:
	
	UPROPERTY()
		FText DialogueText;

	UPROPERTY()
		FText OptionText;

	UPROPERTY()
		TArray<UDialogueNode*> Childs;

public:

	UPROPERTY()
		bool bIsAExitNode;

	UPROPERTY()
		bool bIsAReturnNode;

	UDialogueNode();

	UFUNCTION()
		static UDialogueNode* BuildNode(UObject* WorldContextObject, const FString& dialogue, const FString& option, UDialogueNode* parentNode);

	UFUNCTION()
		FText GetDialogueText();

	UFUNCTION()
		TArray<UDialogueNode*> GetChildNodes();

	UFUNCTION()
		UDialogueNode* GetChildAt(int32 index);

	UFUNCTION()
		TArray<FText> GetDialogueOptions();

	UFUNCTION()
		void SetDialogueText(FText dialogue);

	UFUNCTION()
		void SetOptionText(FText option);
		
	
	
};
