// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "StatementDatabase.generated.h"

#define DATABASE_PATH (FString)(FPaths::GameContentDir() + "Databases/Database.txt")
#define WORLD_DATABASE_PATH (FString)(FPaths::GameContentDir() + "Databases/World/WorldStatements.txt")
#define FACTIONS_DATABASE_PATH (FString)(FPaths::GameContentDir() + "Databases/Factions")
#define AGENTS_DATABASE_PATH (FString)(FPaths::GameContentDir() + "Databases/Agents")


DECLARE_LOG_CATEGORY_EXTERN(StatementLog, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(DatabaseLog, Log, All);

USTRUCT(BlueprintType)
struct FStatement {

	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statement Struct")
		FString Statement;

	UPROPERTY(BlueprintReadOnly, Category = "Statement Struct")
		FString StatementKey;

	UPROPERTY()
		TArray<FString> Vertices;

	UPROPERTY()
		TArray<FString> Edges;

	FStatement()
	{
		Statement = "";
		StatementKey = "";
		Vertices.Empty();
		Edges.Empty();
	}

	FStatement(const FStatement& OtherStatement)
	{
		Statement = OtherStatement.Statement;
		StatementKey = OtherStatement.StatementKey;
		Vertices = OtherStatement.Vertices;
		Edges = OtherStatement.Edges;
	}

	FStatement(const FString& newStatement)
	{
		if (newStatement == "") //warning message that a statement cannot be initialized with an empty string.
		{
			UE_LOG(StatementLog, Warning, TEXT("Can not initialize a statement with a empty string."));
			return;
		}
		else if (!newStatement.Contains(".") && !newStatement.Contains("!")) //warning that a statement cannot have only the root vertex.
		{
			UE_LOG(StatementLog, Warning, TEXT("A statement can not have only the root vertex, it must have at least two vertices."));
			return;
		}

		this->Statement = newStatement; //set the text property to the string input.

		/*Temporary string for creating the vertices. */
		FString temp = "";

		/*for each character in the input string, add that character to the temporary string variable,
		then when finds one of the edge characters, add the resulting string to the vertices array,
		and that edge to the edges array.*/
		for (int32 index = 0; index < newStatement.Len(); index++)
		{
			if (newStatement[index] == '.') //for edges with the "." inclusion identifier.
			{
				Edges.Add(".");
				Vertices.Add(temp);
				temp = "";

			}
			else if (newStatement[index] == '!') //for edges with the "!" exclusion identifier
			{
				Edges.Add("!");
				Vertices.Add(temp);
				temp = "";
			}
			else
			{
				temp += newStatement[index];
			}
		}

		if (temp != "") //this last if is to add the last vertex in the statement, since there is no more edges to be found.
		{
			Vertices.Add(temp);
		}

		//Generate the key to the statement.
		this->GenerateKey();
	}

	~FStatement()
	{
		Statement = NULL;
		StatementKey = NULL;
		Vertices.Empty();
		Edges.Empty();
	}

	FString GetStatement() const { return Statement; }

	FString GetStatementKey() const { return StatementKey; }

	TArray<FString> GetVertices() const { return Vertices; }

	TArray<FString> GetEdges() const { return Edges; }

	FString LastVertex() const { return Vertices.Last(); }

	FString BranchFrom(const int32& index, bool direct = true) {

		if (index >= Vertices.Num())
		{
			UE_LOG(StatementLog, Error, TEXT("Index was out of bounds of the statement %s"), *this->Statement);
			return "";
		}
		else if (index == Vertices.Num() - 1)
		{
			return LastVertex();
		}

		FString ToReturn;

		if (direct)
		{
			for (int32 i = index; i < Vertices.Num() - 1; i++)
			{
				ToReturn += Vertices[i];
				ToReturn += Edges[i];
			}
		}
		else
		{
			for (int32 i = 0; i <= index; i++)
			{
				ToReturn += Vertices[i];
				ToReturn += Edges[i];
			}
		}

		ToReturn += LastVertex();

		return ToReturn;
	}

	void GenerateKey() {
		//First check if the statement already has all of its vertices.
		if (this->Vertices.Num() > 0)
		{
			FString temp = "";
			/*To generate the key, adds each vertices and the edges to the key,
			the only vertices that is ignored, is the last one, so that when comparing statements, statements that would conflict, can be found more easily.*/
			for (int i = 0; i < Edges.Num(); i++)
			{
				temp += Vertices[i];
				temp += Edges[i];
			}

			StatementKey = temp;
		}
		else //warning message
		{
			UE_LOG(StatementLog, Warning, TEXT("Can not generate a key with a statement with no vertices."));
		}
	}

	bool HasSameSignature(const FString& Vertex, const FStatement& OtherStatement) {
		//warning message if the vertex to check is an empty string, or the pointer to the statement to compare is an null pointer.
		if (Vertex == "")
		{
			UE_LOG(StatementLog, Warning, TEXT("Comparing can not be null strings."));
			return false;
		}

		/*Comparing each vertex in the statement for the correspondent vertex in the other statement,
		and if they have any vertex that is different, so they have different signatures. */
		for (int32 index = 0; index < this->Vertices.IndexOfByKey(Vertex); index++)
		{
			if (this->Vertices[index] != OtherStatement.Vertices[index])
			{
				return false;
			}

		}

		return true;
	}

	bool IsEdgeEqual(int32 EdgeIndex, const FStatement& OtherStatement) {

		//for correcting the index to be found in the other statement, so that the signatures can be compared.
		if (EdgeIndex < this->Edges.Num())
		{
			EdgeIndex++;
		}

		//if the vertices of that edge has the same signatures then the vertices of the edge to be compared, then the edges are equal.
		if (HasSameSignature(this->Vertices[EdgeIndex - 1], OtherStatement) &&
			HasSameSignature(this->Vertices[EdgeIndex], OtherStatement))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool IsIncompatibleWith(const FStatement& OtherStatement) {
		/*if the last vertex of the statement is different from the vertex of the last statement,
		also has the same signature and if either of then has the last edge the exclusion identifier, then they are incompatible with each other.*/
		if (this->Vertices.Last() != OtherStatement.Vertices.Last() &&
			HasSameSignature(this->Vertices.Last(), OtherStatement) &&
			(this->Edges.Last() == "!" || OtherStatement.Edges.Last() == "!"))
		{
			return true;
		}

		return false;
	}

	bool IsStatementValid()
	{
		if (this->Statement == "" || this->StatementKey == "" || this->Vertices.Num() <= 1 || this->Edges.Num() == 0)
		{
			return false;
		}

		return true;
	}

	FString& operator[](int32 index)
	{
		return Vertices[index];
	}

	FStatement& operator>>(FStatement& StatementQuery)
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
	}

	const FString& operator[](const int32& index) const {
		return Vertices[index];
	}


};

USTRUCT(BlueprintType)
struct FPracticeState
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Practice State Struct")
		FStatement State;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Practice State Struct")
		TArray<class UAction*> Actions;


	FPracticeState()
	{
		State = FString();
		Actions.Empty();
	}

	~FPracticeState()
	{
		State = FString();
		Actions.Empty();
	}

};

