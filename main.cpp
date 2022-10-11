#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <malloc.h>
#include <windows.h>
#include <stdlib.h>

using namespace std;


class Objects  //����
{
public:             //����Ȩ��
    Objects()
    {
    }
    char name[20];//��Ʒ����
    int amount;  //��Ʒ������
    char doner[20];  //�����ߣ�
    char user[20];   //ʹ���ߣ�
    char donerinfo[20]; //��������Ϣ��
    char order[20];//��Ʒ��ţ�

    Objects* Next;

    void InputAll()   //��ӡ ���� ���� ������ �۳���  �������  ���� Ʒ��
    {

        InputOrder();
        InputName();
        InputDoner();
        InputDonerinfo();
    }

    void InputOrder()
    {
        cout << "\t\t��������Ʒ����ţ�"; cin >> order;
    }

    void InputName()
    {
        cout << "\t\t��������Ʒ�����ƣ�";  cin >> name;
    }
    void InputDoner()
    {
        cout << "\t\t�����������ǳƣ�"; cin >> doner;

    }
    void InputDonerinfo()
    {
        cout << "\t\t������������Ʒ��ȡ��ʽ��"; cin >> donerinfo;
    }
    void Show2()
    {
        cout << "��Ʒ���: " << order << endl << "��Ʒ����:" << name << endl << "��Ʒ�����ߣ� " << doner << endl << "��Ʒ��ȡ��ʽ�� " << donerinfo << endl << "��Ʒ��������: " <<
            amount  << endl;
    }
    void ReadFile(istream& in)
    {
        in >> order >> name >> doner >> donerinfo >> amount;
    };
};

class ObjectsInformation: public Objects

{
public:                                             //����Ȩ��
    ObjectsInformation();                           //��������
    ~ObjectsInformation();
    void showMenu(int n);
    void Find();
    void Save();
    void RemoveGetItem();
    void Swap(Objects*, Objects*);
    int ListCount();


    void AddItem()                      //�Ӽ���������Ʒ��Ϣ
    {
        system("cls");
        End->InputName();
        showMenu(1);

        End->Next = new Objects;
        End = End->Next;
        cout << "��ӳɹ�!" << endl;
        Save();
        cout << "���������ַ�����������";
        _getch();
    }
private:
    Objects* Head, * End;
    int i;
    ifstream in;
    ofstream out;
    Objects* FindItem(char* name)
    {
        for (Objects* p = Head; p->Next != End; p = p->Next)
            if (!strcmp(p->Next->name, name))return p;
        return NULL;
    }
};            // ObjectsInformation��



int ObjectsInformation::ListCount()
{
    if (!Head)
        return 0;
    int n = 0;
    for (Objects* p = Head->Next; p != End; p = p->Next)
    {
        n++;
    }
    return n;
}


ObjectsInformation::ObjectsInformation()
{
    Head = new Objects;
    Head->Next = new Objects;
    End = Head->Next;
    in.open("supermarket.txt");
    if (!in)

        cout << "                                       " << endl <<
        "                                       " << endl <<
        "                                       " << endl <<
        "\t\t\t\tĿǰ�޿�����Ʒ" << endl;
    else
    {
        while (!in.eof())
        {
            End->ReadFile(in);
            if (End->name[0] == '\0')break;
            End->Next = new Objects;
            End = End->Next;
        }
        in.close();
        cout << "    " << endl;
        cout << "    " << endl;
        cout << "    " << endl;
        cout << "    " << endl;
        cout << "\t\t\t\t��ѡ������Ҫ����Ʒ���빱������ϵ" << "\n" << endl;
    }
}

ObjectsInformation::~ObjectsInformation()
{
    Save();
    for (Objects* temp; Head->Next != End;)
    {
        temp = Head->Next;
        Head->Next = Head->Next->Next;
        delete temp;
    }
    delete Head, End;
}


void ObjectsInformation::showMenu(int n)//�˵�
{
    switch (n)
    {
    case 1:
       {
        cout << "      1. ���      2. ��Ʒ����      3. ��Ʒ������      4. ��ȡ��ʽ      \n"
            << endl;
        break;
       }
    case 2:
       {
        system("cls");
        cout << "                                  " << endl;
        cout << "                                  " << endl;
        cout << "                                  " << endl;
        cout << "                                  " << endl;
        cout << " **************************    �������ϵͳ     **************************" << endl;
        cout << "                                  " << endl; cout << "                                  " << endl;
        cout << "                   1.������Ʒ                     " << endl;
        cout << "                                  " << endl;
        cout << "                   2.��ѯ��Ʒ                    " << endl;
        cout << "                                  " << endl;
        cout << "                   3.ɾ��or��ȡ��Ʒ                    " << endl;
        cout << "                                  " << endl;
        cout << "                   4.������Ϣ���ļ���                    " << endl;
        cout << "                                  " << endl;
        cout << "                   0.�˳�ϵͳ                    " << endl;

        cout << "\t\t\n\t\t\t\t ��ѡ��0-4" << endl;
        break;
        }
    }
}

void ObjectsInformation::Find()       //������Ʒ
{
    system("cls");
    char name[20], Id[10]{};
    Objects* p = NULL;
  cout << "\t\t������Ҫ���ҵ���Ʒ�����ƣ�"; cin >> name;
  if (p = FindItem(name))
  {
      p->Next->Show2();
      cout << "���������ַ�����������";
      _getch();
  }
  else
  {
      cout << "\t\tû���ҵ������Ƶ���Ʒ��" << '\n' << endl;
      cout << "���������ַ�����������";
      _getch();
  };
}

void ObjectsInformation::Save()       //������Ʒ��Ϣ���ļ�
{

    out.open("information.txt");
    for (Objects* p = Head->Next; p != End; p = p->Next)
        out << p->order << "\t" << p->name << "\t" << p->doner << "\t" << donerinfo << "\t" << p->amount <<  '\n';

    out.close();
    cout << "������Ϣ�ɹ�" << endl;
}

void ObjectsInformation::RemoveGetItem()          //ɾ����Ʒ��Ϣ
{
    system("cls");
    char name[20];
    Objects* p = NULL, * temp = NULL;

    cout << "\t\t������ɾ��or��ȡ����Ʒ����:" << endl; cin >> name;
    if (p = FindItem(name))
    {
        temp = p->Next;
        p->Next = p->Next->Next;
        delete temp;
        cout << "\t\tɾ��or��ȡ�ɹ�!" << endl;
        Save();
        cout << "���������ַ�����������";
        _getch();
    }
    else
    {
        cout << "\t\tû���ҵ�����Ҫ����Ʒ!" << endl;
        cout << "���������ַ�����������";
        _getch();
    }
}



int main()
{
    cout << "����������ϵͳ" << endl;
    ObjectsInformation Grade;

    cout << "��ܰ��ʾ�������������ϵͳ";
    _getch();
    int k;
    bool quit = false;
    while (!quit)
    {
        Grade.showMenu(2);
        cin >> k;
        switch (k)
      {
        case 0: {quit = true; break; }  //�˻ؽ���
        case 1: {Grade.AddItem(); break; }//�����Ʒ
        case 2: {Grade.Find(); break; }//������Ʒ
        case 3: {Grade.RemoveGetItem(); break; }//ɾ��or��ȡ��Ʒ
        case 4: {Grade.Save(); break; }//������Ϣ
      }
    }
    return 0;
}
