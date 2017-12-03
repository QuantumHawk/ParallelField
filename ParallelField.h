//---------------------------------------------------------------------------

#ifndef ParallelFieldH
#define ParallelFieldH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
     TEdit *edColumn;
     TButton *btnCreateMassiv;
     TLabel *Label1;
     TLabel *Label2;
     TLabel *Label3;
     TEdit *edWorkers;
     TStringGrid *sgMassiv;
     TLabel *Label4;
     void __fastcall btnCreateMassivClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
     __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
