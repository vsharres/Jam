// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetoJam.h"
#include "Statement.h"



UStatement::UStatement(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Statement = NULL;
	StatementKey = NULL;
	Vertices.Empty();
	Edges.Empty();
}

UStatement* UStatement::NewStatement(const FString& newStatementString)
{
	if (newStatementString == "") //warning message that a statement cannot be initialized with an empty string.
	{
		UE_LOG(StatementLog, Warning, TEXT("Can not initialize a statement with a empty string."));
		return NULL;
	}
	else if (!newStatementString.Contains(".") && !newStatementString.Contains("!")) //warning that a statement cannot have only the root vertex.
	{
		UE_LOG(StatementLog, Warning, TEXT("A statement can not have only the root vertex, it must have at least two vertices."));
		return NULL;
	}

	UStatement* NewStatement = NewObject<UStatement>();

	NewStatement->Statement = newStatementString; //set the text property to the string input.

									/*Temporary string for creating the vertices. */
	FString temp = "";

	/*for each character in the input string, add that character to the temporary string variable,
	then when finds one of the edge characters, add the resulting string to the vertices array,
	and that edge to the edges array.*/
	for (int32 index = 0; index < newStatementString.Len(); index++)
	{
		if (newStatementString[index] == '.') //for edges with the "." inclusion identifier.
		{
			NewStatement->Edges.Add(".");
			NewStatement->Vertices.Add(temp);
			temp = "";

		}
		else if (newStatementString[index] == '!') //for edges with the "!" exclusion identifier
		{
			NewStatement->Edges.Add("!");
			NewStatement->Vertices.Add(temp);
			temp = "";
		}
		else
		{
			temp += newStatementString[index];
		}
	}

	if (temp != "") //this last if is to add the last vertex in the statement, since there is no more edges to be found.
	{
		NewStatement->Vertices.Add(temp);
	}

	//Generate the key to the statement.
	NewStatement->GenerateKey();

	return NewStatement;
}

void UStatement::GenerateKey()
{
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

FString UStatement::GetStatement()
{
	return Statement;
}

FString UStatement::GetStatementKey()
{
	return StatementKey;
}

FString UStatement::GetKeyFromString(const FString& StatementString)
{
	if (StatementString == "")
	{
		return "";
	}

	UStatement* temp = NewObject<UStatement>();
	temp->NewStatement(StatementString);

	FString key = temp->GetStatementKey();

	temp->BeginDestroy();

	return key;
}

TArray<FString> UStatement::GetVertices()
{
	return Vertices;
}

TArray<FString> UStatement::GetEdges()
{
	return Edges;
}

FString UStatement::LastVertex()
{
	return Vertices.Last();
}

FString UStatement::BranchFrom(const int32& index, bool direct /*= true*/)
{
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

bool UStatement::HasSameSignature(const FString& Vertex, UStatement* OtherStatement)
{
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
		if (this->Vertices[index] != OtherStatement->Vertices[index])
		{
			return false;
		}

	}

	return true;
}

bool UStatement::IsEdgeEqual(int32 EdgeIndex, UStatement* OtherStatement)
{
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

bool UStatement::IsIncompatibleWith(UStatement* OtherStatement)
{
	/*if the last vertex of the statement is different from the vertex of the last statement,
	also has the same signature and if either of then has the last edge the exclusion identifier, then they are incompatible with each other.*/
	if (this->Vertices.Last() != OtherStatement->Vertices.Last() &&
		HasSameSignature(this->Vertices.Last(), OtherStatement) &&
		(this->Edges.Last() == "!" || OtherStatement->Edges.Last() == "!"))
	{
		return true;
	}

	return false;
}

bool UStatement::IsStatementValid()
{
	if (!this->IsValidLowLevelFast(true) || this->Statement == "" || this->StatementKey == "" || this->Vertices.Num() <= 1 || this->Edges.Num() == 0)
	{
		return false;
	}

	return true;
}

void UStatement::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if ((PropertyName == GET_MEMBER_NAME_CHECKED(UStatement, Statement)))
	{

	}
}

