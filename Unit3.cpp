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
TStringGrid *TempGrid;  // Глобальная переменная в вашем классе TForm3

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
			ShowMessage("Ошибка при сохранении файла");
		} else {
			Product product;
			for (int i = 1; i < StringGrid1->RowCount; i++) { // Начинаем с 1, чтобы пропустить заголовок
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
			ShowMessage("Файл успешно сохранен");
		}
	} else {
		ShowMessage("Ошибка: нет открытого файла для сохранения");
		StatusBar1->Panels->Items[0]->Text = "Ошибка сохранения";
	}
}


//---------------------------------------------------------------------------
void __fastcall TForm3::FormCreate(TObject *Sender)
{
		StringGrid1->Cells[0][0]="№";
		StringGrid1->Cells[1][0]="Название изделия";
		StringGrid1->Cells[2][0]="Цена";
		StringGrid1->Cells[3][0]="Вес изделия";
		StringGrid1->Cells[4][0]="Изготовитель";
		StringGrid1->Cells[5][0]="Основоной материал";
		StringGrid1->Cells[6][0]="Драгоценный камень";
		StringGrid1->Cells[7][0]="Вес камня в каратах";

		Form5=new TForm5 (this);
		Form5->ShowModal();
		Form5->Free();
}
//---------------------------------------------------------------------------

//удаление

