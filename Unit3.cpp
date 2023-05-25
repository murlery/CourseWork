//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <fstream>
#include <System.StrUtils.hpp>
#include <string>


#include "Unit3.h"
#include "Unit2.h"
#include "Unit4.h"
#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
TStringGrid *TempGrid;  // ���������� ���������� � ����� ������ TForm3

struct Product {
	int id;
	char name[50];
	double price;
	double weight;
	char manufacturer[50];
	char material[50];
	char gem[50];
	double gemWeight;
};
 //std::vector<Product> products;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
}

void __fastcall TForm3::N4Click(TObject *Sender)
{
	if (!currentFileName.IsEmpty()) {
		std::ofstream outFile(currentFileName.c_str(), std::ios::out | std::ios::binary);
		if (!outFile) {
			ShowMessage("������ ��� ���������� �����");
		} else {
			Product product;
			for (int i = 1; i < StringGrid1->RowCount; i++) { // �������� � 1, ����� ���������� ���������
				product.id = StrToInt(StringGrid1->Cells[0][i]);
				strncpy(product.name, AnsiString(StringGrid1->Cells[1][i]).c_str(), sizeof(product.name));
				product.price = StrToFloat(StringGrid1->Cells[2][i]);
				product.weight = StrToFloat(StringGrid1->Cells[3][i]);
				strncpy(product.manufacturer, AnsiString(StringGrid1->Cells[4][i]).c_str(), sizeof(product.manufacturer));
				strncpy(product.material, AnsiString(StringGrid1->Cells[5][i]).c_str(), sizeof(product.material));
				strncpy(product.gem, AnsiString(StringGrid1->Cells[6][i]).c_str(), sizeof(product.gem));
				product.gemWeight = StrToFloat(StringGrid1->Cells[7][i]);
				outFile.write((char*)&product, sizeof(Product));
			}
			outFile.close();
			ShowMessage("���� ������� ��������");
		}
	} else {
		ShowMessage("������: ��� ��������� ����� ��� ����������");
		StatusBar1->Panels->Items[0]->Text = "������ ����������";
	}
}


//---------------------------------------------------------------------------
void __fastcall TForm3::FormCreate(TObject *Sender)
{
		StringGrid1->Cells[0][0]="�";
		StringGrid1->Cells[1][0]="�������� �������";
		StringGrid1->Cells[2][0]="����";
		StringGrid1->Cells[3][0]="��� �������";
		StringGrid1->Cells[4][0]="������������";
		StringGrid1->Cells[5][0]="��������� ��������";
		StringGrid1->Cells[6][0]="����������� ������";
		StringGrid1->Cells[7][0]="��� ����� � �������";

		Form5=new TForm5 (this);
		Form5->ShowModal();
		Form5->Free();
}
//---------------------------------------------------------------------------

//��������

