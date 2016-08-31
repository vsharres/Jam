// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "StatementDatabase.generated.h"

#define DATABASE_PATH (FString)(FPaths::GameContentDir() + "Databases/Database.txt")
#define WORLD_DATABASE_PATH (FString)(FPaths::GameContentDir() + "Databases/World/WorldStatements.txt")
#define AGENTS_DATABASE_PATH (FString)(FPaths::GameContentDir() + "Databases/Agents")

class UStatement;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDatabaseUpdated);

UCLASS()
class PROJETOJAM_API UStatementDatabase : public UObject
{
	GENERATED_BODY()

private:

	/**The Map containing all of the statements.
	*Statements that have the same signature, have the same key.
	*/
	TMultiMap<FString, UStatement*> Statements;

	//UPROPERTY(EditDefaultsOnly, Category = Practices)
	//	TArray<FPractice> PracticeList;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Database")
		FOnDatabaseUpdated OnDatabaseUpdated;

	// Sets default values for this actor's properties
	UStatementDatabase();

	~UStatementDatabase();

	/**
	* Called to Initialize the database, reading all of the necessary files to initialize.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Initialize Database", Keywords = "Inititialize Database"), Category = Database)
		void InitializeDataBase();

	/**
	* Called to Inspect the database.
	* @return an Array of string with the text of the statements.
	*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Inspect Database", Keywords = "Inspect Database"), Category = Database)
		TArray<FString> InspectDatabase();

	/**
	* Called to insert into the database a new statement, checking if the new statement is compatible with the other statements in the database.
	* This function deletes the incompatible statements.
	* @param NewStatement - The new statement to be added to the database.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Insert Into Database", Keywords = "Insert Databasa"), Category = Database)
		void InsertIntoDatabase(UStatement* NewStatement);

	/**
	* Called to insert into the database a new statement, checking if the new statement is compatible with the other statements in the database.
	* This function deletes the incompatible statements depending on the value of the bAllowOverriding argument.
	* @param NewStatement - The string statement to be added to the database.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Insert String Into Database", Keywords = "Insert Databasa String"), Category = Database)
		void InsertIntoDatabaseWithString(const FString& NewStatement);

	/**
	* Called to delete a given statement from the database.
	* @param StamentToDelete - The pointer to the statement to be deleted from the database.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Delete From Database", Keywords = "Delete From Database"), Category = Database)
		void DeleteStatementFromDatabase(UStatement* StamentToDelete);

	/**
	* Called to check if a statement is incompatible with the database.
	* This function returns in the argument the key of the incompatible statements in the database
	* @param Statement - The statement to compare with the database.
	* @param IncompatibleKey - The key of the incompatible statements.
	* @return boolean value of true if the file was successful parsed.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "IsIncompatibleWith Database", Keywords = "IsIncompatible Database"), Category = Database)
		bool IsIncompatibleWithDatabase(UStatement* Statement, FString& IncompatibleKey);

	/**
	* Called to check if a given statement is more specific(contains more information) than any statement in the database.
	* @param Statement - The statement to be compared with the database.
	* @param LessSpecificKeys - The array with all of the keys of the statements that are less specific.
	* @return boolean value of true if the statement is more specific than one of the statements in the database.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Is More Specific", Keywords = "More Specific"), Category = Database)
		bool IsMoreSpecificThanDatabase(UStatement* Statement, TArray<FString>& LessSpecificKeys);

	/**
	* Called to check if a given statement is less specific(contains less information) than any statement in the database.
	* @param Statement - The statement to be compared with the database.
	* @return boolean value of true if the statement is less specific than one of the statements in the database.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Is Less Specific", Keywords = "Less Specific"), Category = Database)
		bool IsLessSpecifiThanDatabase(UStatement* Statement);

	/**
	* Called to check if a Key is in the database.
	* @param StatementKey - The FString statement to check.
	* @return boolean value of true if the Key is found.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Is Key in Database", Keywords = "Key in Database"), Category = Database)
		bool IsKeyInDatabase(const FString& StatementKey);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Find Keys", Keywords = "Find Keys"), Category = Database)
		TArray<FString> FindKeysWith(const FString& vertex);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Find Statement", Keywords = "Find Statement"), Category = Database)
		bool FindStatements(const FString& Key, TArray<UStatement*>& OutStatements);

	/**
	* Called to check if a statement is already in the database.
	* @param Statement - the statement to check.
	* @return boolean value of true if the statement is already in the database.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Is in Database", Keywords = "Is in Database"), Category = Database)
		bool HasStatement(UStatement* Statement);

	/**
	* Called to check if a statement(as a text) is in the database.
	* @param StatementText - The FString statement to check.
	* @return boolean value of true if the statement is found.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Is Statement in Database", Keywords = "Statement in Database"), Category = Database)
		bool IsStatementTextInDatabase(const FString& StatementText);

	/**
	* Interface called every time the database is updated.
	*This interface is used to print the values inside the database.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Database was updated", Keywords = "Database Updated"), Category = Database)
		void DatabaseWasUpdated();

	UFUNCTION(BlueprintCallable, Category = "Database")
		bool AddFileStatements(const FString& Path);

	/**
	* The predicate function to sort the database.
	*/
	FORCEINLINE static bool ConstPredicate(const FString& key1, const FString& key2)
	{
		return (key1 < key2);
	}

};
