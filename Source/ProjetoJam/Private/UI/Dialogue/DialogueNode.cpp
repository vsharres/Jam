// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "DialogueNode.h"

UDialogueNode::UDialogueNode()
{
	bIsAReturnNode = false;
	bIsAExitNode = false;

}

UDialogueNode* UDialogueNode::BuildNode(UObject* WorldContextObject, const FString& dialogue, const FString& option, UDialogueNode* parentNode)
{
	if (WorldContextObject)
	{
		UDialogueNode* newNode = NewObject<UDialogueNode>(WorldContextObject);
		check(newNode);

		newNode->SetDialogueText(FText::FromString(dialogue));
		newNode->SetOptionText(FText::FromString(option));

		if (option == "Back")
		{
			newNode->bIsAReturnNode = true;
		}
		else if (option == "Exit")
		{
			newNode->bIsAExitNode = true;
		}

		if (parentNode)
		{
			parentNode->GetChildNodes().Add(newNode);
		}

		return newNode;

	}

	return NULL;
}

FText UDialogueNode::GetDialogueText()
{
	return DialogueText;
}

TArray<UDialogueNode*> UDialogueNode::GetChildNodes()
{
	return Childs;
}

UDialogueNode* UDialogueNode::GetChildAt(int32 index)
{
	if (Childs.Num() - 1 <= index)
	{
		return NULL;
	}

	return Childs[index];
}

TArray<FText> UDialogueNode::GetDialogueOptions()
{
	TArray<FText> ToReturn;

	for (const auto child : Childs)
	{
		if (child)
		{
			ToReturn.Add(child->DialogueText);
		}
	}

	return ToReturn;
}

void UDialogueNode::SetDialogueText(FText dialogue)
{
	DialogueText = dialogue;
}

void UDialogueNode::SetOptionText(FText option)
{
	OptionText = option;
}