void __fastcall TForm3::N12Click(TObject *Sender)
{
	int row = StringGrid1->Row; // �������� ������ ������� ������
	if (row >= 1 && row < StringGrid1->RowCount) // ���������, ��� ������ ������������� ����������
	{
		if (MessageDlg("�� �������, ��� ������ ������� ������ ��� �������: " +StringGrid1->Cells[0][row]+"\n�������� �������: "+StringGrid1->Cells[1][row]+"\n���� �������: "+StringGrid1->Cells[2][row]+"\n��� �������: "+StringGrid1->Cells[3][row]+"\n������������: "+StringGrid1->Cells[4][row]+"\n�������� ��������: "+StringGrid1->Cells[5][row]+"\n����������� ������: "+StringGrid1->Cells[6][row]+"\n��� �����: "+StringGrid1->Cells[7][row], mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
		{
			for (int i = row; i < StringGrid1->RowCount - 1; i++)
			{
				for (int j = 0; j < StringGrid1->ColCount; j++)
				{
					StringGrid1->Cells[j][i] = StringGrid1->Cells[j][i + 1]; // �������� ��� ������ ����� �� ���� �������
				}
			}
			StringGrid1->RowCount--; // ��������� ���������� ����� �� 1

			// ��������� ������ �����
			for (int i = 1; i < StringGrid1->RowCount; i++)
			{
				StringGrid1->Cells[0][i] = IntToStr(i);
			}
		}
	}
    int rCount;
  for (int i = 0; i < StringGrid1->RowCount; i++)
  {
      rCount = i;
  }
  StatusBar1->Panels->Items[0]->Text = "����� ���������: " + IntToStr(rCount);
}

//---------------------------------------------------------------------------



 //��������������
void __fastcall TForm3::N11Click(TObject *Sender)
{
	if (StringGrid1->Row > 0) { // ���� ������� ������
		// ��������� ���� �� Form2 ������� �� ��������� ������
		Form2->Edit1->Text = StringGrid1->Cells[1][StringGrid1->Row];
		Form2->Edit2->Text = StringGrid1->Cells[2][StringGrid1->Row];
		Form2->Edit3->Text = StringGrid1->Cells[3][StringGrid1->Row];
		Form2->Edit4->Text = StringGrid1->Cells[4][StringGrid1->Row];
		Form2->Edit5->Text = StringGrid1->Cells[5][StringGrid1->Row];
		Form2->Edit6->Text = StringGrid1->Cells[6][StringGrid1->Row];
		Form2->Edit7->Text = StringGrid1->Cells[7][StringGrid1->Row];
		Form2->Button1->Caption = "�������������"; // ��������������� Button1 �� "�������������"
		Form2->ShowModal(); // ��������� Form2
	} else {
		ShowMessage("�������� ������ ��� ��������������");
	}
    int rCount;
  for (int i = 0; i < StringGrid1->RowCount; i++)
  {
      rCount = i;
  }
  StatusBar1->Panels->Items[0]->Text = "����� ���������: " + IntToStr(rCount);
}
//---------------------------------------------------------------------------


//---�������� ��������� �����
void __fastcall TForm3::N2Click(TObject *Sender)
{
	SaveDialog1->Filter = "Binary files (*.bin)|*.bin";
	SaveDialog1->DefaultExt = "bin";

if (SaveDialog1->Execute()) {
	std::ofstream outFile(SaveDialog1->FileName.c_str(), std::ios::out | std::ios::binary);
	if (!outFile) {
		ShowMessage("������ ��� �������� �����");
	} else {
		ShowMessage("���� ������� ������");
		outFile.close();
		currentFileName = SaveDialog1->FileName;  // ���������� currentFileName �����
	}
}
}
//---------------------------------------------------------------------------

//---�������� ��������� �����
void __fastcall TForm3::N3Click(TObject *Sender)
{
	OpenDialog1->Filter = "Binary files (*.bin)|*.bin";
	OpenDialog1->DefaultExt = "bin";
	if (OpenDialog1->Execute()) {
		std::ifstream inFile(OpenDialog1->FileName.c_str(), std::ios::in | std::ios::binary);
		if (!inFile) {
			ShowMessage("������ ��� �������� �����");
		} else {
			currentFileName = OpenDialog1->FileName; // ��������� currentFileName

			Product product;
			StringGrid1->RowCount = 2; // ��������� � ������ ������ ������
			while (inFile.read((char*)&product, sizeof(Product))) {
				StringGrid1->Cells[0][StringGrid1->RowCount - 1] = product.id;
				StringGrid1->Cells[1][StringGrid1->RowCount - 1] = product.name;
				StringGrid1->Cells[2][StringGrid1->RowCount - 1] = product.price;
				StringGrid1->Cells[3][StringGrid1->RowCount - 1] = product.weight;
				StringGrid1->Cells[4][StringGrid1->RowCount - 1] = product.manufacturer;
				StringGrid1->Cells[5][StringGrid1->RowCount - 1] = product.material;
				StringGrid1->Cells[6][StringGrid1->RowCount - 1] = product.gem;
				StringGrid1->Cells[7][StringGrid1->RowCount - 1] = product.gemWeight;
				StringGrid1->RowCount++; // ��������� ������ ��� ���������� ��������
			}
			StringGrid1->RowCount--; // ������� ������ ������ � �����
			inFile.close();
		}
	}
}



//---------------------------------------------------------------------------

//����������
void __fastcall TForm3::N5Click(TObject *Sender)
{
SaveDialog1->Filter = "Binary files (*.bin)|*.bin";
	SaveDialog1->DefaultExt = "bin";
	if (SaveDialog1->Execute()) {
		currentFileName = SaveDialog1->FileName;
		std::ofstream outFile(currentFileName.c_str(), std::ios::out | std::ios::binary);
		if (!outFile) {
			ShowMessage("������");
		} else {
			Product product;
			for (int i = 1; i < StringGrid1->RowCount; i++)
			{
				product.id = StrToInt(StringGrid1->Cells[0][i]);
				strncpy(product.name, AnsiString(StringGrid1->Cells[1][i]).c_str(), sizeof(product.name));
				product.price = StrToFloat(StringGrid1->Cells[2][i]);
				product.weight = StrToFloat(StringGrid1->Cells[3][i]);
				strncpy(product.manufacturer, AnsiString(StringGrid1->Cells[4][i]).c_str(), sizeof(product.manufacturer));
				strncpy(product.material, AnsiString(StringGrid1->Cells[5][i]).c_str(), sizeof(product.material));
				strncpy(product.gem, AnsiString(StringGrid1->Cells[6][i]).c_str(), sizeof(product.gem));
				product.gemWeight = StrToFloat(StringGrid1->Cells[7][i]);
				outFile.write((char*)&product, sizeof(Product));
			}
			outFile.close();
			ShowMessage("���� ��������");
		}
	}

}

//---------------------------------------------------------------------------
//����� �� ������ �������
void __fastcall TForm3::N7Click(TObject *Sender)
{
  UnicodeString searchText = InputBox("�����", "������� ����� �������", "");
  int searchType = MessageDlg("����� �� ������� ����������?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel, 0);

  // ������ ����������
  if (searchType == mrYes) {
	for (int i = 1; i < StringGrid1->RowCount; i++) {
	  if (StringGrid1->Cells[0][i] == searchText) {
		StringGrid1->Row = i; // �������� ��������� ������
		ShowMessage("������� ������� �� ������\nH���� �������: " + searchText +"\n�������� �������: "+StringGrid1->Cells[1][i]+"\n���� �������: "+StringGrid1->Cells[2][i]+"\n��� �������: "+StringGrid1->Cells[3][i]+"\n������������: "+StringGrid1->Cells[4][i]+"\n�������� ��������: "+StringGrid1->Cells[5][i]+"\n����������� ������: "+StringGrid1->Cells[6][i]+"\n��� �����: "+StringGrid1->Cells[7][i]);
		return;
	  }
	}
  }
  // ������ ������
  else if (searchType == mrNo) {
	for (int i = 1; i < StringGrid1->RowCount; i++) {
	  if (AnsiStartsText(searchText, StringGrid1->Cells[0][i]))
	   {
		StringGrid1->Row = i; // �������� ��������� ������
		ShowMessage("������ ����� �������: " + StringGrid1->Cells[0][i]+"\n�������� �������: "+StringGrid1->Cells[1][i]+"\n���� �������: "+StringGrid1->Cells[2][i]+"\n��� �������: "+StringGrid1->Cells[3][i]+"\n������������: "+StringGrid1->Cells[4][i]+"\n�������� ��������: "+StringGrid1->Cells[5][i]+"\n����������� ������: "+StringGrid1->Cells[6][i]+"\n��� �����: "+StringGrid1->Cells[7][i]);
		return;
	  }
	}
  }
  // ������
  else {
	return;
  }

  ShowMessage("������� �� ������ �� �������");
}




//---------------------------------------------------------------------------

//����� �� �������� �������
void __fastcall TForm3::N22Click(TObject *Sender)
{
   UnicodeString searchText = InputBox("�����", "������� �������� �������", "");
   int searchType = MessageDlg("����� �� ������� ����������?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel, 0);
   // ������ ����������
  if (searchType == mrYes) {
	for (int i = 1; i < StringGrid1->RowCount; i++) {
	  if (StringGrid1->Cells[1][i] == searchText) {
		StringGrid1->Row = i; // �������� ��������� ������
		ShowMessage("������� ������� �� ��������\n����� �������: " + searchText +"\n�������� �������: "+StringGrid1->Cells[1][i]+"\n���� �������: "+StringGrid1->Cells[2][i]+"\n��� �������: "+StringGrid1->Cells[3][i]+"\n������������: "+StringGrid1->Cells[4][i]+"\n�������� ��������: "+StringGrid1->Cells[5][i]+"\n����������� ������: "+StringGrid1->Cells[6][i]+"\n��� �����: "+StringGrid1->Cells[7][i]);
		return;
	  }
	}
  }
  // ������ ������
  else if (searchType == mrNo) {
	for (int i = 1; i < StringGrid1->RowCount; i++) {
	  if (AnsiStartsText(searchText, StringGrid1->Cells[1][i]))
	   {
		StringGrid1->Row = i; // �������� ��������� ������
		ShowMessage("������� ������� �� ��������\n����� �������: " +StringGrid1->Cells[0][i]  +"\n�������� �������: "+StringGrid1->Cells[1][i]+"\n���� �������: "+StringGrid1->Cells[2][i]+"\n��� �������: "+StringGrid1->Cells[3][i]+"\n������������: "+StringGrid1->Cells[4][i]+"\n�������� ��������: "+StringGrid1->Cells[5][i]+"\n����������� ������: "+StringGrid1->Cells[6][i]+"\n��� �����: "+StringGrid1->Cells[7][i]);
		return;
	  }
	}
  }
  // ������
  else {
	return;
  }
	ShowMessage("������� �� �������� �� �������");

}
//---------------------------------------------------------------------------
//����� �� ���� �������
void __fastcall TForm3::N23Click(TObject *Sender)
{
   UnicodeString searchText = InputBox("�����", "������� ���� �������", "");
   int searchType = MessageDlg("����� �� ������� ����������?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel, 0);
   // ������ ����������
  if (searchType == mrYes) {
	for (int i = 1; i < StringGrid1->RowCount; i++) {
	  if (StringGrid1->Cells[2][i] == searchText) {
		StringGrid1->Row = i; // �������� ��������� ������
		ShowMessage("������� ������� �� ����\n����� �������: " + searchText +"\n�������� �������: "+StringGrid1->Cells[1][i]+"\n���� �������: "+StringGrid1->Cells[2][i]+"\n��� �������: "+StringGrid1->Cells[3][i]+"\n������������: "+StringGrid1->Cells[4][i]+"\n�������� ��������: "+StringGrid1->Cells[5][i]+"\n����������� ������: "+StringGrid1->Cells[6][i]+"\n��� �����: "+StringGrid1->Cells[7][i]);
		return;
	  }
	}
  }
  // ������ ������
  else if (searchType == mrNo) {
	for (int i = 1; i < StringGrid1->RowCount; i++) {
	  if (AnsiStartsText(searchText, StringGrid1->Cells[2][i]))
	   {
		StringGrid1->Row = i; // �������� ��������� ������
		ShowMessage("������� ������� �� ����\n����� �������: " +StringGrid1->Cells[0][i]  +"\n�������� �������: "+StringGrid1->Cells[1][i]+"\n���� �������: "+StringGrid1->Cells[2][i]+"\n��� �������: "+StringGrid1->Cells[3][i]+"\n������������: "+StringGrid1->Cells[4][i]+"\n�������� ��������: "+StringGrid1->Cells[5][i]+"\n����������� ������: "+StringGrid1->Cells[6][i]+"\n��� �����: "+StringGrid1->Cells[7][i]);
		return;
	  }
	}
  }
  // ������
  else {
	return;
  }
	ShowMessage("������� �� ���� �� �������");

}
//---------------------------------------------------------------------------
//����� �� ���� �������
void __fastcall TForm3::N24Click(TObject *Sender)
{
   UnicodeString searchText = InputBox("�����", "������� ��� �������", "");
   int searchType = MessageDlg("����� �� ������� ����������?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel, 0);
   // ������ ����������
  if (searchType == mrYes) {
	for (int i = 1; i < StringGrid1->RowCount; i++) {
	  if (StringGrid1->Cells[3][i] == searchText) {
		StringGrid1->Row = i; // �������� ��������� ������
		ShowMessage("������� ������� �� ����\n����� �������: " + searchText +"\n�������� �������: "+StringGrid1->Cells[1][i]+"\n���� �������: "+StringGrid1->Cells[2][i]+"\n��� �������: "+StringGrid1->Cells[3][i]+"\n������������: "+StringGrid1->Cells[4][i]+"\n�������� ��������: "+StringGrid1->Cells[5][i]+"\n����������� ������: "+StringGrid1->Cells[6][i]+"\n��� �����: "+StringGrid1->Cells[7][i]);
		return;
	  }
	}
  }
  // ������ ������
  else if (searchType == mrNo) {
	for (int i = 1; i < StringGrid1->RowCount; i++) {
	  if (AnsiStartsText(searchText, StringGrid1->Cells[3][i]))
	   {
		StringGrid1->Row = i; // �������� ��������� ������
		ShowMessage("������� ������� �� ����\n����� �������: " +StringGrid1->Cells[0][i]  +"\n�������� �������: "+StringGrid1->Cells[1][i]+"\n���� �������: "+StringGrid1->Cells[2][i]+"\n��� �������: "+StringGrid1->Cells[3][i]+"\n������������: "+StringGrid1->Cells[4][i]+"\n�������� ��������: "+StringGrid1->Cells[5][i]+"\n����������� ������: "+StringGrid1->Cells[6][i]+"\n��� �����: "+StringGrid1->Cells[7][i]);
		return;
	  }
	}
  }
  // ������
  else {
	return;
  }
	ShowMessage("������� �� ���� �� �������");

}
//---------------------------------------------------------------------------
//����� �� ������������ �������
void __fastcall TForm3::N25Click(TObject *Sender)
{
	 UnicodeString searchText = InputBox("�����", "������� ������������ �������", "");
   int searchType = MessageDlg("����� �� ������� ����������?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel, 0);
   // ������ ����������
  if (searchType == mrYes) {
	for (int i = 1; i < StringGrid1->RowCount; i++) {
	  if (StringGrid1->Cells[4][i] == searchText) {
		StringGrid1->Row = i; // �������� ��������� ������
		ShowMessage("������� ������� �� ������������\n����� �������: " + searchText +"\n�������� �������: "+StringGrid1->Cells[1][i]+"\n���� �������: "+StringGrid1->Cells[2][i]+"\n��� �������: "+StringGrid1->Cells[3][i]+"\n������������: "+StringGrid1->Cells[4][i]+"\n�������� ��������: "+StringGrid1->Cells[5][i]+"\n����������� ������: "+StringGrid1->Cells[6][i]+"\n��� �����: "+StringGrid1->Cells[7][i]);
		return;
	  }
	}
  }
  // ������ ������
  else if (searchType == mrNo) {
	for (int i = 1; i < StringGrid1->RowCount; i++) {
	  if (AnsiStartsText(searchText, StringGrid1->Cells[4][i]))
	   {
		StringGrid1->Row = i; // �������� ��������� ������
		ShowMessage("������� ������� �� ������������\n����� �������: " +StringGrid1->Cells[0][i]  +"\n�������� �������: "+StringGrid1->Cells[1][i]+"\n���� �������: "+StringGrid1->Cells[2][i]+"\n��� �������: "+StringGrid1->Cells[3][i]+"\n������������: "+StringGrid1->Cells[4][i]+"\n�������� ��������: "+StringGrid1->Cells[5][i]+"\n����������� ������: "+StringGrid1->Cells[6][i]+"\n��� �����: "+StringGrid1->Cells[7][i]);
		return;
	  }
	}
  }
  // ������
  else {
	return;
  }
	ShowMessage("������� �� ������������ �� �������");

}
//---------------------------------------------------------------------------
 //����� �� ��������� ��������� �������
void __fastcall TForm3::N26Click(TObject *Sender)
{
	  UnicodeString searchText = InputBox("�����", "������� �������� �������� �������", "");
   int searchType = MessageDlg("����� �� ������� ����������?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel, 0);
   // ������ ����������
  if (searchType == mrYes) {
	for (int i = 1; i < StringGrid1->RowCount; i++) {
	  if (StringGrid1->Cells[5][i] == searchText) {
		StringGrid1->Row = i; // �������� ��������� ������
		ShowMessage("������� ������� �� ��������� ���������\n����� �������: " + searchText +"\n�������� �������: "+StringGrid1->Cells[1][i]+"\n���� �������: "+StringGrid1->Cells[2][i]+"\n��� �������: "+StringGrid1->Cells[3][i]+"\n������������: "+StringGrid1->Cells[4][i]+"\n�������� ��������: "+StringGrid1->Cells[5][i]+"\n����������� ������: "+StringGrid1->Cells[6][i]+"\n��� �����: "+StringGrid1->Cells[7][i]);
		return;
	  }
	}
  }
  // ������ ������
  else if (searchType == mrNo) {
	for (int i = 1; i < StringGrid1->RowCount; i++) {
	  if (AnsiStartsText(searchText, StringGrid1->Cells[5][i]))
	   {
		StringGrid1->Row = i; // �������� ��������� ������
		ShowMessage("������� ������� �� ��������� ���������\n����� �������: " +StringGrid1->Cells[0][i]  +"\n�������� �������: "+StringGrid1->Cells[1][i]+"\n���� �������: "+StringGrid1->Cells[2][i]+"\n��� �������: "+StringGrid1->Cells[3][i]+"\n������������: "+StringGrid1->Cells[4][i]+"\n�������� ��������: "+StringGrid1->Cells[5][i]+"\n����������� ������: "+StringGrid1->Cells[6][i]+"\n��� �����: "+StringGrid1->Cells[7][i]);
		return;
	  }
	}
  }
  // ������
  else {
	return;
  }
	ShowMessage("������� �� ��������� ��������� �� �������");

}
//---------------------------------------------------------------------------
//����� �� ������������ ����� �������
void __fastcall TForm3::N27Click(TObject *Sender)
{
	 UnicodeString searchText = InputBox("�����", "������� ����������� ������ �������", "");
   int searchType = MessageDlg("����� �� ������� ����������?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel, 0);
   // ������ ����������
  if (searchType == mrYes) {
	for (int i = 1; i < StringGrid1->RowCount; i++) {
	  if (StringGrid1->Cells[6][i] == searchText) {
		StringGrid1->Row = i; // �������� ��������� ������
		ShowMessage("������� ������� �� ������������ �����\n����� �������: " + searchText +"\n�������� �������: "+StringGrid1->Cells[1][i]+"\n���� �������: "+StringGrid1->Cells[2][i]+"\n��� �������: "+StringGrid1->Cells[3][i]+"\n������������: "+StringGrid1->Cells[4][i]+"\n�������� ��������: "+StringGrid1->Cells[5][i]+"\n����������� ������: "+StringGrid1->Cells[6][i]+"\n��� �����: "+StringGrid1->Cells[7][i]);
		return;
	  }
	}
  }
  // ������ ������
  else if (searchType == mrNo) {
	for (int i = 1; i < StringGrid1->RowCount; i++) {
	  if (AnsiStartsText(searchText, StringGrid1->Cells[6][i]))
	   {
		StringGrid1->Row = i; // �������� ��������� ������
		ShowMessage("������� ������� �� ������������ �����\n����� �������: " +StringGrid1->Cells[0][i]  +"\n�������� �������: "+StringGrid1->Cells[1][i]+"\n���� �������: "+StringGrid1->Cells[2][i]+"\n��� �������: "+StringGrid1->Cells[3][i]+"\n������������: "+StringGrid1->Cells[4][i]+"\n�������� ��������: "+StringGrid1->Cells[5][i]+"\n����������� ������: "+StringGrid1->Cells[6][i]+"\n��� �����: "+StringGrid1->Cells[7][i]);
		return;
	  }
	}
  }
  // ������
  else {
	return;
  }
	ShowMessage("������� �� ������������ ����� �� �������");

}
//---------------------------------------------------------------------------
//����� �� ���� �����
void __fastcall TForm3::N28Click(TObject *Sender)
{
	 UnicodeString searchText = InputBox("�����", "������� ��� ����� �������", "");
   int searchType = MessageDlg("����� �� ������� ����������?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel, 0);
   // ������ ����������
  if (searchType == mrYes) {
	for (int i = 1; i < StringGrid1->RowCount; i++) {
	  if (StringGrid1->Cells[7][i] == searchText) {
		StringGrid1->Row = i; // �������� ��������� ������
		ShowMessage("������� ������� �� ���� �����\n����� �������: " + searchText +"\n�������� �������: "+StringGrid1->Cells[1][i]+"\n���� �������: "+StringGrid1->Cells[2][i]+"\n��� �������: "+StringGrid1->Cells[3][i]+"\n������������: "+StringGrid1->Cells[4][i]+"\n�������� ��������: "+StringGrid1->Cells[5][i]+"\n����������� ������: "+StringGrid1->Cells[6][i]+"\n��� �����: "+StringGrid1->Cells[7][i]);
		return;
	  }
	}
  }
  // ������ ������
  else if (searchType == mrNo) {
	for (int i = 1; i < StringGrid1->RowCount; i++) {
	  if (AnsiStartsText(searchText, StringGrid1->Cells[7][i]))
	   {
		StringGrid1->Row = i; // �������� ��������� ������
		ShowMessage("������� ������� �� ���� �����\n����� �������: " +StringGrid1->Cells[0][i]  +"\n�������� �������: "+StringGrid1->Cells[1][i]+"\n���� �������: "+StringGrid1->Cells[2][i]+"\n��� �������: "+StringGrid1->Cells[3][i]+"\n������������: "+StringGrid1->Cells[4][i]+"\n�������� ��������: "+StringGrid1->Cells[5][i]+"\n����������� ������: "+StringGrid1->Cells[6][i]+"\n��� �����: "+StringGrid1->Cells[7][i]);
		return;
	  }
	}
  }
  // ������
  else {
	return;
  }
	ShowMessage("������� �� ���� ����� �� �������");

}
//---------------------------------------------------------------------------





//---------------------------------------------------------------------------

void __fastcall TForm3::N21Click(TObject *Sender)
{
  ShowMessage("������ ������������ ��������: 1.0.0 \n���� �������� ��������� ���������: 16.05.2023 \n�����: ���������� �������");
}
//---------------------------------------------------------------------------

void __fastcall TForm3::N20Click(TObject *Sender)
{

	 ShowMessage("�������� ������ � ���������� ��������� �������. \n1. ��������: ��� ��������� ������������� ��� ���������� �������� � ��������� �������� � ��������. � ������� ��� �� ������ ���������, ������������� � ������� ���������� � ��������, � ����� ��������� ����� � ���������� ������. \n2. ��������� � ������: ��������� �� ������� ���������. ������ ��������� ����������� ���� ��� ������ ������. \n3. ������� � �����������: \n����:\n- �������: ������� ����� ���� ��� ����� ������ � ������ � ������.\n- �������: ��������� ������� � ������� ������������ ���� � �������.\n- ���������: ��������� ������� ������ � �������� ����.\n- ��������� ���: ��������� ��������� ������� ������ � ����� ����.\n������:\n- ���������� ������.\n- �������������� �������\n- �������� ������.\n���������:\n-�����.\n- ����������.");

}

//---------------------------------------------------------------------------


void __fastcall TForm3::N19Click(TObject *Sender)
{
	ShowMessage("� ��������� �������� ��������� �������� ��������� � ����: �������� �������, ����, ��� �������, ������������, �������� ��������, ����������� ������, ��� ����� (� �������). �������� ���������, ����������� ������ ������� ��������������� � ������� ����������� ����. ������ ������ �������, ��� ����� � ������� ��������� ��������.");
}

//---------------------------------------------------------------------------

void __fastcall TForm3::FormClose(TObject *Sender, TCloseAction &Action)
{
	// ���������, ��������� �� ������
	if (!dataSaved) {
		if (MessageBox(NULL, L"�� �� ��������� ���� ������. �� ������ ��������� �� ����� �������?", L"��������������", MB_YESNO | MB_ICONQUESTION) == IDYES) {
			N4Click(NULL);
		}
	}
}

//---------------------------------------------------------------------------


void __fastcall TForm3::N10Click(TObject *Sender)
{
	   Form2->Button1->Caption = "��������"; // ��������������� Button1 �� "�������������"
		Form2->ShowModal(); // ��������� Form2
        int rCount;
  for (int i = 0; i < StringGrid1->RowCount; i++)
  {
      rCount = i;
  }
  StatusBar1->Panels->Items[0]->Text = "����� ���������: " + IntToStr(rCount);
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------

void __fastcall TForm3::Edit2KeyPress(TObject *Sender, System::WideChar &Key)
{
  if (!std::isdigit(Key) && Key != VK_BACK && Key!=VK_RETURN)// ���� ��� �� ����� � �� ������� Backspace
	{   ShowMessage("������� ������ ����� ��� ��������");
		Key = 0; // �������� ����
	}
}
//---------------------------------------------------------------------------


//���������� �� ����������� ������---------------------------------------------------------------------------

void __fastcall TForm3::N34Click(TObject *Sender)
{
	 for (int i = 1; i < StrToInt(StringGrid1->RowCount); i++) { // �������� � 1, ����� ���������� ��������� �������
		for (int j = i + 1; j < StrToInt(StringGrid1->RowCount); j++) {
			if (StrToInt(StringGrid1->Cells[0][j]) < StrToInt(StringGrid1->Cells[0][i])) {
				// ������ ������� ������, ���� �������� � ��������� ������ ������ �������� � �������
				for (int k = 0; k < StringGrid1->ColCount; k++) {
					UnicodeString temp = StringGrid1->Cells[k][i];
					StringGrid1->Cells[k][i] = StringGrid1->Cells[k][j];
					StringGrid1->Cells[k][j] = temp;
				}
			}
		}
	}
}
 //���� ����� ��������
void __fastcall TForm3::N35Click(TObject *Sender)
{
	 for (int i = 1; i < StrToInt(StringGrid1->RowCount); i++) { // �������� � 1, ����� ���������� ��������� �������
		for (int j = i + 1; j < StrToInt(StringGrid1->RowCount); j++) {
			if (StrToInt(StringGrid1->Cells[0][j]) > StrToInt(StringGrid1->Cells[0][i])) {
				// ������ ������� ������, ���� �������� � ��������� ������ ������ �������� � �������
				for (int k = 0; k < StringGrid1->ColCount; k++) {
					UnicodeString temp = StringGrid1->Cells[k][i];
					StringGrid1->Cells[k][i] = StringGrid1->Cells[k][j];
					StringGrid1->Cells[k][j] = temp;
				}
			}
		}
	}
}

 //���� �������� �� ����
void __fastcall TForm3::N36Click(TObject *Sender)
{
   for (int i = 1; i < StringGrid1->RowCount; i++) { // �������� � 1, ����� ���������� ��������� �������
		for (int j = i + 1; j < StringGrid1->RowCount; j++) {
			if (StringGrid1->Cells[1][j].CompareIC(StringGrid1->Cells[1][i]) < 0) {
				// ������ ������� ������, ���� �������� � ��������� ������ ������ �������� � �������
				for (int k = 1; k < StringGrid1->ColCount; k++) {
					UnicodeString temp = StringGrid1->Cells[k][i];
					StringGrid1->Cells[k][i] = StringGrid1->Cells[k][j];
					StringGrid1->Cells[k][j] = temp;
				}
			}
		}
	}

 }

//---------------------------------------------------------------------------

//���� �� ���� ����
void __fastcall TForm3::N40Click(TObject *Sender)
{
  for (int i = 1; i < StrToInt(StringGrid1->RowCount); i++) { // �������� � 1, ����� ���������� ��������� �������
		for (int j = i + 1; j < StrToInt(StringGrid1->RowCount); j++) {
			if (StrToInt(StringGrid1->Cells[2][j]) < StrToInt(StringGrid1->Cells[2][i])) {
				// ������ ������� ������, ���� �������� � ��������� ������ ������ �������� � �������
				for (int k = 0; k < StringGrid1->ColCount; k++) {
					UnicodeString temp = StringGrid1->Cells[k][i];
					StringGrid1->Cells[k][i] = StringGrid1->Cells[k][j];
					StringGrid1->Cells[k][j] = temp;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
 //���� �������� �� ��������
void __fastcall TForm3::N38Click(TObject *Sender)
{
  for (int i = 1; i < StringGrid1->RowCount; i++) { // �������� � 1, ����� ���������� ��������� �������
		for (int j = i + 1; j < StringGrid1->RowCount; j++) {
			if (StringGrid1->Cells[1][j].CompareIC(StringGrid1->Cells[1][i]) > 0) {
				// ������ ������� ������, ���� �������� � ��������� ������ ������ �������� � �������
				for (int k = 1; k < StringGrid1->ColCount; k++) {
					UnicodeString temp = StringGrid1->Cells[k][i];
					StringGrid1->Cells[k][i] = StringGrid1->Cells[k][j];
					StringGrid1->Cells[k][j] = temp;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
 void __fastcall TForm3::N37Click(TObject *Sender)
{
   Form4->ShowModal();
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------

void __fastcall TForm3::StringGrid1SelectCell(TObject *Sender, int ACol, int ARow,
		  bool &CanSelect)
{
   StatusBar1->Panels->Items[2]->Text = "���������� ������: " + IntToStr(ARow);
   StatusBar1->Panels->Items[3]->Text = "�������: " + IntToStr(ACol);
}
//�� ���� ����
void __fastcall TForm3::N41Click(TObject *Sender)
{
    for (int i = 1; i < StrToInt(StringGrid1->RowCount); i++) { // �������� � 1, ����� ���������� ��������� �������
		for (int j = i + 1; j < StrToInt(StringGrid1->RowCount); j++) {
			if (StrToInt(StringGrid1->Cells[2][j]) > StrToInt(StringGrid1->Cells[2][i])) {
				// ������ ������� ������, ���� �������� � ��������� ������ ������ �������� � �������
				for (int k = 0; k < StringGrid1->ColCount; k++) {
					UnicodeString temp = StringGrid1->Cells[k][i];
					StringGrid1->Cells[k][i] = StringGrid1->Cells[k][j];
					StringGrid1->Cells[k][j] = temp;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
 //�� ���� ����
void __fastcall TForm3::N43Click(TObject *Sender)
{
   for (int i = 1; i < StrToInt(StringGrid1->RowCount); i++) { // �������� � 1, ����� ���������� ��������� �������
		for (int j = i + 1; j < StrToInt(StringGrid1->RowCount); j++) {
			if (StrToInt(StringGrid1->Cells[3][j]) < StrToInt(StringGrid1->Cells[3][i])) {
				// ������ ������� ������, ���� �������� � ��������� ������ ������ �������� � �������
				for (int k = 0; k < StringGrid1->ColCount; k++) {
					UnicodeString temp = StringGrid1->Cells[k][i];
					StringGrid1->Cells[k][i] = StringGrid1->Cells[k][j];
					StringGrid1->Cells[k][j] = temp;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
//�� ���� ����
void __fastcall TForm3::N44Click(TObject *Sender)
{
     for (int i = 1; i < StrToInt(StringGrid1->RowCount); i++) { // �������� � 1, ����� ���������� ��������� �������
		for (int j = i + 1; j < StrToInt(StringGrid1->RowCount); j++) {
			if (StrToInt(StringGrid1->Cells[3][j]) > StrToInt(StringGrid1->Cells[3][i])) {
				// ������ ������� ������, ���� �������� � ��������� ������ ������ �������� � �������
				for (int k = 0; k < StringGrid1->ColCount; k++) {
					UnicodeString temp = StringGrid1->Cells[k][i];
					StringGrid1->Cells[k][i] = StringGrid1->Cells[k][j];
					StringGrid1->Cells[k][j] = temp;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
 //  �� ������������   ����
void __fastcall TForm3::N46Click(TObject *Sender)
{
   for (int i = 1; i < StringGrid1->RowCount; i++) { // �������� � 1, ����� ���������� ��������� �������
		for (int j = i + 1; j < StringGrid1->RowCount; j++) {
			if (StringGrid1->Cells[4][j].CompareIC(StringGrid1->Cells[4][i]) < 0) {
				// ������ ������� ������, ���� �������� � ��������� ������ ������ �������� � �������
				for (int k = 1; k < StringGrid1->ColCount; k++) {
					UnicodeString temp = StringGrid1->Cells[k][i];
					StringGrid1->Cells[k][i] = StringGrid1->Cells[k][j];
					StringGrid1->Cells[k][j] = temp;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
 //�� ������������ ����
void __fastcall TForm3::N47Click(TObject *Sender)
{
  for (int i = 1; i < StringGrid1->RowCount; i++) { // �������� � 1, ����� ���������� ��������� �������
		for (int j = i + 1; j < StringGrid1->RowCount; j++) {
			if (StringGrid1->Cells[4][j].CompareIC(StringGrid1->Cells[4][i]) > 0) {
				// ������ ������� ������, ���� �������� � ��������� ������ ������ �������� � �������
				for (int k = 1; k < StringGrid1->ColCount; k++) {
					UnicodeString temp = StringGrid1->Cells[k][i];
					StringGrid1->Cells[k][i] = StringGrid1->Cells[k][j];
					StringGrid1->Cells[k][j] = temp;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
//�� ��������� ����
void __fastcall TForm3::N49Click(TObject *Sender)
{
   for (int i = 1; i < StringGrid1->RowCount; i++) { // �������� � 1, ����� ���������� ��������� �������
		for (int j = i + 1; j < StringGrid1->RowCount; j++) {
			if (StringGrid1->Cells[5][j].CompareIC(StringGrid1->Cells[5][i]) < 0) {
				// ������ ������� ������, ���� �������� � ��������� ������ ������ �������� � �������
				for (int k = 1; k < StringGrid1->ColCount; k++) {
					UnicodeString temp = StringGrid1->Cells[k][i];
					StringGrid1->Cells[k][i] = StringGrid1->Cells[k][j];
					StringGrid1->Cells[k][j] = temp;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
 //�� ��������� ����
void __fastcall TForm3::N50Click(TObject *Sender)
{
           for (int i = 1; i < StringGrid1->RowCount; i++) { // �������� � 1, ����� ���������� ��������� �������
		for (int j = i + 1; j < StringGrid1->RowCount; j++) {
			if (StringGrid1->Cells[5][j].CompareIC(StringGrid1->Cells[5][i]) > 0) {
				// ������ ������� ������, ���� �������� � ��������� ������ ������ �������� � �������
				for (int k = 1; k < StringGrid1->ColCount; k++) {
					UnicodeString temp = StringGrid1->Cells[k][i];
					StringGrid1->Cells[k][i] = StringGrid1->Cells[k][j];
					StringGrid1->Cells[k][j] = temp;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

 //�� ����� ����
void __fastcall TForm3::N52Click(TObject *Sender)
{
   for (int i = 1; i < StringGrid1->RowCount; i++) { // �������� � 1, ����� ���������� ��������� �������
		for (int j = i + 1; j < StringGrid1->RowCount; j++) {
			if (StringGrid1->Cells[6][j].CompareIC(StringGrid1->Cells[6][i]) < 0) {
				// ������ ������� ������, ���� �������� � ��������� ������ ������ �������� � �������
				for (int k = 1; k < StringGrid1->ColCount; k++) {
					UnicodeString temp = StringGrid1->Cells[k][i];
					StringGrid1->Cells[k][i] = StringGrid1->Cells[k][j];
					StringGrid1->Cells[k][j] = temp;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
 //�� ����� ����
void __fastcall TForm3::N53Click(TObject *Sender)
{
   for (int i = 1; i < StringGrid1->RowCount; i++) { // �������� � 1, ����� ���������� ��������� �������
		for (int j = i + 1; j < StringGrid1->RowCount; j++) {
			if (StringGrid1->Cells[6][j].CompareIC(StringGrid1->Cells[6][i]) > 0) {
				// ������ ������� ������, ���� �������� � ��������� ������ ������ �������� � �������
				for (int k = 1; k < StringGrid1->ColCount; k++) {
					UnicodeString temp = StringGrid1->Cells[k][i];
					StringGrid1->Cells[k][i] = StringGrid1->Cells[k][j];
					StringGrid1->Cells[k][j] = temp;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm3::N55Click(TObject *Sender)
{
   for (int i = 1; i < StrToInt(StringGrid1->RowCount); i++) { // �������� � 1, ����� ���������� ��������� �������
		for (int j = i + 1; j < StrToInt(StringGrid1->RowCount); j++) {
			if (StrToInt(StringGrid1->Cells[7][j]) < StrToInt(StringGrid1->Cells[7][i])) {
				// ������ ������� ������, ���� �������� � ��������� ������ ������ �������� � �������
				for (int k = 0; k < StringGrid1->ColCount; k++) {
					UnicodeString temp = StringGrid1->Cells[k][i];
					StringGrid1->Cells[k][i] = StringGrid1->Cells[k][j];
					StringGrid1->Cells[k][j] = temp;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm3::N56Click(TObject *Sender)
{
    for (int i = 1; i < StrToInt(StringGrid1->RowCount); i++) { // �������� � 1, ����� ���������� ��������� �������
		for (int j = i + 1; j < StrToInt(StringGrid1->RowCount); j++) {
			if (StrToInt(StringGrid1->Cells[7][j]) > StrToInt(StringGrid1->Cells[7][i])) {
				// ������ ������� ������, ���� �������� � ��������� ������ ������ �������� � �������
				for (int k = 0; k < StringGrid1->ColCount; k++) {
					UnicodeString temp = StringGrid1->Cells[k][i];
					StringGrid1->Cells[k][i] = StringGrid1->Cells[k][j];
					StringGrid1->Cells[k][j] = temp;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

