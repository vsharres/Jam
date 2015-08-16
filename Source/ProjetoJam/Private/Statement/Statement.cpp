// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ProjetoJam.h"
#include "Public/Statement/Statement.h"

DEFINE_LOG_CATEGORY(StatementLog);


UStatement::UStatement()
{
	this->Text = "";
	this->KeyName = "";
}

FString UStatement::GetText()
{
	return Text;
}

FName UStatement::GetKeyName()
{
	return KeyName;
}

FString UStatement::LastVertex()
{
	return Vertices.Last();
}

FString UStatement::BranchFrom(const int32& index)
{
	if (index >= Vertices.Num())
	{
		UE_LOG(StatementLog, Error, TEXT("Index was out of bounds of the statement %s"), *this->Text);
		return "";
	}
	else if (index == Vertices.Num() - 1)
	{
		return LastVertex();
	}

	FString ToReturn;

	for (int32 i = index; i < Vertices.Num() - 1; i++)
	{
		ToReturn += Vertices[i];
		ToReturn += Edges[i];
	}

	ToReturn += LastVertex();

	return ToReturn;

}

TArray<FString> UStatement::GetVertices()
{
	return Vertices;
}

TArray<FString > UStatement::GetEdges()
{
	return Edges;
}

void UStatement::SetStatement(const FString& Text)
{
	if (Text == "") //warning message that a statement cannot be initialized with an empty string.
	{
		UE_LOG(StatementLog, Warning, TEXT("Can not initialize a statement with a empty string."));
		return;
	}
	else if (!Text.Contains(".") && !Text.Contains("!")) //warning that a statement cannot have only the root vertex.
	{
		UE_LOG(StatementLog, Warning, TEXT("A statement can not have only the root vertex, it must have at least two vertices."));
		return;
	}

	this->Text = Text; //set the text property to the string input.

	/*Temporary string for creating the vertices. */
	FString temp = "";

	/*for each character in the input string, add that character to the temporary string variable,
	then when finds one of the edge characters, add the resulting string to the vertices array,
	and that edge to the edges array.*/
	for (int32 index = 0; index < Text.Len(); index++)
	{
		if (Text[index] == '.') //for edges with the "." inclusion identifier.
		{
			Edges.Add(".");
			Vertices.Add(temp);
			temp = "";

		}
		else if (Text[index] == '!') //for edges with the "!" exclusion identifier
		{
			Edges.Add("!");
			Vertices.Add(temp);
			temp = "";
		}
		else
		{
			temp += Text[index];
		}
	}

	if (temp != "") //this last if is to add the last vertex in the statement, since there is no more edges to be found.
	{
		Vertices.Add(temp);
	}

	//Generate the key to the statement.
	this->GenerateKey();
	this->Rename(*Text);
}


void UStatement::GenerateKey()
{
	//First check if the statement already has all of its vertices.
	if (this->Vertices.Num() > 0)
	{
		FString temp = "";
		/*To generate the key, adds each vertices and the edges to the key,
		the only vertices that is ignored, is the last one, so that when comparing statements, statements that would conflict, can be found more easily.*/
		for (int i = 0; i < Edges.Num();i++)
		{
			temp += Vertices[i];
			temp += Edges[i];
		}

		KeyName = FName(*temp);
	}
	else //warning message
	{
		UE_LOG(StatementLog, Warning, TEXT("Can not generate a key with a statement with no vertices."));
	}

}

bool UStatement::HasSameSignature(const FString& Vertex, UStatement* OtherStatement)
{
	//warning message if the vertex to check is an empty string, or the pointer to the statement to compare is an null pointer.
	if (Vertex == "" || !OtherStatement)
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
	//Warning for a null pointer to the other statement.
	if (!OtherStatement)
	{
		UE_LOG(StatementLog, Warning, TEXT("The comparing statement cannot be null."));
		return false;
	}

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
	//warning for a null pointer to the comparing statement.
	if (!OtherStatement)
	{
		UE_LOG(StatementLog, Warning, TEXT("The comparing statement cannot be null."));
		return true;
	}

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

UStatement* UStatement::NewStatementFromBlueprint(UObject* WorldContextObject, const FString& Statement)
{
	//The world context where to spawn the statement from a blueprint
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject);

	UStatement* tempStatement = (UStatement*)NewObject<UStatement>(UStatement::StaticClass());
	tempStatement->SetStatement(Statement);

	return tempStatement;
}


