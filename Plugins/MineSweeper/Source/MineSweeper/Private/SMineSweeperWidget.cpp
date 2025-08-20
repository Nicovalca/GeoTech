#include "SMineSweeperWidget.h"

#include "MineSweeperStyle.h"
#include "Widgets/Input/SNumericEntryBox.h"

void SMineSweeperWidget::Construct(const FArguments& args)
{
	ChildSlot
	[
		SNew(SBox)
			.Padding(5)
			[				
				SNew(SVerticalBox)
				+SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SSplitter)
					+SSplitter::Slot()
					[
						SNew(SBox)
						.Padding(10)
						[
							SNew(SHorizontalBox)			
							+SHorizontalBox::Slot()
							.AutoWidth()					
							.VAlign(VAlign_Top)						
							[
								SNew(STextBlock)						
								.Text(FText::FromString("Width"))
							]
							+SHorizontalBox::Slot()
							.Padding(10,0)
							[
								SNew(SNumericEntryBox<int32>)
								.MinValue(0)
								.MaxValue(50)
								.Value_Lambda([this]() {return GridWidth; })
								.OnValueChanged_Lambda([this](int32 const Value) {GridWidth=Value; })
								
							]
						]
					]
					+SSplitter::Slot()
					[
						SNew(SBox)
						.Padding(10)
						[
							SNew(SHorizontalBox)			
							+SHorizontalBox::Slot()
							.AutoWidth()					
							.VAlign(VAlign_Top)
							[
								SNew(STextBlock)						
								.Text(FText::FromString("Height"))
							]
							+SHorizontalBox::Slot()
							.Padding(10,0)
							[
								SNew(SNumericEntryBox<int32>)
								.MinValue(0)
								.MaxValue(50)
								.Value_Lambda([this]() {return GridHeight; })
								.OnValueChanged_Lambda([this](int32 const Value) {GridHeight=Value; })								
							]
						]
					]
				]
				+SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SHorizontalBox)			
					+SHorizontalBox::Slot()
					.AutoWidth()					
					.VAlign(VAlign_Top)
					.Padding(10,0)
					[
						SNew(STextBlock)						
						.Text(FText::FromString("Number of mines"))
						
					]
					+SHorizontalBox::Slot()
					[
						SNew(SNumericEntryBox<int32>)
						.MinValue(0)
						.MaxValue(50)
						.Value_Lambda([this]() {return MinesCount; })
						.OnValueChanged_Lambda([this](int32 const Value) {MinesCount=Value; })
					]
				]
				+SVerticalBox::Slot()
				.Padding(10)
				.AutoHeight()
				.HAlign(HAlign_Center)				
				[
					SNew(SButton)
					.Text(FText::FromString("Create new game"))
					.HAlign(HAlign_Center)
					.OnClicked_Lambda([this]()
					{
						Game = MakeShared<FMineSweeperGame>(GridWidth, GridHeight, MinesCount);
						UpdateSlateGrid();
						return FReply::Handled();
					})
				]
				+SVerticalBox::Slot()
				.AutoHeight()
				[
					SAssignNew(GridBox, SBox)
				]
			]
		];
	
}

void SMineSweeperWidget::UpdateSlateGrid()
{
	const TSharedRef<SGridPanel> Grid = SNew(SGridPanel);	

	for	(int32 X = 0; X < Game->GetWidth(); X++)
	{
		for (int32 Y = 0; Y < Game->GetHeight(); Y++)
		{
			const int32 LinearCell = (GridWidth*Y)+X;
			
			Grid->AddSlot(X,Y)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			.Padding(2)
			[
				SNew(SBox)
				.WidthOverride(48)
				.HeightOverride(48)
				[	
					SNew(SBorder)
					.BorderImage(FMineSweeperStyle::Get().GetBrush("MineSweeper.GrayBox"))
					[
						MakeCellWidget(X, Y)
					]
				]
			];
		}
	}
	
	GridBox->SetContent(
		SNew(SBorder)
		.Padding(5)
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[			
			Grid
		]
	);
}

TSharedRef<SWidget> SMineSweeperWidget::MakeCellWidget(int32 X, int32 Y)
{
	const int32 CellValue = Game->GetCellValue(X,Y);
	if (CellValue < 0)
	{
		return SNew(SButton)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			.ButtonColorAndOpacity(FLinearColor::Gray)
			.OnClicked(FOnClicked::CreateLambda([this, X, Y]()
			{
				if (!Game->OnCheckCellSafe(X,Y))
				{
					FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("Game Over!")));
					Game->UnfoldMineField();
				}
				else if (Game->CheckWinCondition())
				{
					FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("Field clear!")));
					Game->UnfoldMineField();
				}
				
				UpdateSlateGrid();
				return FReply::Handled();
			}));
	}

	// regular field already iteracted
	return SNew(SBorder)
		.BorderImage(FMineSweeperStyle::Get().GetBrush(CellValue == GExploded ? "MineSweeper.RedBox" : "MineSweeper.BlackBox"))
		.Padding(2)
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.Text(CellValue > 0 ? FText::AsNumber(CellValue) : FText::GetEmpty())
		];
}