void __fastcall TForm3::N12Click(TObject *Sender)
{
	int row = StringGrid1->Row; // получаем индекс текущей строки
	if (row >= 1 && row < StringGrid1->RowCount) // проверяем, что строка действительно существует
	{
		if (MessageDlg("Вы уверены, что хотите удалить строку под номером: " +StringGrid1->Cells[0][row]+"\nНазвание изделия: "+StringGrid1->Cells[1][row]+"\nЦена изделия: "+StringGrid1->Cells[2][row]+"\nВес изделия: "+StringGrid1->Cells[3][row]+"\nИзготовитель: "+StringGrid1->Cells[4][row]+"\nОсновной материал: "+StringGrid1->Cells[5][row]+"\nДрагоценный камень: "+StringGrid1->Cells[6][row]+"\nВес камня: "+StringGrid1->Cells[7][row], mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
		{
			for (int i = row; i < StringGrid1->RowCount - 1; i++)
			{
				for (int j = 0; j < StringGrid1->ColCount; j++)
				{
					StringGrid1->Cells[j][i] = StringGrid1->Cells[j][i + 1]; // сдвигаем все строки вверх на одну позицию
				}
			}
			StringGrid1->RowCount--; // уменьшаем количество строк на 1

			// Обновляем номера строк
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
  StatusBar1->Panels->Items[0]->Text = "Число элементов: " + IntToStr(rCount);
}

//---------------------------------------------------------------------------



 //редактирование
void __fastcall TForm3::N11Click(TObject *Sender)
{
	if (StringGrid1->Row > 0) { // Если выбрана строка
		// Заполняем поля на Form2 данными из выбранной строки
		Form2->Edit1->Text = StringGrid1->Cells[1][StringGrid1->Row];
		Form2->Edit2->Text = StringGrid1->Cells[2][StringGrid1->Row];
		Form2->Edit3->Text = StringGrid1->Cells[3][StringGrid1->Row];
		Form2->Edit4->Text = StringGrid1->Cells[4][StringGrid1->Row];
		Form2->Edit5->Text = StringGrid1->Cells[5][StringGrid1->Row];
		Form2->Edit6->Text = StringGrid1->Cells[6][StringGrid1->Row];
		Form2->Edit7->Text = StringGrid1->Cells[7][StringGrid1->Row];
		Form2->Button1->Caption = "Редактировать"; // Переименовываем Button1 на "Редактировать"
		Form2->ShowModal(); // Открываем Form2
	} else {
		ShowMessage("Выберите строку для редактирования");
	}
    int rCount;
  for (int i = 0; i < StringGrid1->RowCount; i++)
  {
      rCount = i;
  }
  StatusBar1->Panels->Items[0]->Text = "Число элементов: " + IntToStr(rCount);
}
//---------------------------------------------------------------------------


//---СОЗДАНИЕ Бинарного файла
void __fastcall TForm3::N2Click(TObject *Sender)
{
	SaveDialog1->Filter = "Binary files (*.bin)|*.bin";
	SaveDialog1->DefaultExt = "bin";

if (SaveDialog1->Execute()) {
	std::ofstream outFile(SaveDialog1->FileName.c_str(), std::ios::out | std::ios::binary);
	if (!outFile) {
		ShowMessage("Ошибка при создании файла");
	} else {
		ShowMessage("Файл успешно создан");
		outFile.close();
		currentFileName = SaveDialog1->FileName;  // установите currentFileName здесь
	}
}
}
//---------------------------------------------------------------------------

//---ОТКРЫТИЕ Бинарного файла
void __fastcall TForm3::N3Click(TObject *Sender)
{
	OpenDialog1->Filter = "Binary files (*.bin)|*.bin";
	OpenDialog1->DefaultExt = "bin";
	if (OpenDialog1->Execute()) {
		std::ifstream inFile(OpenDialog1->FileName.c_str(), std::ios::in | std::ios::binary);
		if (!inFile) {
			ShowMessage("Ошибка при открытии файла");
		} else {
			currentFileName = OpenDialog1->FileName; // Обновляем currentFileName

			Product product;
			StringGrid1->RowCount = 2; // Заголовок и первая строка данных
			while (inFile.read((char*)&product, sizeof(Product))) {
				StringGrid1->Cells[0][StringGrid1->RowCount - 1] = product.id;
				StringGrid1->Cells[1][StringGrid1->RowCount - 1] = product.name;
				StringGrid1->Cells[2][StringGrid1->RowCount - 1] = product.price;
				StringGrid1->Cells[3][StringGrid1->RowCount - 1] = product.weight;
				StringGrid1->Cells[4][StringGrid1->RowCount - 1] = product.manufacturer;
				StringGrid1->Cells[5][StringGrid1->RowCount - 1] = product.material;
				StringGrid1->Cells[6][StringGrid1->RowCount - 1] = product.gem;
				StringGrid1->Cells[7][StringGrid1->RowCount - 1] = product.gemWeight;
				StringGrid1->RowCount++; // Добавляем строку для следующего продукта
			}
			StringGrid1->RowCount--; // Удаляем лишнюю строку в конце
			inFile.close();
		}
	}
}



//---------------------------------------------------------------------------

//Сохранение
void __fastcall TForm3::N5Click(TObject *Sender)
{
SaveDialog1->Filter = "Binary files (*.bin)|*.bin";
	SaveDialog1->DefaultExt = "bin";
	if (SaveDialog1->Execute()) {
		currentFileName = SaveDialog1->FileName;
		std::ofstream outFile(currentFileName.c_str(), std::ios::out | std::ios::binary);
		if (!outFile) {
			ShowMessage("Ошибка");
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
			ShowMessage("Файл сохранен");
		}
	}

}

//---------------------------------------------------------------------------
//ПОИСК по номеру изделия
void __fastcall TForm3::N7Click(TObject *Sender)
{
  UnicodeString searchText = InputBox("Поиск", "Введите номер изделия", "");
  int searchType = MessageDlg("Поиск по полному совпадению?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel, 0);

  // Полное совпадение
  if (searchType == mrYes) {
	for (int i = 1; i < StringGrid1->RowCount; i++) {
	  if (StringGrid1->Cells[0][i] == searchText) {
		StringGrid1->Row = i; // выделить найденную строку
		ShowMessage("Найдено изделие по номеру\nHомер изделия: " + searchText +"\nНазвание изделия: "+StringGrid1->Cells[1][i]+"\nЦена изделия: "+StringGrid1->Cells[2][i]+"\nВес изделия: "+StringGrid1->Cells[3][i]+"\nИзготовитель: "+StringGrid1->Cells[4][i]+"\nОсновной материал: "+StringGrid1->Cells[5][i]+"\nДрагоценный камень: "+StringGrid1->Cells[6][i]+"\nВес камня: "+StringGrid1->Cells[7][i]);
		return;
	  }
	}
  }
  // Начало строки
  else if (searchType == mrNo) {
	for (int i = 1; i < StringGrid1->RowCount; i++) {
	  if (AnsiStartsText(searchText, StringGrid1->Cells[0][i]))
	   {
		StringGrid1->Row = i; // выделить найденную строку
		ShowMessage("Найден номер изделия: " + StringGrid1->Cells[0][i]+"\nНазвание изделия: "+StringGrid1->Cells[1][i]+"\nЦена изделия: "+StringGrid1->Cells[2][i]+"\nВес изделия: "+StringGrid1->Cells[3][i]+"\nИзготовитель: "+StringGrid1->Cells[4][i]+"\nОсновной материал: "+StringGrid1->Cells[5][i]+"\nДрагоценный камень: "+StringGrid1->Cells[6][i]+"\nВес камня: "+StringGrid1->Cells[7][i]);
		return;
	  }
	}
  }
  // Отмена
  else {
	return;
  }

  ShowMessage("Изделие по номеру не найдено");
}




//---------------------------------------------------------------------------

//ПОИСК по названию изделия
void __fastcall TForm3::N22Click(TObject *Sender)
{
   UnicodeString searchText = InputBox("Поиск", "Введите название изделия", "");
   int searchType = MessageDlg("Поиск по полному совпадению?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel, 0);
   // Полное совпадение
  if (searchType == mrYes) {
	for (int i = 1; i < StringGrid1->RowCount; i++) {
	  if (StringGrid1->Cells[1][i] == searchText) {
		StringGrid1->Row = i; // выделить найденную строку
		ShowMessage("Найдено изделие по названию\nНомер изделия: " + searchText +"\nНазвание изделия: "+StringGrid1->Cells[1][i]+"\nЦена изделия: "+StringGrid1->Cells[2][i]+"\nВес изделия: "+StringGrid1->Cells[3][i]+"\nИзготовитель: "+StringGrid1->Cells[4][i]+"\nОсновной материал: "+StringGrid1->Cells[5][i]+"\nДрагоценный камень: "+StringGrid1->Cells[6][i]+"\nВес камня: "+StringGrid1->Cells[7][i]);
		return;
	  }
	}
  }
  // Начало строки
  else if (searchType == mrNo) {
	for (int i = 1; i < StringGrid1->RowCount; i++) {
	  if (AnsiStartsText(searchText, StringGrid1->Cells[1][i]))
	   {
		StringGrid1->Row = i; // выделить найденную строку
		ShowMessage("Найдено изделие по названию\nНомер изделия: " +StringGrid1->Cells[0][i]  +"\nНазвание изделия: "+StringGrid1->Cells[1][i]+"\nЦена изделия: "+StringGrid1->Cells[2][i]+"\nВес изделия: "+StringGrid1->Cells[3][i]+"\nИзготовитель: "+StringGrid1->Cells[4][i]+"\nОсновной материал: "+StringGrid1->Cells[5][i]+"\nДрагоценный камень: "+StringGrid1->Cells[6][i]+"\nВес камня: "+StringGrid1->Cells[7][i]);
		return;
	  }
	}
  }
  // Отмена
  else {
	return;
  }
	ShowMessage("Изделие по названию не найдено");

}
//---------------------------------------------------------------------------
//ПОИСК по цене изделия
void __fastcall TForm3::N23Click(TObject *Sender)
{
   UnicodeString searchText = InputBox("Поиск", "Введите цену изделия", "");
   int searchType = MessageDlg("Поиск по полному совпадению?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel, 0);
   // Полное совпадение
  if (searchType == mrYes) {
	for (int i = 1; i < StringGrid1->RowCount; i++) {
	  if (StringGrid1->Cells[2][i] == searchText) {
		StringGrid1->Row = i; // выделить найденную строку
		ShowMessage("Найдено изделие по цене\nНомер изделия: " + searchText +"\nНазвание изделия: "+StringGrid1->Cells[1][i]+"\nЦена изделия: "+StringGrid1->Cells[2][i]+"\nВес изделия: "+StringGrid1->Cells[3][i]+"\nИзготовитель: "+StringGrid1->Cells[4][i]+"\nОсновной материал: "+StringGrid1->Cells[5][i]+"\nДрагоценный камень: "+StringGrid1->Cells[6][i]+"\nВес камня: "+StringGrid1->Cells[7][i]);
		return;
	  }
	}
  }
  // Начало строки
  else if (searchType == mrNo) {
	for (int i = 1; i < StringGrid1->RowCount; i++) {
	  if (AnsiStartsText(searchText, StringGrid1->Cells[2][i]))
	   {
		StringGrid1->Row = i; // выделить найденную строку
		ShowMessage("Найдено изделие по цене\nНомер изделия: " +StringGrid1->Cells[0][i]  +"\nНазвание изделия: "+StringGrid1->Cells[1][i]+"\nЦена изделия: "+StringGrid1->Cells[2][i]+"\nВес изделия: "+StringGrid1->Cells[3][i]+"\nИзготовитель: "+StringGrid1->Cells[4][i]+"\nОсновной материал: "+StringGrid1->Cells[5][i]+"\nДрагоценный камень: "+StringGrid1->Cells[6][i]+"\nВес камня: "+StringGrid1->Cells[7][i]);
		return;
	  }
	}
  }
  // Отмена
  else {
	return;
  }
	ShowMessage("Изделие по цене не найдено");

}
//---------------------------------------------------------------------------
//ПОИСК по весу изделия
void __fastcall TForm3::N24Click(TObject *Sender)
{
   UnicodeString searchText = InputBox("Поиск", "Введите вес изделия", "");
   int searchType = MessageDlg("Поиск по полному совпадению?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel, 0);
   // Полное совпадение
  if (searchType == mrYes) {
	for (int i = 1; i < StringGrid1->RowCount; i++) {
	  if (StringGrid1->Cells[3][i] == searchText) {
		StringGrid1->Row = i; // выделить найденную строку
		ShowMessage("Найдено изделие по весу\nНомер изделия: " + searchText +"\nНазвание изделия: "+StringGrid1->Cells[1][i]+"\nЦена изделия: "+StringGrid1->Cells[2][i]+"\nВес изделия: "+StringGrid1->Cells[3][i]+"\nИзготовитель: "+StringGrid1->Cells[4][i]+"\nОсновной материал: "+StringGrid1->Cells[5][i]+"\nДрагоценный камень: "+StringGrid1->Cells[6][i]+"\nВес камня: "+StringGrid1->Cells[7][i]);
		return;
	  }
	}
  }
  // Начало строки
  else if (searchType == mrNo) {
	for (int i = 1; i < StringGrid1->RowCount; i++) {
	  if (AnsiStartsText(searchText, StringGrid1->Cells[3][i]))
	   {
		StringGrid1->Row = i; // выделить найденную строку
		ShowMessage("Найдено изделие по весу\nНомер изделия: " +StringGrid1->Cells[0][i]  +"\nНазвание изделия: "+StringGrid1->Cells[1][i]+"\nЦена изделия: "+StringGrid1->Cells[2][i]+"\nВес изделия: "+StringGrid1->Cells[3][i]+"\nИзготовитель: "+StringGrid1->Cells[4][i]+"\nОсновной материал: "+StringGrid1->Cells[5][i]+"\nДрагоценный камень: "+StringGrid1->Cells[6][i]+"\nВес камня: "+StringGrid1->Cells[7][i]);
		return;
	  }
	}
  }
  // Отмена
  else {
	return;
  }
	ShowMessage("Изделие по весу не найдено");

}
//---------------------------------------------------------------------------
//ПОИСК по изготовителю изделия
void __fastcall TForm3::N25Click(TObject *Sender)
{
	 UnicodeString searchText = InputBox("Поиск", "Введите изготовителя изделия", "");
   int searchType = MessageDlg("Поиск по полному совпадению?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel, 0);
   // Полное совпадение
  if (searchType == mrYes) {
	for (int i = 1; i < StringGrid1->RowCount; i++) {
	  if (StringGrid1->Cells[4][i] == searchText) {
		StringGrid1->Row = i; // выделить найденную строку
		ShowMessage("Найдено изделие по изготовителю\nНомер изделия: " + searchText +"\nНазвание изделия: "+StringGrid1->Cells[1][i]+"\nЦена изделия: "+StringGrid1->Cells[2][i]+"\nВес изделия: "+StringGrid1->Cells[3][i]+"\nИзготовитель: "+StringGrid1->Cells[4][i]+"\nОсновной материал: "+StringGrid1->Cells[5][i]+"\nДрагоценный камень: "+StringGrid1->Cells[6][i]+"\nВес камня: "+StringGrid1->Cells[7][i]);
		return;
	  }
	}
  }
  // Начало строки
  else if (searchType == mrNo) {
	for (int i = 1; i < StringGrid1->RowCount; i++) {
	  if (AnsiStartsText(searchText, StringGrid1->Cells[4][i]))
	   {
		StringGrid1->Row = i; // выделить найденную строку
		ShowMessage("Найдено изделие по изготовителю\nНомер изделия: " +StringGrid1->Cells[0][i]  +"\nНазвание изделия: "+StringGrid1->Cells[1][i]+"\nЦена изделия: "+StringGrid1->Cells[2][i]+"\nВес изделия: "+StringGrid1->Cells[3][i]+"\nИзготовитель: "+StringGrid1->Cells[4][i]+"\nОсновной материал: "+StringGrid1->Cells[5][i]+"\nДрагоценный камень: "+StringGrid1->Cells[6][i]+"\nВес камня: "+StringGrid1->Cells[7][i]);
		return;
	  }
	}
  }
  // Отмена
  else {
	return;
  }
	ShowMessage("Изделие по изготовителю не найдено");

}
//---------------------------------------------------------------------------
 //ПОИСК по основному материалу изделия
void __fastcall TForm3::N26Click(TObject *Sender)
{
	  UnicodeString searchText = InputBox("Поиск", "Введите основной материал изделия", "");
   int searchType = MessageDlg("Поиск по полному совпадению?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel, 0);
   // Полное совпадение
  if (searchType == mrYes) {
	for (int i = 1; i < StringGrid1->RowCount; i++) {
	  if (StringGrid1->Cells[5][i] == searchText) {
		StringGrid1->Row = i; // выделить найденную строку
		ShowMessage("Найдено изделие по основному материалу\nНомер изделия: " + searchText +"\nНазвание изделия: "+StringGrid1->Cells[1][i]+"\nЦена изделия: "+StringGrid1->Cells[2][i]+"\nВес изделия: "+StringGrid1->Cells[3][i]+"\nИзготовитель: "+StringGrid1->Cells[4][i]+"\nОсновной материал: "+StringGrid1->Cells[5][i]+"\nДрагоценный камень: "+StringGrid1->Cells[6][i]+"\nВес камня: "+StringGrid1->Cells[7][i]);
		return;
	  }
	}
  }
  // Начало строки
  else if (searchType == mrNo) {
	for (int i = 1; i < StringGrid1->RowCount; i++) {
	  if (AnsiStartsText(searchText, StringGrid1->Cells[5][i]))
	   {
		StringGrid1->Row = i; // выделить найденную строку
		ShowMessage("Найдено изделие по основному материалу\nНомер изделия: " +StringGrid1->Cells[0][i]  +"\nНазвание изделия: "+StringGrid1->Cells[1][i]+"\nЦена изделия: "+StringGrid1->Cells[2][i]+"\nВес изделия: "+StringGrid1->Cells[3][i]+"\nИзготовитель: "+StringGrid1->Cells[4][i]+"\nОсновной материал: "+StringGrid1->Cells[5][i]+"\nДрагоценный камень: "+StringGrid1->Cells[6][i]+"\nВес камня: "+StringGrid1->Cells[7][i]);
		return;
	  }
	}
  }
  // Отмена
  else {
	return;
  }
	ShowMessage("Изделие по основному материалу не найдено");

}
//---------------------------------------------------------------------------
//ПОИСК по драгоценному камню изделия
void __fastcall TForm3::N27Click(TObject *Sender)
{
	 UnicodeString searchText = InputBox("Поиск", "Введите драгоценный камень изделия", "");
   int searchType = MessageDlg("Поиск по полному совпадению?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel, 0);
   // Полное совпадение
  if (searchType == mrYes) {
	for (int i = 1; i < StringGrid1->RowCount; i++) {
	  if (StringGrid1->Cells[6][i] == searchText) {
		StringGrid1->Row = i; // выделить найденную строку
		ShowMessage("Найдено изделие по драгоценному камню\nНомер изделия: " + searchText +"\nНазвание изделия: "+StringGrid1->Cells[1][i]+"\nЦена изделия: "+StringGrid1->Cells[2][i]+"\nВес изделия: "+StringGrid1->Cells[3][i]+"\nИзготовитель: "+StringGrid1->Cells[4][i]+"\nОсновной материал: "+StringGrid1->Cells[5][i]+"\nДрагоценный камень: "+StringGrid1->Cells[6][i]+"\nВес камня: "+StringGrid1->Cells[7][i]);
		return;
	  }
	}
  }
  // Начало строки
  else if (searchType == mrNo) {
	for (int i = 1; i < StringGrid1->RowCount; i++) {
	  if (AnsiStartsText(searchText, StringGrid1->Cells[6][i]))
	   {
		StringGrid1->Row = i; // выделить найденную строку
		ShowMessage("Найдено изделие по драгоценному камню\nНомер изделия: " +StringGrid1->Cells[0][i]  +"\nНазвание изделия: "+StringGrid1->Cells[1][i]+"\nЦена изделия: "+StringGrid1->Cells[2][i]+"\nВес изделия: "+StringGrid1->Cells[3][i]+"\nИзготовитель: "+StringGrid1->Cells[4][i]+"\nОсновной материал: "+StringGrid1->Cells[5][i]+"\nДрагоценный камень: "+StringGrid1->Cells[6][i]+"\nВес камня: "+StringGrid1->Cells[7][i]);
		return;
	  }
	}
  }
  // Отмена
  else {
	return;
  }
	ShowMessage("Изделие по драгоценному камню не найдено");

}
//---------------------------------------------------------------------------
//ПОИСК по весу камня
void __fastcall TForm3::N28Click(TObject *Sender)
{
	 UnicodeString searchText = InputBox("Поиск", "Введите вес камня изделия", "");
   int searchType = MessageDlg("Поиск по полному совпадению?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel, 0);
   // Полное совпадение
  if (searchType == mrYes) {
	for (int i = 1; i < StringGrid1->RowCount; i++) {
	  if (StringGrid1->Cells[7][i] == searchText) {
		StringGrid1->Row = i; // выделить найденную строку
		ShowMessage("Найдено изделие по весу камня\nНомер изделия: " + searchText +"\nНазвание изделия: "+StringGrid1->Cells[1][i]+"\nЦена изделия: "+StringGrid1->Cells[2][i]+"\nВес изделия: "+StringGrid1->Cells[3][i]+"\nИзготовитель: "+StringGrid1->Cells[4][i]+"\nОсновной материал: "+StringGrid1->Cells[5][i]+"\nДрагоценный камень: "+StringGrid1->Cells[6][i]+"\nВес камня: "+StringGrid1->Cells[7][i]);
		return;
	  }
	}
  }
  // Начало строки
  else if (searchType == mrNo) {
	for (int i = 1; i < StringGrid1->RowCount; i++) {
	  if (AnsiStartsText(searchText, StringGrid1->Cells[7][i]))
	   {
		StringGrid1->Row = i; // выделить найденную строку
		ShowMessage("Найдено изделие по весу камня\nНомер изделия: " +StringGrid1->Cells[0][i]  +"\nНазвание изделия: "+StringGrid1->Cells[1][i]+"\nЦена изделия: "+StringGrid1->Cells[2][i]+"\nВес изделия: "+StringGrid1->Cells[3][i]+"\nИзготовитель: "+StringGrid1->Cells[4][i]+"\nОсновной материал: "+StringGrid1->Cells[5][i]+"\nДрагоценный камень: "+StringGrid1->Cells[6][i]+"\nВес камня: "+StringGrid1->Cells[7][i]);
		return;
	  }
	}
  }
  // Отмена
  else {
	return;
  }
	ShowMessage("Изделие по весу камня не найдено");

}
//---------------------------------------------------------------------------





//---------------------------------------------------------------------------

void __fastcall TForm3::N21Click(TObject *Sender)
{
  ShowMessage("Версия программного продукта: 1.0.0 \nДата внесения последних изменений: 16.05.2023 \nАвтор: Адаховская Валерия");
}
//---------------------------------------------------------------------------

void __fastcall TForm3::N20Click(TObject *Sender)
{

	 ShowMessage("Описание работы с программой Ювелирный магазин. \n1. Описание: Эта программа предназначена для управления записями о ювелирных изделиях в магазине. С помощью нее вы можете добавлять, редактировать и удалять информацию о изделиях, а также проводить поиск и сортировку данных. \n2. Установка и запуск: Программа не требует установки. Просто запустите исполняемый файл для начала работы. \n3. Функции и возможности: \nФайл:\n- Создать: создает новый файл для ввода данных о зверях и птицах.\n- Открыть: позволяет выбрать и открыть существующий файл с данными.\n- Сохранить: сохраняет текущие данные в открытый файл.\n- Сохранить как: позволяет сохранить текущие данные в новый файл.\nПравка:\n- Добавление записи.\n- Редактирование записиь\n- Удаление записи.\nОбработка:\n-Поиск.\n- Сортировка.");

}

//---------------------------------------------------------------------------


void __fastcall TForm3::N19Click(TObject *Sender)
{
	ShowMessage("В ювелирном магазине следующие сведения заносятся в файл: название изделия, цена, вес изделия, изготовитель, основной материал, драгоценный камень, вес камня (в каратах). Написать программу, формирующую список изделий отсортированный в порядке возрастания цены. Выдать список изделий, вес камня в которых превышает заданный.");
}

//---------------------------------------------------------------------------

void __fastcall TForm3::FormClose(TObject *Sender, TCloseAction &Action)
{
	// Проверяем, сохранены ли данные
	if (!dataSaved) {
		if (MessageBox(NULL, L"Вы не сохранили ваши данные. Вы хотите сохранить их перед выходом?", L"Предупреждение", MB_YESNO | MB_ICONQUESTION) == IDYES) {
			N4Click(NULL);
		}
	}
}

//---------------------------------------------------------------------------


void __fastcall TForm3::N10Click(TObject *Sender)
{
	   Form2->Button1->Caption = "Добавить"; // Переименовываем Button1 на "Редактировать"
		Form2->ShowModal(); // Открываем Form2
        int rCount;
  for (int i = 0; i < StringGrid1->RowCount; i++)
  {
      rCount = i;
  }
  StatusBar1->Panels->Items[0]->Text = "Число элементов: " + IntToStr(rCount);
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------

void __fastcall TForm3::Edit2KeyPress(TObject *Sender, System::WideChar &Key)
{
  if (!std::isdigit(Key) && Key != VK_BACK && Key!=VK_RETURN)// Если это не цифра и не клавиша Backspace
	{   ShowMessage("Введите только цифры без пробелов");
		Key = 0; // Отменить ввод
	}
}
//---------------------------------------------------------------------------


//Сортировка по возрастанию номера---------------------------------------------------------------------------

void __fastcall TForm3::N34Click(TObject *Sender)
{
	 for (int i = 1; i < StrToInt(StringGrid1->RowCount); i++) { // начинаем с 1, чтобы пропустить заголовок таблицы
		for (int j = i + 1; j < StrToInt(StringGrid1->RowCount); j++) {
			if (StrToInt(StringGrid1->Cells[0][j]) < StrToInt(StringGrid1->Cells[0][i])) {
				// меняем местами строки, если значение в следующей строке меньше значения в текущей
				for (int k = 0; k < StringGrid1->ColCount; k++) {
					UnicodeString temp = StringGrid1->Cells[k][i];
					StringGrid1->Cells[k][i] = StringGrid1->Cells[k][j];
					StringGrid1->Cells[k][j] = temp;
				}
			}
		}
	}
}
 //Сорт номер убывание
void __fastcall TForm3::N35Click(TObject *Sender)
{
	 for (int i = 1; i < StrToInt(StringGrid1->RowCount); i++) { // начинаем с 1, чтобы пропустить заголовок таблицы
		for (int j = i + 1; j < StrToInt(StringGrid1->RowCount); j++) {
			if (StrToInt(StringGrid1->Cells[0][j]) > StrToInt(StringGrid1->Cells[0][i])) {
				// меняем местами строки, если значение в следующей строке меньше значения в текущей
				for (int k = 0; k < StringGrid1->ColCount; k++) {
					UnicodeString temp = StringGrid1->Cells[k][i];
					StringGrid1->Cells[k][i] = StringGrid1->Cells[k][j];
					StringGrid1->Cells[k][j] = temp;
				}
			}
		}
	}
}

 //Сорт название по возр
void __fastcall TForm3::N36Click(TObject *Sender)
{
   for (int i = 1; i < StringGrid1->RowCount; i++) { // начинаем с 1, чтобы пропустить заголовок таблицы
		for (int j = i + 1; j < StringGrid1->RowCount; j++) {
			if (StringGrid1->Cells[1][j].CompareIC(StringGrid1->Cells[1][i]) < 0) {
				// меняем местами строки, если значение в следующей строке меньше значения в текущей
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

//Сорт по цене возр
void __fastcall TForm3::N40Click(TObject *Sender)
{
  for (int i = 1; i < StrToInt(StringGrid1->RowCount); i++) { // начинаем с 1, чтобы пропустить заголовок таблицы
		for (int j = i + 1; j < StrToInt(StringGrid1->RowCount); j++) {
			if (StrToInt(StringGrid1->Cells[2][j]) < StrToInt(StringGrid1->Cells[2][i])) {
				// меняем местами строки, если значение в следующей строке меньше значения в текущей
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
 //Сорт название по убыванию
void __fastcall TForm3::N38Click(TObject *Sender)
{
  for (int i = 1; i < StringGrid1->RowCount; i++) { // начинаем с 1, чтобы пропустить заголовок таблицы
		for (int j = i + 1; j < StringGrid1->RowCount; j++) {
			if (StringGrid1->Cells[1][j].CompareIC(StringGrid1->Cells[1][i]) > 0) {
				// меняем местами строки, если значение в следующей строке меньше значения в текущей
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
   StatusBar1->Panels->Items[2]->Text = "Выделенная строка: " + IntToStr(ARow);
   StatusBar1->Panels->Items[3]->Text = "Столбец: " + IntToStr(ACol);
}
//по цене убыв
void __fastcall TForm3::N41Click(TObject *Sender)
{
    for (int i = 1; i < StrToInt(StringGrid1->RowCount); i++) { // начинаем с 1, чтобы пропустить заголовок таблицы
		for (int j = i + 1; j < StrToInt(StringGrid1->RowCount); j++) {
			if (StrToInt(StringGrid1->Cells[2][j]) > StrToInt(StringGrid1->Cells[2][i])) {
				// меняем местами строки, если значение в следующей строке меньше значения в текущей
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
 //по весу возр
void __fastcall TForm3::N43Click(TObject *Sender)
{
   for (int i = 1; i < StrToInt(StringGrid1->RowCount); i++) { // начинаем с 1, чтобы пропустить заголовок таблицы
		for (int j = i + 1; j < StrToInt(StringGrid1->RowCount); j++) {
			if (StrToInt(StringGrid1->Cells[3][j]) < StrToInt(StringGrid1->Cells[3][i])) {
				// меняем местами строки, если значение в следующей строке меньше значения в текущей
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
//по весу убыв
void __fastcall TForm3::N44Click(TObject *Sender)
{
     for (int i = 1; i < StrToInt(StringGrid1->RowCount); i++) { // начинаем с 1, чтобы пропустить заголовок таблицы
		for (int j = i + 1; j < StrToInt(StringGrid1->RowCount); j++) {
			if (StrToInt(StringGrid1->Cells[3][j]) > StrToInt(StringGrid1->Cells[3][i])) {
				// меняем местами строки, если значение в следующей строке меньше значения в текущей
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
 //  по изготовителю   возр
void __fastcall TForm3::N46Click(TObject *Sender)
{
   for (int i = 1; i < StringGrid1->RowCount; i++) { // начинаем с 1, чтобы пропустить заголовок таблицы
		for (int j = i + 1; j < StringGrid1->RowCount; j++) {
			if (StringGrid1->Cells[4][j].CompareIC(StringGrid1->Cells[4][i]) < 0) {
				// меняем местами строки, если значение в следующей строке меньше значения в текущей
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
 //по изготовителю убыв
void __fastcall TForm3::N47Click(TObject *Sender)
{
  for (int i = 1; i < StringGrid1->RowCount; i++) { // начинаем с 1, чтобы пропустить заголовок таблицы
		for (int j = i + 1; j < StringGrid1->RowCount; j++) {
			if (StringGrid1->Cells[4][j].CompareIC(StringGrid1->Cells[4][i]) > 0) {
				// меняем местами строки, если значение в следующей строке меньше значения в текущей
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
//по материалу возр
void __fastcall TForm3::N49Click(TObject *Sender)
{
   for (int i = 1; i < StringGrid1->RowCount; i++) { // начинаем с 1, чтобы пропустить заголовок таблицы
		for (int j = i + 1; j < StringGrid1->RowCount; j++) {
			if (StringGrid1->Cells[5][j].CompareIC(StringGrid1->Cells[5][i]) < 0) {
				// меняем местами строки, если значение в следующей строке меньше значения в текущей
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
 //по материалу убыв
void __fastcall TForm3::N50Click(TObject *Sender)
{
           for (int i = 1; i < StringGrid1->RowCount; i++) { // начинаем с 1, чтобы пропустить заголовок таблицы
		for (int j = i + 1; j < StringGrid1->RowCount; j++) {
			if (StringGrid1->Cells[5][j].CompareIC(StringGrid1->Cells[5][i]) > 0) {
				// меняем местами строки, если значение в следующей строке меньше значения в текущей
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

 //по камню возр
void __fastcall TForm3::N52Click(TObject *Sender)
{
   for (int i = 1; i < StringGrid1->RowCount; i++) { // начинаем с 1, чтобы пропустить заголовок таблицы
		for (int j = i + 1; j < StringGrid1->RowCount; j++) {
			if (StringGrid1->Cells[6][j].CompareIC(StringGrid1->Cells[6][i]) < 0) {
				// меняем местами строки, если значение в следующей строке меньше значения в текущей
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
 //по камню убыв
void __fastcall TForm3::N53Click(TObject *Sender)
{
   for (int i = 1; i < StringGrid1->RowCount; i++) { // начинаем с 1, чтобы пропустить заголовок таблицы
		for (int j = i + 1; j < StringGrid1->RowCount; j++) {
			if (StringGrid1->Cells[6][j].CompareIC(StringGrid1->Cells[6][i]) > 0) {
				// меняем местами строки, если значение в следующей строке меньше значения в текущей
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
   for (int i = 1; i < StrToInt(StringGrid1->RowCount); i++) { // начинаем с 1, чтобы пропустить заголовок таблицы
		for (int j = i + 1; j < StrToInt(StringGrid1->RowCount); j++) {
			if (StrToInt(StringGrid1->Cells[7][j]) < StrToInt(StringGrid1->Cells[7][i])) {
				// меняем местами строки, если значение в следующей строке меньше значения в текущей
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
    for (int i = 1; i < StrToInt(StringGrid1->RowCount); i++) { // начинаем с 1, чтобы пропустить заголовок таблицы
		for (int j = i + 1; j < StrToInt(StringGrid1->RowCount); j++) {
			if (StrToInt(StringGrid1->Cells[7][j]) > StrToInt(StringGrid1->Cells[7][i])) {
				// меняем местами строки, если значение в следующей строке меньше значения в текущей
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