USTRUCT()
struct FPractice :public FStatement
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Practice Struct")
		TArray<FPracticeState> States;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Practice Struct")
		FPracticeState CurrentState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Practice Struct")
		TArray<FStatement> ConstructionStatements;

	FPractice()
	{
		CurrentState = FPracticeState();
		States.Empty();
		ConstructionStatements.Empty();
	}

	FPractice(const FPractice& OtherPractice)
	{
		Statement = OtherPractice.Statement;
		StatementKey = OtherPractice.StatementKey;
		Vertices = OtherPractice.Vertices;
		Edges = OtherPractice.Edges;
		CurrentState = OtherPractice.CurrentState;
		States = OtherPractice.States;
		ConstructionStatements = OtherPractice.ConstructionStatements;
	}

	FPractice(const FStatement& OtherStatement)
	{
		Statement = OtherStatement.Statement;
		StatementKey = OtherStatement.StatementKey;
		Vertices = OtherStatement.Vertices;
		Edges = OtherStatement.Edges;
		CurrentState = FPracticeState();
		States.Empty();
		ConstructionStatements.Empty();
	}

	~FPractice()
	{
		States.Empty();
		ConstructionStatements.Empty();
	}

	//TO DO
	bool IsValidPractice() {
		return true;
	}
};

UCLASS()
class PROJETOJAM_API AStatementDatabase : public AActor
{
	GENERATED_BODY()

private:

	/**The Map containing all of the statements.
	*Statements that have the same signature, have the same key.
	*In the case of Practices, the key of the practice is the name of the acting agent.
	*/
	TMultiMap<FString, FStatement> Statements;

	UPROPERTY(EditDefaultsOnly, Category = Practices)
		TArray<FPractice> PracticeList;

public:

	// Sets default values for this actor's properties
	AStatementDatabase();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Database", Keywords = "Get Database", WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"), Category = Database)
		static AStatementDatabase* GetStatementDatabase(UObject* WorldContextObject);

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
		void InsertIntoDatabase(const FStatement& NewStatement);

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
		void DeleteStatementFromDatabase(const FStatement& StamentToDelete);

	/**
	* Called to check if a statement is incompatible with the database.
	* This function returns in the argument the key of the incompatible statements in the database
	* @param Statement - The statement to compare with the database.
	* @param IncompatibleKey - The key of the incompatible statements.
	* @return boolean value of true if the file was successful parsed.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "IsIncompatibleWith Database", Keywords = "IsIncompatible Database"), Category = Database)
		bool IsIncompatibleWithDatabase(const FStatement& Statement, FString& IncompatibleKey);

	/**
	* Called to check if a given statement is more specific(contains more information) than any statement in the database.
	* @param Statement - The statement to be compared with the database.
	* @param LessSpecificKeys - The array with all of the keys of the statements that are less specific.
	* @return boolean value of true if the statement is more specific than one of the statements in the database.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Is More Specific", Keywords = "More Specific"), Category = Database)
		bool IsMoreSpecificThanDatabase(const FStatement& Statement, TArray<FString>& LessSpecificKeys);

	/**
	* Called to check if a given statement is less specific(contains less information) than any statement in the database.
	* @param Statement - The statement to be compared with the database.
	* @return boolean value of true if the statement is less specific than one of the statements in the database.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Is Less Specific", Keywords = "Less Specific"), Category = Database)
		bool IsLessSpecifiThanDatabase(const FStatement& Statement);

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
		FStatement FindStatement(const FString& Key);

	/**
	* Called to parse the world file.
	* This function already inserts the statements to the database
	* @return boolean value of true if the file was successful parsed.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Parse World File", Keywords = "Parse World File"), Category = Database)
		bool ParseWorldFile();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Parse World File", Keywords = "Parse World File"), Category = Database)
		bool ParseFactionsFile();

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
		bool HasStatement(const FStatement& Statement);

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
		void DatabaseWasUpdated();

	/**
	* Called to write the content of the database to an external file.
	* File is located in the Content/Databases folder with the name Database.txt
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Write To File", Keywords = "Write File"), Category = Database)
		void WriteToFile();



	/**
	* The predicate function to sort the database.
	*/
	FORCEINLINE static bool ConstPredicate(const FString& key1, const FString& key2)
	{
		return (key1 < key2);
	}

};
