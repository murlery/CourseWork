//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
 #include <System.Character.hpp>
#include <fstream>
 #include <System.StrUtils.hpp>

#include "Unit3.h"
#include "Unit2.h"
#include "Unit4.h"
#include "Unit6.h"

#include "Unit4.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;

TStringGrid *TempGrid;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Button1Click(TObject *Sender)
{
	if (Edit1->Text.IsEmpty()) {
		  ShowMessage("����������, ������� ��� �����");
		   return;
		}else{
		double requiredWeight = StrToFloat(Edit1->Text);

		// ������� ���������� ���������, ��������������� �������
		int count = 0;
		for(int i = 1; i < Form3->StringGrid1->RowCount; i++)
		{
			if(StrToFloat(Form3->StringGrid1->Cells[7][i]) > requiredWeight)
			{
				count++;
			}
		}

		// ���� ��� ���������� ���������, ������� �� �������
		if(count == 0)
		{
			ShowMessage("��� ��������� � ����� ����� ������ " + FloatToStr(requiredWeight));
			return;
		}

		// ��������� �������� ������
		TempGrid = new TStringGrid(this);
		TempGrid->ColCount = Form3->StringGrid1->ColCount;
		TempGrid->RowCount = Form3->StringGrid1->RowCount;
		for(int i = 0; i < Form3->StringGrid1->RowCount; i++)
		{
			for(int j = 0; j < Form3->StringGrid1->ColCount; j++)
			{
				TempGrid->Cells[j][i] = Form3->StringGrid1->Cells[j][i];
			}
		}


		Form6->StringGrid1->RowCount = count + 1;
		int rowNumber = 1;
		for(int i = 1; i < TempGrid->RowCount; i++)
		{
			if(StrToFloat(TempGrid->Cells[7][i]) > requiredWeight)
			{
				for(int j = 0; j < Form3->StringGrid1->ColCount; j++)
				{
					Form6->StringGrid1->Cells[j][rowNumber] = TempGrid->Cells[j][i];
				}
				rowNumber++;
			}
		}}
	   Form4->Close();
	   Form6->ShowModal();
       Form4->Edit1->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Edit1KeyPress(TObject *Sender, System::WideChar &Key)
{
  if (!std::isdigit(Key) && Key != VK_BACK && Key!=VK_RETURN ) // ���� ��� �� ����� � �� ������� Backspace
	{   ShowMessage("������� ������ �����");
		Key = 0; // �������� ����
	}
}
//---------------------------------------------------------------------------

