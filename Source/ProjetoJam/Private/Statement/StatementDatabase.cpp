// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "StatementDatabase.h"
#include "Practice.h"
#include "Agent.h"

// Sets default values
UStatementDatabase::UStatementDatabase()
{
}

UStatementDatabase::~UStatementDatabase()
{
	Statements.Empty();
}

void UStatementDatabase::InitializeDataBase()
{
	//AddFileStatements(WORLD_DATABASE_PATH);

	/*TArray<UStatement*> Statements;
	const FString key = "agents.";

	if (FindStatements(key, Statements))
	{
		for (UStatement* Statement : Statements)
		{
			FString StatementsPath(FPaths::GameContentDir() + "Databases/Agents/" + Statement->LastVertex() + ".txt");

			AddFileStatements(StatementsPath);
		}
	}*/

}

TArray<FString> UStatementDatabase::InspectDatabase()
{
	TArray<UStatement*> Temp;

	Statements.GenerateValueArray(Temp);

	TArray<FString> ToReturn;

	for (int32 index = 0; index < Temp.Num(); index++)
	{
		ToReturn.Add((Temp[index])->GetStatement());
	}

	return ToReturn;
}

void UStatementDatabase::InsertIntoDatabase(UStatement* NewStatement)
{
	if (Statements.Num() == 0)
	{
		Statements.Add(NewStatement->GetStatementKey(), NewStatement);
		return;
	}

	FString IncompatibleKey = "";
	TArray<FString> LessSpecificKeys;

	if (HasStatement(NewStatement))
	{
		UE_LOG(DatabaseLog, Log, TEXT("The statement was not added, because the statement %s is already in the database."), *NewStatement->GetStatement());
		return;
	}
	else if (IsIncompatibleWithDatabase(NewStatement, IncompatibleKey))
	{

		Statements.Remove(IncompatibleKey);
		UE_LOG(DatabaseLog, Log, TEXT("Deleting statements with key %s, for they are incompatible."), *IncompatibleKey);

		Statements.Add(NewStatement->GetStatementKey(), NewStatement);
		UE_LOG(DatabaseLog, Log, TEXT("Adding statement %s"), *NewStatement->GetStatement());
		Statements.KeySort(ConstPredicate);

		DatabaseWasUpdated();

		return;

	}
	else if (IsMoreSpecificThanDatabase(NewStatement, LessSpecificKeys))
	{
		for (int32 index = 0; index < LessSpecificKeys.Num(); index++)
		{
			Statements.Remove(LessSpecificKeys[index]);
			UE_LOG(DatabaseLog, Log, TEXT("Deleting statements with key %s , for they are less specific then the new statement %s."), *LessSpecificKeys[index], *NewStatement->GetStatement());
		}
		Statements.Add(NewStatement->GetStatementKey(), NewStatement);
		UE_LOG(DatabaseLog, Log, TEXT("Adding statement %s"), *NewStatement->GetStatement());
		Statements.KeySort(ConstPredicate);

		DatabaseWasUpdated();

		return;
	}
	else if (IsLessSpecifiThanDatabase(NewStatement))
	{
		UE_LOG(DatabaseLog, Log, TEXT("The statement was not added, because the statement %s is less specific than the database."), *NewStatement->GetStatement());
		return;
	}
	else
	{
		Statements.Add(NewStatement->GetStatementKey(), NewStatement);
		UE_LOG(DatabaseLog, Log, TEXT("Adding statement %s"), *NewStatement->GetStatement());
		Statements.KeySort(ConstPredicate);
		DatabaseWasUpdated();

		return;
	}
}

void UStatementDatabase::InsertIntoDatabaseWithString(const FString& NewStatement)
{
	if (NewStatement == "")
	{
		UE_LOG(DatabaseLog, Warning, TEXT("Can not add statement with null string to database."));
		return;
	}

	UStatement* StatementToInsert = UStatement::NewStatement(NewStatement);
	InsertIntoDatabase(StatementToInsert);
}

void UStatementDatabase::DeleteStatementFromDatabase(UStatement* StamentToDelete)
{

	if (Statements.FindRef(StamentToDelete->GetStatementKey())->GetStatement() == "")
	{
		UE_LOG(DatabaseLog, Warning, TEXT("Cannot find the statement in the database."));
		return;
	}
	else
	{
		for (auto Itr = Statements.CreateKeyIterator(StamentToDelete->GetStatementKey()); Itr; ++Itr)
		{
			if (Itr.Value()->GetStatement() == StamentToDelete->GetStatement())
			{
				Itr.RemoveCurrent();
			}
		}

		Statements.KeySort(ConstPredicate);
		DatabaseWasUpdated();

	}

}

bool UStatementDatabase::IsIncompatibleWithDatabase(UStatement* Statement, FString& IncompatibleKey)
{
	FString TempDotKey = "";

	TempDotKey = Statement->GetStatementKey().LeftChop(1);
	TempDotKey.AppendChar('.');

	if (Statements.Contains(TempDotKey) && Statement->GetStatementKey().Right(1) == "!")
	{
		IncompatibleKey = TempDotKey;
		return true;
	}

	FString TempExcKey = "";

	TempExcKey = Statement->GetStatementKey().LeftChop(1);
	TempExcKey.AppendChar('!');

	if (Statements.Contains(TempExcKey))
	{
		IncompatibleKey = TempExcKey;
		return true;
	}

	return false;
}

