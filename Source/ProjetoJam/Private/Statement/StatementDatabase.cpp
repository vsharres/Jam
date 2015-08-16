// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoJam.h"
#include "Public/Statement/Statement.h"
#include "Public/Statement/StatementDatabase.h"
#include "Public/Agents/Agent.h"
#include "Public/Location/Location.h"

DEFINE_LOG_CATEGORY(DatabaseLog);


// Sets default values
AStatementDatabase::AStatementDatabase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WorldSatatementFilePath = FPaths::GameContentDir() + "Databases/World/WorldStatements.txt";
	AgentStatementFilePath = FPaths::GameContentDir() + "Databases/Agents";
	DatabaseFilePath = FPaths::GameContentDir() + "Databases/Database.txt";

}

void AStatementDatabase::InitializeDataBase()
{

	if (!ParseWorldFile())
	{
		UE_LOG(DatabaseLog, Error, TEXT("Could not parse world file."));
		return;
	}

	if (!ParseAgentsFile())
	{
		UE_LOG(DatabaseLog, Error, TEXT("Could not parse character file."));
		return;
	}

}

TArray<FString> AStatementDatabase::InspectDatabase()
{
	TArray<UStatement*> Temp;

	Statements.GenerateValueArray(Temp);

	TArray<FString> ToReturn;

	for (int32 index = 0; index < Temp.Num(); index++)
	{
		ToReturn.Add((Temp[index])->GetText());
	}

	return ToReturn;
}

void AStatementDatabase::InsertIntoDatabase(UStatement* NewStatement)
{
	if (!NewStatement)
	{
		UE_LOG(DatabaseLog, Error, TEXT("Can not add statement with null reference to database."));
		return;
	}

	if (Statements.Num() == 0)
	{
		Statements.Add(NewStatement->GetKeyName(), NewStatement);
		return;
	}

	FName IncompatibleKey = "";
	TArray<FName> LessSpecificKeys;

	if (HasStatement(NewStatement))
	{
		UE_LOG(DatabaseLog, Log, TEXT("The statement was not added, because the statement %s is already in the database."), *NewStatement->GetText());
		return;
	}
	else if (IsIncompatibleWithDatabase(NewStatement, IncompatibleKey))
	{

		Statements.Remove(IncompatibleKey);
		UE_LOG(DatabaseLog, Log, TEXT("Deleting statements with key %s, for they are incompatible."), *(IncompatibleKey.ToString()));

		Statements.Add(NewStatement->GetKeyName(), NewStatement);
		UE_LOG(DatabaseLog, Log, TEXT("Adding statement %s"), *NewStatement->GetText());
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
			UE_LOG(DatabaseLog, Log, TEXT("Deleting statements with key %s , for they are less specific then the new statement %s."), *(LessSpecificKeys[index].ToString()), *NewStatement->GetText());
		}
		Statements.Add(NewStatement->GetKeyName(), NewStatement);
		UE_LOG(DatabaseLog, Log, TEXT("Adding statement %s"), *NewStatement->GetText());
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
		UE_LOG(DatabaseLog, Log, TEXT("The statement was not added, because the statement %s is less specific than the database."), *NewStatement->GetText());
		return;
	}
	else
	{
		Statements.Add(NewStatement->GetKeyName(), NewStatement);
		UE_LOG(DatabaseLog, Log, TEXT("Adding statement %s"), *NewStatement->GetText());
		Statements.KeySort(ConstPredicate);
		DatabaseWasUpdated();
		if (GEngine)
		{
			WriteToFile();
		}
		return;
	}
}

void AStatementDatabase::InsertIntoDatabaseWithString(const FString& NewStatement)
{
	if (NewStatement == "")
	{
		UE_LOG(DatabaseLog, Error, TEXT("Can not add statement with null string to database."));
		return;
	}

	UStatement* StatementToInsert = NewObject<UStatement>();
	StatementToInsert->SetStatement(NewStatement);

	InsertIntoDatabase(StatementToInsert);
}

