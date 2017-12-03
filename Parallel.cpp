//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Parallel.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
     : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnCreateMassivClick(TObject *Sender)
{
     //Очистка всех ячеек
     for (int i=sgMassiv->FixedCols;i<sgMassiv->ColCount; i++)
          sgMassiv->Cols[i]->Clear();

     //подгон размера массива
     AnsiString countColumnStr = edColumn->Text;
     int countColumn = StrToInt(countColumnStr);
     sgMassiv->ColCount = countColumn + 1;

     //подпись столбцов
     for(int i=1; i<(countColumn+1); i++)
     {
          sgMassiv->Cells[i][0] = IntToStr(i) + " столбец";
     }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
     sgMassiv->Cells[0][1] = "A";
     sgMassiv->Cells[0][2] = "В";

}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnFillClick(TObject *Sender)
{
     //добавить проверку, есть ли число в ячейке, иначе будет ошибка

     //автоматическое заполнение массива значениями
     AnsiString countColumnStr = edColumn->Text;
     int countColumn = StrToInt(countColumnStr);
     int A[]={1,3,5,2,4,6,1,7};
     int B[]={2,4,3,1,7,3,6,2};
     if(countColumn < 9)
     {
          for(int i=1; i<countColumn+1; i++)
          {
               sgMassiv->Cells[i][1] = A[i-1];
               sgMassiv->Cells[i][2] = B[i-1];
          }
     }
     else
     {
          ShowMessage("Надо не больше 8 :))");
          edColumn->SetFocus();
     }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnCreateWorkerClick(TObject *Sender)
{
     AnsiString countWorkerStr = edWorkers->Text;
     int countWorker = StrToInt(countWorkerStr);

     for (int i=0; i<countWorker; i++)
        {
        TEdit *edit = new TEdit(this);
        edit->Parent = this;
        edit->Name = "edit"+AnsiString(i+1);
        edit->Height = 21;
        edit->Width = 121;
        edit->Left = 56;
        edit->Top = 280+i*edit->Height;
        //edit->Text = "";
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnParallelClick(TObject *Sender)
{
     AnsiString countWorkerStr = edWorkers->Text;
     int countWorker = StrToInt(countWorkerStr);
     AnsiString countColumnStr = edColumn->Text;
     int countColumn = StrToInt(countColumnStr);

     //создание массива для edit, пусть едитов будет не больше 6.
     //AnsiString MsvEd[]={'edit1','edit2','edit3','edit4','edit5','edit6'};

     //поиск "кванта" и "порога", так назову их
     //квант в нашем случае - это типа интервал, сколько пар даем работнику
     //порог - это сколько раз используется квант, потом квант уменьшем на единицу
     //порог нужен, если есть остаток у деления
     //если нет остатка у деления, то порог равен 0
     int kvant;
     int porog;

     if(countColumn%countWorker == 0)
     {
          //ShowMessage("Делится без остатка");
          kvant = countColumn/countWorker;
          porog = 0; //нужна ли строка, посмотрим !!!!!!!!!!!!!
          ShowMessage("квант - " + IntToStr(kvant) + "\nпорог - " + IntToStr(porog));

          int i=0, indexMsv=1;
          int sum=0;
          int c;
          int kv = kvant;
          while(i<countColumn)
          {
               //тут используется только квант, без порога
               //надо подумать, как сгруппировать данные, чтобы отправить работнику
               //как только сгруппируем, сразу отправим работнику
               c = sgMassiv->Cells[i+1][1]*sgMassiv->Cells[i+1][2]; //убрать в оригинале
               sum = sum + c; //убрать в оригинале
               kv--;
               if(kv == 0)
               {
                    //в этом цикле будет переход к следующему работнику вместо edit
                    TEdit *edit = (TEdit*)FindComponent("edit"+AnsiString(indexMsv));
                    edit->Text = IntToStr(sum); //убрать в оригинале
                    indexMsv++;
                    sum = 0;//убрать в оригинале
                    kv = kvant;
               }
               i++;
          }
     }
     else
     {
          //ShowMessage("Делится c остатком");
          kvant = countColumn/countWorker + 1;

          //****рациональное распределение между работниками****
          porog = countColumn; //для удобства, для универсальности кода
          while(countWorker < porog)
          {
               porog = porog - countWorker;
          }

          //****end****
          ShowMessage("квант - " + IntToStr(kvant) + "\nпорог - " + IntToStr(porog));

          int kv = kvant;
          bool flag=false; //чтобы один раз уменьшить квант на единицу
          int i=0, indexMsv=1;
          int sum=0;
          int c;

          while(i < countColumn)
          {

               //надо подумать, как сгруппировать данные, чтобы отправить работнику
               //как только сгруппируем, сразу отправим работнику
               c = sgMassiv->Cells[i+1][1]*sgMassiv->Cells[i+1][2]; //убрать в оригинале
               sum = sum + c; //убрать в оригинале
               kv--;
               if(kv == 0)
               {
                    //в этом цикле будет переход к следующему работнику вместо edit
                    TEdit *edit = (TEdit*)FindComponent("edit"+AnsiString(indexMsv));
                    edit->Text = IntToStr(sum); //убрать в оригинале
                    indexMsv++;
                    sum = 0;//убрать в оригинале
                    porog--;
                    if(porog == 0 && flag == false)
                    {
                         kvant--;
                         flag = true;
                    }

                    kv = kvant;
               }
               i++;
          }

     }



}
//---------------------------------------------------------------------------
