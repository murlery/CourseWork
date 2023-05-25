//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
	TStringGrid *StringGrid1;
	TLabel *Label1;
	TMainMenu *MainMenu1;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TMenuItem *N5;
	TMenuItem *N9;
	TMenuItem *N10;
	TMenuItem *N11;
	TMenuItem *N12;
	TMenuItem *N13;
	TMenuItem *N14;
	TMenuItem *N15;
	TMenuItem *N16;
	TMenuItem *N17;
	TMenuItem *N18;
	TMenuItem *N19;
	TMenuItem *N20;
	TMenuItem *N21;
	TStatusBar *StatusBar1;
	TMenuItem *N7;
	TMenuItem *N22;
	TMenuItem *N23;
	TMenuItem *N24;
	TMenuItem *N25;
	TMenuItem *N26;
	TMenuItem *N27;
	TMenuItem *N28;
	TSaveDialog *SaveDialog1;
	TOpenDialog *OpenDialog1;
	TPopupMenu *PopupMenu1;
	TMenuItem *N6;
	TMenuItem *N8;
	TMenuItem *N29;
	TPopupMenu *PopupMenu2;
	TMenuItem *N30;
	TMenuItem *N31;
	TMenuItem *N32;
	TMenuItem *N33;
	TToolBar *ToolBar1;
	TToolButton *ToolButton1;
	TToolButton *ToolButton2;
	TToolButton *ToolButton3;
	TToolButton *ToolButton4;
	TToolButton *ToolButton5;
	TToolButton *ToolButton6;
	TImageList *ImageList1;
	TToolButton *ToolButton7;
	TToolButton *ToolButton8;
	TMenuItem *N37;
	TToolButton *ToolButton9;
	TToolButton *ToolButton10;
	TToolButton *ToolButton11;
	TToolButton *ToolButton12;
	TToolButton *ToolButton13;
	TToolButton *ToolButton14;
	TToolButton *ToolButton15;
	TToolButton *ToolButton16;
	TToolButton *ToolButton17;
	TToolButton *ToolButton18;
	TToolButton *ToolButton19;
	TToolButton *ToolButton20;
	TMenuItem *N34;
	TMenuItem *N35;
	TMenuItem *N36;
	TMenuItem *N38;
	TMenuItem *N39;
	TMenuItem *N40;
	TMenuItem *N41;
	TMenuItem *N42;
	TMenuItem *N43;
	TMenuItem *N44;
	TMenuItem *N45;
	TMenuItem *N46;
	TMenuItem *N47;
	TMenuItem *N48;
	TMenuItem *N49;
	TMenuItem *N50;
	TMenuItem *N51;
	TMenuItem *N52;
	TMenuItem *N53;
	TMenuItem *N54;
	TMenuItem *N55;
	TMenuItem *N56;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall N12Click(TObject *Sender);
	void __fastcall N11Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall N5Click(TObject *Sender);
	void __fastcall N7Click(TObject *Sender);
	void __fastcall N22Click(TObject *Sender);
	void __fastcall N23Click(TObject *Sender);
	void __fastcall N24Click(TObject *Sender);
	void __fastcall N25Click(TObject *Sender);
	void __fastcall N26Click(TObject *Sender);
	void __fastcall N27Click(TObject *Sender);
	void __fastcall N28Click(TObject *Sender);
	//void __fastcall N16Click(TObject *Sender);
	//void __fastcall N17Click(TObject *Sender);
	void __fastcall N21Click(TObject *Sender);
	void __fastcall N20Click(TObject *Sender);
	void __fastcall N19Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);

	void __fastcall N10Click(TObject *Sender);

	void __fastcall Edit2KeyPress(TObject *Sender, System::WideChar &Key);


	void __fastcall StringGrid1SelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
   //	void __fastcall N13Click(TObject *Sender);
	void __fastcall N34Click(TObject *Sender);
    	void __fastcall N35Click(TObject *Sender);
	void __fastcall N36Click(TObject *Sender);
	void __fastcall N37Click(TObject *Sender);


	void __fastcall N40Click(TObject *Sender);
	void __fastcall N38Click(TObject *Sender);
	void __fastcall N41Click(TObject *Sender);
	void __fastcall N43Click(TObject *Sender);
	void __fastcall N44Click(TObject *Sender);
	void __fastcall N46Click(TObject *Sender);
	void __fastcall N47Click(TObject *Sender);
	void __fastcall N49Click(TObject *Sender);
	void __fastcall N50Click(TObject *Sender);
	void __fastcall N52Click(TObject *Sender);
	void __fastcall N53Click(TObject *Sender);
	void __fastcall N55Click(TObject *Sender);
	void __fastcall N56Click(TObject *Sender);














private:	// User declarations

	bool dataSaved;

public:		// User declarations
	__fastcall TForm3(TComponent* Owner);
	AnsiString currentFileName;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
