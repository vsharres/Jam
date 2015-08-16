// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "StatementDatabase.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(DatabaseLog, Log, All);

UCLASS()
class PROJETOJAM_API AStatementDatabase : public AActor
{
	GENERATED_BODY()

private:

	/**The Map containing all of the statements.
	*Statements that have the same signature, have the same key.
	*In the case of Practices, the key of the practice is the name of the acting agent.
	*/
	TMultiMap<FName, class UStatement*> Statements;

	/**The full path to the World Statements file. */
	UPROPERTY(EditDefaultsOnly, Category = Database)
		FString WorldSatatementFilePath;

	/**The full path to the Characters Statements file. */
	UPROPERTY(EditDefaultsOnly,Category = Database)
		FString AgentStatementFilePath;

	/**The full path to the database file. */
	UPROPERTY(EditDefaultsOnly, Category = Database)
		FString DatabaseFilePath;

public:	

	// Sets default values for this actor's properties
	AStatementDatabase();

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
		bool IsIncompatibleWithDatabase(UStatement* Statement, FName& IncompatibleKey);

	/**
	* Called to check if a given statement is more specific(contains more information) than any statement in the database.
	* @param Statement - The statement to be compared with the database.
	* @param LessSpecificKeys - The array with all of the keys of the statements that are less specific.
	* @return boolean value of true if the statement is more specific than one of the statements in the database.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Is More Specific", Keywords = "More Specific"), Category = Database)
		bool IsMoreSpecificThanDatabase(UStatement* Statement, TArray<FName>& LessSpecificKeys);

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
		bool IsKeyInDatabase(const FName& StatementKey);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Find Keys", Keywords = "Find Keys"), Category = Database)
		TArray<FName> FindKeysWith(const FString& vertex);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Find Statement", Keywords = "Find Statement"), Category = Database)
		UStatement* FindStatement(const FName& Key);

	/**
	* Called to parse the world file.
	* This function already inserts the statements to the database
	* @return boolean value of true if the file was successful parsed.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Parse World File", Keywords = "Parse World File"), Category = Database)
		bool ParseWorldFile();

	/**
	* Called to parse the agents file.
	* This function already inserts the statements to the database
	* @return boolean value of true if the file was successful parsed.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Parse Character File", Keywords = "Parse Character File"), Category = Database)
		bool ParseAgentsFile();

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
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Database was updated", Keywords = "Database Updated"), Category = Database)
		virtual void DatabaseWasUpdated();

	/**
	* Called to write the content of the database to an external file.
	* File is located in the Content/Databases folder with the name Database.txt
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Write To File", Keywords = "Write File"), Category = Database)
		void WriteToFile();

	/**
	* The predicate function to sort the database.
	*/
	FORCEINLINE static bool ConstPredicate(const FName& key1, const FName& key2)
	{
		return (key1 < key2);
	}
	
};
