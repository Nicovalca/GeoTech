#include "FMineSweeperGame.h"

FMineSweeperGame::FMineSweeperGame(const int32 InWidth, const int32 InHeight, const int32 InMines)
	: Width(InWidth), Height(InHeight), Mines(InMines)
{
	if (Width <=0 || Height <=0)
	{
		UE_LOG(LogTemp, Error, TEXT("You must provide a valid grid size"));
		return;
	}
	
	const int32 Range = Width*Height;	
	FieldValues.Empty();
	FieldValues.Init(GUntouched,Range);

	if (Mines>Range)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot generate a minefield with more mines than cells"));
		return;
	}
	
	for (int32 i = 0; i < Mines; i++)
	{
		bool FoundNewMineSlot = false;
		while (!FoundNewMineSlot)
		{
			int32 NewMine = FMath::RandRange(0, Range-1);
			if (FieldValues[NewMine] != GMine)
			{
				FieldValues[NewMine] = GMine;
				FoundNewMineSlot = true;
			}
		}
	}	
}

// helper from grid to linear cell value
int32 FMineSweeperGame::GetCellValue(int32 X, int32 Y) const
{
	return FieldValues[ToLinearCell(X,Y)];
}

bool FMineSweeperGame::OnCheckCellSafe(int32 X, int32 Y)
{
	int32 LinearCell = ToLinearCell(X,Y);

	if (FieldValues[LinearCell] == GMine)
		return false;
	
	FieldValues[LinearCell] = GSafe;
	TArray<int32> Neighbors = GetAdjacentCells(X,Y);

	// mines Count
	for (auto Neighbor : Neighbors)
	{
		if (FieldValues[Neighbor] == GMine)
			FieldValues[LinearCell] +=1;
	}

	// recursive if empty
	if (FieldValues[LinearCell] != GSafe)
		return true;
	
	for (const int32 Neighbor : Neighbors)
	{
		if (FieldValues[Neighbor] != GUntouched)
			continue;
			
		int32 NeighborX = Neighbor % Width;
		int32 NeighborY = Neighbor / Width;

		OnCheckCellSafe(NeighborX,NeighborY);
	}
	
	return true;
}

bool FMineSweeperGame::CheckWinCondition() const
{
	return !FieldValues.Contains(GUntouched);
}

void FMineSweeperGame::UnfoldMineField()
{
	for (int32& Field : FieldValues)
	{
		if (Field == GMine) Field = GExploded;
		if (Field == GUntouched) Field = GSafe;
	}
}

TArray<int32> FMineSweeperGame::GetAdjacentCells(int32 X, int32 Y) const
{
	TArray<int32> Result;
	for (int32 offsetY = -1; offsetY <= 1; ++offsetY)
	{
		for (int32 offsetX = -1; offsetX <= 1; ++offsetX)
		{
			if (offsetX == 0 && offsetY == 0)
				continue;

			int32 MovedX = X + offsetX;
			int32 MovedY = Y + offsetY;

			if (MovedX >= 0 && MovedX < Width && MovedY >= 0 && MovedY < Height)
			{
				int32 LinearCell = (Width*MovedY)+MovedX;
				if (FieldValues[LinearCell] != GSafe)
					Result.Add(LinearCell);	
			}
		}
	}

	return Result;
}


