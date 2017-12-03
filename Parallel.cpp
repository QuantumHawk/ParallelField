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
     //������� ���� �����
     for (int i=sgMassiv->FixedCols;i<sgMassiv->ColCount; i++)
          sgMassiv->Cols[i]->Clear();

     //������ ������� �������
     AnsiString countColumnStr = edColumn->Text;
     int countColumn = StrToInt(countColumnStr);
     sgMassiv->ColCount = countColumn + 1;

     //������� ��������
     for(int i=1; i<(countColumn+1); i++)
     {
          sgMassiv->Cells[i][0] = IntToStr(i) + " �������";
     }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
     sgMassiv->Cells[0][1] = "A";
     sgMassiv->Cells[0][2] = "�";

}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnFillClick(TObject *Sender)
{
     //�������� ��������, ���� �� ����� � ������, ����� ����� ������

     //�������������� ���������� ������� ����������
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
          ShowMessage("���� �� ������ 8 :))");
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

     //�������� ������� ��� edit, ����� ������ ����� �� ������ 6.
     //AnsiString MsvEd[]={'edit1','edit2','edit3','edit4','edit5','edit6'};

     //����� "������" � "������", ��� ������ ��
     //����� � ����� ������ - ��� ���� ��������, ������� ��� ���� ���������
     //����� - ��� ������� ��� ������������ �����, ����� ����� �������� �� �������
     //����� �����, ���� ���� ������� � �������
     //���� ��� ������� � �������, �� ����� ����� 0
     int kvant;
     int porog;

     if(countColumn%countWorker == 0)
     {
          //ShowMessage("������� ��� �������");
          kvant = countColumn/countWorker;
          porog = 0; //����� �� ������, ��������� !!!!!!!!!!!!!
          ShowMessage("����� - " + IntToStr(kvant) + "\n����� - " + IntToStr(porog));

          int i=0, indexMsv=1;
          int sum=0;
          int c;
          int kv = kvant;
          while(i<countColumn)
          {
               //��� ������������ ������ �����, ��� ������
               //���� ��������, ��� ������������� ������, ����� ��������� ���������
               //��� ������ �����������, ����� �������� ���������
               c = sgMassiv->Cells[i+1][1]*sgMassiv->Cells[i+1][2]; //������ � ���������
               sum = sum + c; //������ � ���������
               kv--;
               if(kv == 0)
               {
                    //� ���� ����� ����� ������� � ���������� ��������� ������ edit
                    TEdit *edit = (TEdit*)FindComponent("edit"+AnsiString(indexMsv));
                    edit->Text = IntToStr(sum); //������ � ���������
                    indexMsv++;
                    sum = 0;//������ � ���������
                    kv = kvant;
               }
               i++;
          }
     }
     else
     {
          //ShowMessage("������� c ��������");
          kvant = countColumn/countWorker + 1;

          //****������������ ������������� ����� �����������****
          porog = countColumn; //��� ��������, ��� ��������������� ����
          while(countWorker < porog)
          {
               porog = porog - countWorker;
          }

          //****end****
          ShowMessage("����� - " + IntToStr(kvant) + "\n����� - " + IntToStr(porog));

          int kv = kvant;
          bool flag=false; //����� ���� ��� ��������� ����� �� �������
          int i=0, indexMsv=1;
          int sum=0;
          int c;

          while(i < countColumn)
          {

               //���� ��������, ��� ������������� ������, ����� ��������� ���������
               //��� ������ �����������, ����� �������� ���������
               c = sgMassiv->Cells[i+1][1]*sgMassiv->Cells[i+1][2]; //������ � ���������
               sum = sum + c; //������ � ���������
               kv--;
               if(kv == 0)
               {
                    //� ���� ����� ����� ������� � ���������� ��������� ������ edit
                    TEdit *edit = (TEdit*)FindComponent("edit"+AnsiString(indexMsv));
                    edit->Text = IntToStr(sum); //������ � ���������
                    indexMsv++;
                    sum = 0;//������ � ���������
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
