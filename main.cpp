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


class Objects  //大类
{
public:             //公共权限
    Objects()
    {
    }
    char name[20];//物品名称
    int amount;  //物品数量；
    char doner[20];  //贡献者；
    char user[20];   //使用者；
    char donerinfo[20]; //贡献者信息；
    char order[20];//商品序号；

    Objects* Next;

    void InputAll()   
    {

        InputOrder();
        InputName();
        InputDoner();
        InputDonerinfo();
    }

    void InputOrder()
    {
        cout << "\t\t请输入物品的序号："; cin >> order;
    }

    void InputName()
    {
        cout << "\t\t请输入物品的名称：";  cin >> name;
    }
    void InputDoner()
    {
        cout << "\t\t请输入您的昵称："; cin >> doner;

    }
    void InputDonerinfo()
    {
        cout << "\t\t请输入您的物品获取方式："; cin >> donerinfo;
    }
    void Show2()
    {
        cout << "物品序号: " << order << endl << "物品名称:" << name << endl << "物品贡献者： " << doner << endl << "物品获取方式： " << donerinfo << endl << "物品数量数量: " <<
            amount  << endl;
    }
    void ReadFile(istream& in)
    {
        in >> order >> name >> doner >> donerinfo >> amount;
    };
};

class ObjectsInformation: public Objects

{
public:                                             //公共权限
    ObjectsInformation();                           //函数声明
    ~ObjectsInformation();
    void showMenu(int n);
    void Find();
    void Save();
    void RemoveGetItem();
    void Swap(Objects*, Objects*);
    int ListCount();


    void AddItem()                      //从键盘输入商品信息
    {
        system("cls");
        End->InputName();
        showMenu(1);

        End->Next = new Objects;
        End = End->Next;
        cout << "添加成功!" << endl;
        Save();
        cout << "输入任意字符！继续……";
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
};            // ObjectsInformation类



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
        "\t\t\t\t目前无可用物品" << endl;
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
        cout << "\t\t\t\t请选择你想要的物品并与贡献者联系" << "\n" << endl;
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


void ObjectsInformation::showMenu(int n)//菜单
{
    switch (n)
    {
    case 1:
       {
        cout << "      1. 序号      2. 物品名称      3. 物品贡献者      4. 获取方式      \n"
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
        cout << " **************************    你帮我助系统     **************************" << endl;
        cout << "                                  " << endl; cout << "                                  " << endl;
        cout << "                   1.增添物品                     " << endl;
        cout << "                                  " << endl;
        cout << "                   2.查询物品                    " << endl;
        cout << "                                  " << endl;
        cout << "                   3.删除or获取物品                    " << endl;
        cout << "                                  " << endl;
        cout << "                   4.保存信息至文件中                    " << endl;
        cout << "                                  " << endl;
        cout << "                   0.退出系统                    " << endl;

        cout << "\t\t\n\t\t\t\t 请选择：0-4" << endl;
        break;
        }
    }
}

void ObjectsInformation::Find()       //查找物品
{
    system("cls");
    char name[20], Id[10]{};
    Objects* p = NULL;
  cout << "\t\t请输入要查找的物品的名称："; cin >> name;
  if (p = FindItem(name))
  {
      p->Next->Show2();
      cout << "输入任意字符！继续……";
      _getch();
  }
  else
  {
      cout << "\t\t没有找到该名称的物品！" << '\n' << endl;
      cout << "输入任意字符！继续……";
      _getch();
  };
}

void ObjectsInformation::Save()       //保存物品信息到文件
{

    out.open("information.txt");
    for (Objects* p = Head->Next; p != End; p = p->Next)
        out << p->order << "\t" << p->name << "\t" << p->doner << "\t" << donerinfo << "\t" << p->amount <<  '\n';

    out.close();
    cout << "保存信息成功" << endl;
}

void ObjectsInformation::RemoveGetItem()          //删除物品信息
{
    system("cls");
    char name[20];
    Objects* p = NULL, * temp = NULL;

    cout << "\t\t请输入删除or获取的物品名称:" << endl; cin >> name;
    if (p = FindItem(name))
    {
        temp = p->Next;
        p->Next = p->Next->Next;
        delete temp;
        cout << "\t\t删除or获取成功!" << endl;
        Save();
        cout << "输入任意字符！继续……";
        _getch();
    }
    else
    {
        cout << "\t\t没有找到您需要的物品!" << endl;
        cout << "输入任意字符！继续……";
        _getch();
    }
}



int main()
{
    cout << "你帮我助软件系统" << endl;
    ObjectsInformation Grade;

    cout << "温馨提示：按任意键进入系统";
    _getch();
    int k;
    bool quit = false;
    while (!quit)
    {
        Grade.showMenu(2);
        cin >> k;
        switch (k)
      {
        case 0: {quit = true; break; }  //退回界面
        case 1: {Grade.AddItem(); break; }//添加物品
        case 2: {Grade.Find(); break; }//查找物品
        case 3: {Grade.RemoveGetItem(); break; }//删除or获取物品
        case 4: {Grade.Save(); break; }//保存信息
      }
    }
    return 0;
}
