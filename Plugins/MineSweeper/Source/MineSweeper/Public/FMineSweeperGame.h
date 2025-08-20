// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

constexpr int32 GMine		 = -2;
constexpr int32 GUntouched	= -1;
constexpr int32 GSafe		= 0;
constexpr int32 GExploded	= 42;

class FMineSweeperGame
{
public:
	FMineSweeperGame(int32 InWidth, int32 InHeight, int32 InMines);
	
	int32 GetWidth() const { return Width; }
	int32 GetHeight() const { return Height; }
	int32 GetCellValue(int32 X, int32 Y) const;

	bool OnCheckCellSafe(int32 X, int32 Y);
	bool CheckWinCondition() const;

	void UnfoldMineField();

private:
	int32 Width;
	int32 Height;
	int32 Mines;
	TArray<int32> FieldValues;

	int32 ToLinearCell(int32 X, int32 Y) const { return (Width * Y) + X; }
	TArray<int32> GetAdjacentCells(int32 X, int32 Y) const;
};
