#pragma once

#include "CoreMinimal.h"
#include "FMineSweeperGame.h"

class SMineSweeperWidget : public SCompoundWidget
{
public:
	
	SLATE_BEGIN_ARGS(SMineSweeperWidget) {}		
	SLATE_END_ARGS()

	void Construct(const FArguments& args);

private:

	TSharedPtr<FMineSweeperGame> Game;

	TSharedPtr<SBox> GridBox;
	
	void UpdateSlateGrid();
	
	TSharedRef<SWidget> MakeCellWidget(int32 X, int32 Y);

	int32 GridWidth= 6;
	int32 GridHeight = 6;
	int32 MinesCount = 10;	
};
