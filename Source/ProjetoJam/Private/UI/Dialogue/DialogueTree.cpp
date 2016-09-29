// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "DialogueTree.h"
#include "DialogueNode.h"
#include "XmlParser.h"

UDialogueTree::UDialogueTree()
{

}

void UDialogueTree::BuildDialogueTree(const FString& Path)
{
	const FString pathName = FPaths::GameContentDir() + TEXT("DialogueTable/") + Path;

	const FXmlFile file(pathName);

	const FXmlNode* RootNode = file.GetRootNode();
	check(RootNode);

	Head = UDialogueNode::BuildNode(this, RootNode->GetContent(), TEXT(""), NULL);
	check(Head);
	GenerateNode(Head, RootNode);

}

void UDialogueTree::GenerateNode(UDialogueNode* parentDialogueNode, const FXmlNode* parentNode)
{

	for(const auto& child : parentNode->GetChildrenNodes())
	{
		UDialogueNode* nextNode = UDialogueNode::BuildNode(this, child->GetContent(), child->GetAttribute(TEXT("text")), parentDialogueNode);
		check(nextNode);

		GenerateNode(nextNode, child);
		
	}

}

