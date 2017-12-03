//---------------------------------------------------------------------------

#ifndef ParallelH
#define ParallelH
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
     TLabel *Label1;
     TEdit *edColumn;
     TButton *btnCreateMassiv;
     TStringGrid *sgMassiv;
     TButton *btnFill;
     TLabel *Label3;
     TEdit *edWorkers;
     TButton *btnParallel;
     TButton *btnCreateWorker;
     TLabel *Label2;
     void __fastcall btnCreateMassivClick(TObject *Sender);
     void __fastcall FormCreate(TObject *Sender);
     void __fastcall btnFillClick(TObject *Sender);
     void __fastcall btnCreateWorkerClick(TObject *Sender);
     void __fastcall btnParallelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
     __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