bool UStatementDatabase::IsMoreSpecificThanDatabase(UStatement* Statement, TArray<FString>& LessSpecificKeys)
{
	FString TempKey = "";

	for (int32 index = 0; index < Statement->GetEdges().Num(); index++)
	{
		TempKey += Statement->GetVertices()[index];
		TempKey += Statement->GetEdges()[index];

		if (Statements.Contains(TempKey) && Statement->GetStatementKey().Contains(TempKey) && Statements.FindRef(TempKey)->GetEdges().Num() < Statement->GetEdges().Num())
		{
			LessSpecificKeys.Add(TempKey);
		}
	}

	if (LessSpecificKeys.Num() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool UStatementDatabase::IsLessSpecifiThanDatabase(UStatement* Statement)
{
	TArray<FString> DatabaseKeys;
	Statements.GenerateKeyArray(DatabaseKeys);

	for (auto& Itr : DatabaseKeys)
	{
		if (Itr.Contains(Statement->GetStatementKey()) && Itr.Len() > Statement->GetStatementKey().Len())
		{
			return true;
		}
	}

	return false;
}

bool UStatementDatabase::IsKeyInDatabase(const FString& Key)
{

	if (Statements.Find(Key))
	{
		return true;
	}
	else
	{
		return false;
	}

}

TArray<FString> UStatementDatabase::FindKeysWith(const FString& vertex)
{
	TArray<FString> ArrayToReturn;

	if (vertex == "")
	{
		UE_LOG(DatabaseLog, Warning, TEXT("Cannot find keys with a null vertex."));
		return ArrayToReturn;
	}

	TArray<FString> temp;
	Statements.GenerateKeyArray(temp);

	for (int32 index = 0; index < temp.Num(); index++)
	{
		FString otherStatement = vertex;

		if (temp[index].Compare(otherStatement) == 0)
		{
			ArrayToReturn.Push(temp[index]);
		}
	}

	return ArrayToReturn;

}

bool UStatementDatabase::FindStatements(const FString& Key, TArray<UStatement*>& OutStatements)
{
	if (Key == "")
	{
		UE_LOG(DatabaseLog, Error, TEXT("Cannot find statement with a null key."));
		return false;
	}

	if (Statements.Contains(Key))
	{
		Statements.MultiFind(Key, OutStatements);
		return true;
	}

	return false;
}

UStatement* UStatementDatabase::FindExludingStatement(const FString& Key)
{
	if (!Key.Contains("!"))
	{
		UE_LOG(DatabaseLog, Warning, TEXT("Can only find excluding statements."));
	}

	if (Statements.Contains(Key))
	{
		return Statements.FindRef(Key);
	}

	return nullptr;
}

bool UStatementDatabase::HasStatement(UStatement* Statement)
{

	if (Statements.Contains(Statement->GetStatementKey()))
	{
		if (Statements.FindChecked(Statement->GetStatementKey())->GetStatement() == Statement->GetStatement())
		{
			return true;
		}
	}

	return false;

}

bool UStatementDatabase::IsStatementTextInDatabase(const FString& StatementText)
{

	if (Statements.Find(UStatement::GetKeyFromString(StatementText)))
	{
		return true;
	}
	else
	{
		return false;
	}

}

void UStatementDatabase::DatabaseWasUpdated()
{
	OnDatabaseUpdated.Broadcast();
}

bool UStatementDatabase::AddFileStatements(const FString& Path)
{
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*Path))
	{
		UE_LOG(DatabaseLog, Warning, TEXT("Can not find the %s file."), *Path);
		return false;
	}

	TArray<FString> Lines;

	if (!FFileHelper::LoadANSITextFileToStrings(*Path, NULL, Lines))
	{
		UE_LOG(DatabaseLog, Warning, TEXT("Could not load strings from file."));
		return false;
	}

	for (int32 index = 0; index < Lines.Num(); index++)
	{
		int32 indx;
		if (Lines[index].Contains("practice"))
		{

			int32 praticeNameStartIndex;

			Lines[index].FindLastChar('.', praticeNameStartIndex);
			FString practiceName = Lines[index].RightChop(praticeNameStartIndex + 1);
			//temp.FindChar('.', praticeNameEndIndex);

			//FString practiceName = temp.Left(praticeNameEndIndex);

			UDataTable* PracticeDataTable = LoadObject<UDataTable>(NULL, TEXT("/Game/Databases/Practices/PracticesTable.PracticesTable"), NULL, LOAD_None, NULL);
			if (PracticeDataTable)
			{
				static const FString ContextString(TEXT("GENERAL"));

				FPracticeTable* practiceTable = PracticeDataTable->FindRow<FPracticeTable>(FName(*practiceName), ContextString);

				if (practiceTable)
				{
					UPractice* newPractice = UPractice::NewPractice(GetTransientPackage(), Lines[index], practiceTable->PracticeBlueprintAsset);
					InsertIntoDatabase(newPractice);
				}
			}


		}
		else if (Lines[index].FindChar('!', indx) || Lines[index].FindChar('.', indx))
		{
			UStatement* newStatement = UStatement::NewStatement(Lines[index]);

			InsertIntoDatabase(newStatement);
		}
	}

	return true;
}