void AStatementDatabase::DeleteStatementFromDatabase(UStatement* StamentToDelete)
{
	if (!StamentToDelete)
	{
		UE_LOG(DatabaseLog, Error, TEXT("Can not delete statement with null reference."));
		return;
	}

	if (!Statements.FindRef(StamentToDelete->GetKeyName()))
	{
		UE_LOG(DatabaseLog, Warning, TEXT("Can not find the statement in the database."));
		return;
	}
	else
	{
		for (auto Itr = Statements.CreateKeyIterator(StamentToDelete->GetKeyName()); Itr; ++Itr)
		{
			if (Itr.Value()->GetText() == StamentToDelete->GetText())
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

bool AStatementDatabase::IsIncompatibleWithDatabase(UStatement* Statement, FName& IncompatibleKey)
{
	if (!Statement)
	{
		UE_LOG(DatabaseLog, Error, TEXT("Cannot compare null statement to the database."));
		return false;
	}

	FString TempDotKey = "";

	TempDotKey = Statement->GetKeyName().ToString().LeftChop(1);
	TempDotKey.AppendChar('.');

	if (Statements.Contains(FName(*TempDotKey)) && Statement->GetKeyName().ToString().Right(1) == "!")
	{
		IncompatibleKey = FName(*TempDotKey);
		return true;
	}

	FString TempExcKey = "";

	TempExcKey = Statement->GetKeyName().ToString().LeftChop(1);
	TempExcKey.AppendChar('!');

	if (Statements.Contains(FName(*TempExcKey)))
	{
		IncompatibleKey = FName(*TempExcKey);
		return true;
	}

	return false;
}

bool AStatementDatabase::IsMoreSpecificThanDatabase(UStatement* Statement, TArray<FName>& LessSpecificKeys)
{
	if (!Statement)
	{
		UE_LOG(DatabaseLog, Error, TEXT("Can't compare statement with null reference"));
		return false;
	}

	FString TempKey = "";

	for (int32 index = 0; index < Statement->GetEdges().Num(); index++)
	{
		TempKey += Statement->GetVertices()[index];
		TempKey += Statement->GetEdges()[index];

		if (Statements.Contains(FName(*TempKey)) && Statement->GetKeyName().ToString().Contains(TempKey) && Statements.FindRef(FName(*TempKey))->GetEdges().Num() < Statement->GetEdges().Num())
		{
			LessSpecificKeys.Add(FName(*TempKey));
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

bool AStatementDatabase::IsLessSpecifiThanDatabase(UStatement* Statement)
{
	if (!Statement)
	{
		UE_LOG(DatabaseLog, Error, TEXT("Can't compare statement with null reference"));
		return false;
	}

	TArray<FName> DatabaseKeys;
	Statements.GenerateKeyArray(DatabaseKeys);

	for (auto& Itr : DatabaseKeys)
	{
		if (Itr.ToString().Contains(Statement->GetKeyName().ToString()) && Itr.ToString().Len() > Statement->GetKeyName().ToString().Len())
		{
			return true;
		}
	}

	return false;
}

bool AStatementDatabase::IsKeyInDatabase(const FName& Key)
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

TArray<FName> AStatementDatabase::FindKeysWith(const FString& vertex)
{
	TArray<FName> ArrayToReturn;

	if (vertex == "")
	{
		UE_LOG(DatabaseLog, Warning, TEXT("Cannot find keys with a null vertex."));
		return ArrayToReturn;
	}

	TArray<FName> temp;
	Statements.GenerateKeyArray(temp);

	for (int32 index = 0; index < temp.Num(); index++)
	{
		FName otherStatement = FName(*vertex);

		if (temp[index].Compare(otherStatement) == 0)
		{
			ArrayToReturn.Push(temp[index]);
		}
	}

	return ArrayToReturn;

}

UStatement* AStatementDatabase::FindStatement(const FName& Key)
{
	if (Key == "")
	{
		UE_LOG(DatabaseLog, Error, TEXT("Cannot find statement with a null key."));
		return nullptr;
	}

	if (Statements.Contains(Key))
	{
		return Statements.FindChecked(Key);
	}
	else
	{
		return nullptr;
	}
}

bool AStatementDatabase::ParseWorldFile()
{
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*WorldSatatementFilePath))
	{
		UE_LOG(DatabaseLog, Error, TEXT("World Statements File does not exist."));
		return false;
	}

	TArray<FString> Lines;

	if (!FFileHelper::LoadANSITextFileToStrings(*WorldSatatementFilePath, NULL, Lines))
	{
		UE_LOG(DatabaseLog, Warning, TEXT("Could not load strings from file."));
		return false;
	}

	for (int32 index = 0; index < Lines.Num(); index++)
	{
		if (Lines[index] != "")
		{
			UStatement* NewStatement = NewObject<UStatement>();
			NewStatement->SetStatement(Lines[index]);
			InsertIntoDatabase(NewStatement);
		}
	}

	return true;
}

bool AStatementDatabase::ParseAgentsFile()
{
	if (!Statements.Contains("instantiate."))
	{
		UE_LOG(DatabaseLog, Warning, TEXT("There is no agent in the database to be initialized. Check WorldStatements file."));
		return false;
	}

	TArray<UStatement*> Agents;
	Statements.MultiFind("instantiate.", Agents, true);

	for (int32 index = 0; index < Agents.Num(); index++)
	{
		FString path = (AgentStatementFilePath + "/" + (Agents[index])->GetVertices()[1] + ".txt");
		if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*path))
		{
			UE_LOG(DatabaseLog, Warning, TEXT("Can not find the %s file."), *(Agents[index])->GetVertices()[1]);
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
					UStatement* NewStatement = NewObject<UStatement>();
					NewStatement->SetStatement(Lines[LineIndex]);
					InsertIntoDatabase(NewStatement);
				}
			}

		}
	}

	Statements.Remove("instantiate.");

	return true;
}

bool AStatementDatabase::HasStatement(UStatement* Statement)
{
	if (!Statement)
	{
		UE_LOG(DatabaseLog, Error, TEXT("Can't compare statement with null reference"));
		return false;
	}

	if (Statements.Contains(Statement->GetKeyName()))
	{
		if (Statements.FindChecked(Statement->GetKeyName())->GetText() == Statement->GetText())
		{
			return true;
		}
	}

	return false;

}

bool AStatementDatabase::IsStatementTextInDatabase(const FString& StatementText)
{
	UStatement* temp = NewObject<UStatement>(this);
	temp->SetStatement(StatementText);

	if (Statements.Find(temp->GetKeyName()))
	{
		return true;
	}
	else
	{
		return false;
	}

}

void AStatementDatabase::WriteToFile()
{
	TArray <FString> Lines;

	for (auto StatesItr = Statements.CreateConstIterator(); StatesItr; ++StatesItr)
	{
		Lines.Add(*StatesItr->Value->GetText());
	}

	if (Lines.Num() == 0)
	{
		return;
	}

	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*DatabaseFilePath))
	{
		FPlatformFileManager::Get().GetPlatformFile().DeleteFile(*DatabaseFilePath);
	}

	FString ToSave;

	for (int32 index = 0; index < Lines.Num(); index++)
	{
		ToSave += Lines[index];
		ToSave += "\r\n";
	}

	ToSave += "END";

	FFileHelper::SaveStringToFile(ToSave, *DatabaseFilePath);

}
