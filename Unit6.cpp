//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit6.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm6 *Form6;
//---------------------------------------------------------------------------
__fastcall TForm6::TForm6(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm6::FormCreate(TObject *Sender)
{
		StringGrid1->Cells[0][0]="�";
		StringGrid1->Cells[1][0]="�������� �������";
		StringGrid1->Cells[2][0]="����";
		StringGrid1->Cells[3][0]="��� �������";
		StringGrid1->Cells[4][0]="������������";
		StringGrid1->Cells[5][0]="��������� ��������";
		StringGrid1->Cells[6][0]="����������� ������";
		StringGrid1->Cells[7][0]="��� ����� � �������";
}
//---------------------------------------------------------------------------
