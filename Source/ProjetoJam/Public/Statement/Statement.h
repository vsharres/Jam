// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Statement.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(StatementLog, Log, All);

/**
 * 
 */
UCLASS(Blueprintable)
class PROJETOJAM_API UStatement : public UObject
{
	GENERATED_BODY()
	
private:

	UPROPERTY(VisibleAnywhere, Category = Statement)
		FString Statement;

	UPROPERTY()
		FString StatementKey;

	UPROPERTY()
		TArray<FString> Vertices;

	UPROPERTY()
		TArray<FString> Edges;

public:

	UStatement(const FObjectInitializer& ObjectInitializer);


	UFUNCTION(BlueprintCallable, Category = Statement)
		static UStatement* NewStatement(const FString& newStatementString);

	UFUNCTION(BlueprintCallable, Category = Statement)
		void GenerateKey();

	UFUNCTION(BlueprintPure, Category = Statement)
		FString GetStatement();

	UFUNCTION(BlueprintPure, Category = Statement)
		FString GetStatementKey();

	UFUNCTION(BlueprintPure, Category = Statement)
		static FString GetKeyFromString(const FString& StatementString);

	UFUNCTION(BlueprintPure, Category = Statement)
		TArray<FString> GetVertices();

	UFUNCTION(BlueprintPure, Category = Statement)
	TArray<FString> GetEdges();

	UFUNCTION(BlueprintPure, Category = Statement)
	FString LastVertex();

	UFUNCTION(BlueprintPure, Category = Statement)
	FString BranchFrom(const int32& index, bool direct = true);

	UFUNCTION(BlueprintPure, Category = Statement)
		bool HasSameSignature(const FString& Vertex, UStatement* OtherStatement);

	UFUNCTION(BlueprintPure, Category = Statement)
		bool IsEdgeEqual(int32 EdgeIndex, UStatement* OtherStatement);

	UFUNCTION(BlueprintPure, Category = Statement)
		bool IsIncompatibleWith(UStatement* OtherStatement);

	UFUNCTION(BlueprintPure, Category = Statement)
		bool IsStatementValid();

#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif


	FORCEINLINE FString& operator[](int32 index)
	{
		return Vertices[index];
	}

	/*FORCEINLINE UStatement& operator>>(UStatement& StatementQuery)
	{
		FString asString = StatementQuery.GetStatement();

		TArray<int32> indexQuery;
		TArray<TCHAR> CharArray = asString.GetCharArray();

		for (int32 index = 0; index < CharArray.Num(); index++)
		{
			if (FChar::IsLower(CharArray[index]))
			{
				indexQuery.Add(index);
			}

		}

		if (indexQuery.Num() > 0)
		{
			for (int32 index = 0; index < indexQuery.Num(); index++)
			{
				if (this->Vertices.Num() >= index + 1)
				{
					asString.ReplaceInline(&CharArray[indexQuery[index]], *(this->Vertices[index]), ESearchCase::CaseSensitive);
				}
			}

		}

		*this = asString;

		return *this;
	}*/

	


	
	
};
