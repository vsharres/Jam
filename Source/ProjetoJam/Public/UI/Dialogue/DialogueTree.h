// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "DialogueTree.generated.h"

USTRUCT(BlueprintType)
struct FDialogueTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Table")
		FString DialoguePath;


	FDialogueTable()
	{}

};


/**
 * 
 */
UCLASS(BlueprintType)
class PROJETOJAM_API UDialogueTree : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogueTree")
		class UDialogueNode* Head;

	UDialogueTree();

	UFUNCTION(BlueprintCallable, Category = "DialogueTree")
		void BuildDialogueTree(const FString& Path);

	
	void GenerateNode(UDialogueNode* parentDialogueNode, const class FXmlNode* ParentNode);

	
};
