// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "StatementDatabase.h"
#include "Statement.h"
#include "Agent.h"
#include "Location.h"

DEFINE_LOG_CATEGORY(DatabaseLog);

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
	ParseWorldFile();
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
		if (GEngine)
		{
			WriteToFile();
		}
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
		if (GEngine)
		{
			WriteToFile();
		}
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
		if (GEngine)
		{
			WriteToFile();
		}

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
		if (GEngine)
		{
			WriteToFile();
		}
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

UStatement* UStatementDatabase::FindStatement(const FString& Key)
{
	if (Key == "")
	{
		UE_LOG(DatabaseLog, Error, TEXT("Cannot find statement with a null key."));
		return NULL;
	}

	if (Statements.Contains(Key))
	{
		return Statements.FindChecked(Key);
	}
	else
	{
		return NULL;
	}
}

bool UStatementDatabase::ParseWorldFile()
{
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*WORLD_DATABASE_PATH))
	{
		UE_LOG(DatabaseLog, Error, TEXT("World Statements File does not exist."));
		return false;
	}

	TArray<FString> Lines;

	if (!FFileHelper::LoadANSITextFileToStrings(*WORLD_DATABASE_PATH, NULL, Lines))
	{
		UE_LOG(DatabaseLog, Warning, TEXT("Could not load strings from file."));
		return false;
	}

	for (int32 index = 0; index < Lines.Num(); index++)
	{
		int32 indx;
		if (Lines[index].FindChar('!', indx) || Lines[index].FindChar('.', indx))
		{
			UStatement* NewStatement = UStatement::NewStatement(Lines[index]);
			
			InsertIntoDatabase(NewStatement);
		}
	}

	return true;
}

bool UStatementDatabase::ParseAgentsFile()
{
	if (!Statements.Contains("instantiate.agent."))
	{
		UE_LOG(DatabaseLog, Warning, TEXT("There is no agent in the database to be initialized. Check WorldStatements file."));
		return false;
	}

	TArray<UStatement*> Agents;
	Statements.MultiFind("instantiate.agent.", Agents, true);

	for (int32 index = 0; index < Agents.Num(); index++)
	{
		FString path = (AGENTS_DATABASE_PATH + "/" + (Agents[index])->LastVertex() + ".txt");
		if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*path))
		{
			UE_LOG(DatabaseLog, Warning, TEXT("Can not find the %s file."), *path);
			return false;
		}
		else
		{
			TArray<FString> Lines;

			if (!FFileHelper::LoadANSITextFileToStrings(*path, NULL, Lines))
			{
				UE_LOG(DatabaseLog, Warning, TEXT("Could not load strings from file."));
				return false;
			}

			for (int32 LineIndex = 0; LineIndex < Lines.Num(); LineIndex++)
			{
				if (Lines[LineIndex] != "")
				{
					UStatement* NewStatement =UStatement::NewStatement(Agents[index]->BranchFrom(1, false) + "." + Lines[LineIndex]);
	
					InsertIntoDatabase(NewStatement);
				}
			}

		}
	}

	Statements.Remove("instantiate.agent.");

	return true;
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

void UStatementDatabase::WriteToFile()
{
	TArray <FString> Lines;

	for (auto StatesItr = Statements.CreateConstIterator(); StatesItr; ++StatesItr)
	{
		Lines.Add(*StatesItr->Value->GetStatement());
	}

	if (Lines.Num() == 0)
	{
		return;
	}

	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*DATABASE_PATH))
	{
		FPlatformFileManager::Get().GetPlatformFile().DeleteFile(*DATABASE_PATH);
	}

	FString ToSave;

	for (int32 index = 0; index < Lines.Num(); index++)
	{
		ToSave += Lines[index];
		ToSave += "\r\n";
	}

	ToSave += "END";

	FFileHelper::SaveStringToFile(ToSave, *DATABASE_PATH);

}
