//本代码采用GBK编码，若出现中文乱码请在终端输入  >chcp 936
#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
#define Max 1000 //通讯录最大容量

//学生联系人结构体
struct Person
{
   string m_Name;  //姓名
   int m_Sex;      //性别 1 男 2 女
   int m_Age;      //年龄
   string m_Addr;  //寝室
   string m_Phone; //电话
};
//模糊映射
unordered_map<char, vector<int>> mp;
//学生通讯录结构体
struct Addressbooks
{
   struct Person personArray[Max];
   int m_Size; //当前人数;
};
bool cmp(Person a, Person b)
{
   return a.m_Name < b.m_Name;
}
//开始界面
void startPage();
//关闭界面
void overPage();
//菜单
void showMenu();
//添加学生联系人
void addPerson(Addressbooks *adsPerson);
//显示学生联系人
void showPerson(Addressbooks *adsPerson);
//检测学生联系人是否存在
int judgePro(Addressbooks *adsPerson, string name);
pair<int, int> judge(Addressbooks *adsPerson, string name);
//删除学生联系人
void deletePerson(Addressbooks *adsPerson);
//精确查找学生联系人
void ExactSearch(Addressbooks *adsPerson);
//模糊查找学生联系人
void FuzzySearch(Addressbooks *adsPerson);
//修改学生联系人
void modifyPerson(Addressbooks *adsPerson);
//清空学生联系人
void clearPerson(Addressbooks *adsPerson);
//全屏
void full_screen();
//debug
void FuzzySearchPro(Addressbooks *adsPerson);
//快速读入测试数据
void developerFunctions(Addressbooks *adsPerson)
{
   freopen("data.in", "r", stdin);
   //cin.clear();
   //cout << "请输入姓名" << endl;
   int times = 5; //测试数据数量
   while (times--)
   {
      string name;
      cin >> name;
      adsPerson->personArray[adsPerson->m_Size].m_Name = name;
      int sex;
      //cout << "请输入性别" << endl;
      // cout << "1 男" << endl;
      // << "2 女" << endl;
      string temp;
      cin >> temp;
      if (temp == "男" || temp == "1")
         sex = 1;
      else if (temp == "女" || temp == "2")
         sex = 2;
      if (sex == 1 || sex == 2)
      {
         adsPerson->personArray[adsPerson->m_Size].m_Sex = sex;
      }
      //cout << "请输入年龄" << endl;
      int age;

      cin >> age;
      adsPerson->personArray[adsPerson->m_Size].m_Age = age;
      //cout << "请输入寝室" << endl;
      string address;
      cin >> address;
      adsPerson->personArray[adsPerson->m_Size].m_Addr = address;
      //cout << "请输入电话号码" << endl;
      string phone;
      cin >> phone;
      adsPerson->personArray[adsPerson->m_Size].m_Phone = phone;
      adsPerson->m_Size++;
      sort(adsPerson->personArray, adsPerson->personArray + adsPerson->m_Size, cmp);
   }
   fclose(stdin);
}
int main()
{
   full_screen();
   startPage();
   Addressbooks adsPerson;
   adsPerson.m_Size = 0;

   int select = 0;
   while (true)
   {
      showMenu();
      cin.clear();
      cin >> select;
      //scanf("%d", &select);
      switch (select)
      {
      case 1:
      {
         addPerson(&adsPerson);
         break;
      }
      case 2:
      {
         showPerson(&adsPerson);
         break;
      }
      case 3:
      {
         deletePerson(&adsPerson);
         break;
      }
      case 4: //精确查找联系人
      {
         ExactSearch(&adsPerson);
         break;
      }
      case 5: //模糊查找联系人
      {
         FuzzySearchPro(&adsPerson);
         FuzzySearch(&adsPerson);
         break;
      }
      case 6:
      {
         modifyPerson(&adsPerson);
         break;
      }
      case 7: //清空
      {
         clearPerson(&adsPerson);
         break;
      }
      case 0:
      {
         overPage();
         return 0;
      }
      case 8: //导入测试数据
      {
         developerFunctions(&adsPerson);
         freopen("CON", "r", stdin);
         cin.clear();
         cout << "导入成功！" << endl;
         system("pause");
         system("cls");
         break;
      }
      case 9: //debug
      {
         cout << "???" << endl;
         system("pause");
         system("cls");
         break;
      }
      }
   }

   system("pause");
   return 0;
}
//开始界面
void startPage()
{
   cout << R"(　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　
　　　　　　　　　　　　　　　※※　　　　　　　　　　　　　　　　※※　　　　　　　　　※※　　　　　　　　　　　　　　
　　　　　　　　　　　　　　　※※　　　　　　　　　　　　　　　　※※※　　　　※※※※※※　　※※※※※※　　　　　　
　　　　　　　　　　　　　　　※※※※※※※※※　　　　　　　　　※※※※　　※※※※※※※　※※※※※※※※　　　　　
　　　※※※※※※※※※※　　※※※※※※※※※※　　　　　　　　　※※※　　※※※　　　　※※※※※※※※※　　　　　
　　　※※※※※※※※※※　※※※　　　　　　※※※　　　　　　　　　※※※　※※　　　　　※※　　　　　※※　　　　　
　　　　　　　　　　　※※　※※※　※※　　　　※※　　　　　　　　　　※※　※※　　　　　※※　　　　　※※　　　　　
　　　※※　　　　　　※※　※※　　※※　　　　※※　　　　　　　　　　　　　※※　　　　　※※　　　　　※※　　　　　
　　　※※※　　　　　※※　※※　　※※　　　※※※　　　　　　　　　　　　　※※　　　　　※※　　　　　※※　　　　　
　　　　※※※　　　※※※※※※　　※※　　　※※※　　　　　　※※※※　　　※※　　　　　※※　　　　　※※　　　　　
　　　　※※※　　　※※※※※※　　※※　　　※※　　　　　　　※※※※※※　※※　　　　　※※　　　　　※※　　　　　
　　　　　※※※　　※※　※※　　　※※　　　※※　　　　　　　　　　※※※　※※　　　　　※※　　　　　※※　　　　　
　　　　　　※※※※※※　※※　　　※※※　※※※　　　　　　　　　　　※※　※※　　　　　※※　　　　　※※　　　　　
　　　　　　※※※※※※　　　　　　※※※　※※　　　　　　　　　　　　※※　※※　　　　　※※　　　　　※※　　　　　
　　　　　　　※※※※　　　　　　　※※※　　　　　　　　　　　　　　　※※　※※　　　　　※※　　　　　※※　　　　　
　　　　　　　　※※※　　　　　　※※※※※　　　　　　　　　　　　　　※※　※※　　　　　※※　　　　　※※　　　　　
　　　　　　　※※※※　　　　　　※※※※※　　　　　　　　　　　　　　※※　※※　　※※※※※　　　　　※※　　　　　
　　　　　　※※※※※※　　　　※※※　※※※　　　　　　　　　　　　　※※　※※※※※※※※※　　　　　※※　　　　　
　　　　　　※※※※※※　　　　※※※　※※※　　　　　　　　　　　　　※※　※※※※※※　※※　※※　　※※　　　　　
　　　　　※※※　　※※※　　※※※　　　※※※　　　　　　　　　　　　※※　※※※※　　　※※　※※※※※※　　　　　
　　　　※※※　　　※※※　　※※※　　　※※※　　　　　　　　　　　※※※　　　　　　　　※※　※※※※※※　　　　　
　　　※※※　　　　　※※　※※※　　　　　※※※　　　　　　　　　※※※※※　　　　　　　※※　　　　　　　　　　　　
　　※※※※　　　　　※※※※※　　　　　　　※※※　　　　　　　※※※　※※※※　　　　　※※　　　　　　　　　　　　
　　※※※　　　　　　　※※※※　　　　　　　※※※※　　　　　※※※※　　※※※※※※※※※※※※※※※※※※　　　　
　　※※　　　　　　　　※※※　　　　　　　　　※※※　　　　　※※※　　　　※※※※※※※※※※※※※※※※※※　　　
　　　　　　　　　　　　※※　　　　　　　　　　　※※　　　　　　　　　　　　　　　　※※※※※※※※※※※※※　　　　
   )";
   _sleep(1500);
   system("cls");
}
//关闭界面
void overPage()
{
   system("cls");
   cout << R"(　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　
　※※※※※※※※※※※※※※※※※※※※※※※※※　　　　　　　　　　※※※※※※※※※※※※※※※※　　　　　　　　
　　※※※※※※※※※※※※※※※※※※※※※※※　　　　　　　　　　※※※※※※※※※※※※※※※※※※　　　　　　　
　　　　　　　　　　　　※※　　　　　　　　　　　　　　　　　　　　　※※　　　　　　　　　　　　　　※※　　　　　　　
　　　　　　　　　　　　※※　　　　　　　　　　　　　　　　　　　　　※※　　　　　　　　　　　　　　※※　　　　　　　
　　　　※※※※※※※※※※※※※※※※※※※　　　　　　　　　　　　※※　　　　　　※※　　　　　　※※　　　　　　　
　　　　※※※※※※※※※※※※※※※※※※※※　　　　　　　　　　　※※　　　　　　※※　　　　　　※※　　　　　　　
　　　　※※　　　　　　※※　　　　　　　　※※　　　　　　　　　　　※※　　　　　　※※　　　　　　※※　　　　　　　
　　　　※※　　　　　　※※　　　　　　　　※※　　　　　　　　　　　※※　　　　　　※※　　　　　　※※　　　　　　　
　　　　※※　　　　　　※※　　　　　　　　※※　　　　　　　　　　　※※　　　　　　※※　　　　　　※※　　　　　　　
　　　　※※※※※※※※※※※※※※※※※※※※　　　　　　　　　　　※※　　　　　　※※　　　　　　※※　　　　　　　
　　　　※※※※※※※※※※※※※※※※※※※※　　　　　　　　　　　※※　　　　　　※※※　　　　　※※　　　　　　　
　　　　※※　　　　　　※※　　　　　　　　※※　　　　　　　　　　　※※　　　　　※※※※※　　　　※※　　　　　　　
　　　　※※　　　　　　※※　　　　　　　　※※　　　　　　　　　　　※※　　　　　※※　※※　　　　※※　　　　　　　
　　　　※※　　　　　　※※　　　　　　　　※※　　　　　　　　　　　※※　　　　　※※　※※　　　　※※　　　　　　　
　　　　※※　　　　　　※※　　　　　　　　※※　　　　　　　　　　　※※　　　　※※※　※※　　　　※※　　　　　　　
　※※※※※※※※※※※※※※※※※※※※※※※※※※　　　　　　　　※※　　　　※※※　※※　　　　※※　　　　　　　
　※※※※※※※※※※※※※※※※※※※※※※※※※　　　　　　　　　　※　　　※※※　　※※　　　　　　　　　　　　　
　　　　※※　　　　　　　　　　　　　　　　※※　　　　　　　　　　　　　　　※※※　　　※※　　　　　　　※※　　　　
　　　　※※　　　　　　　　　　　　　　　　※※　　　　　　　　　　　　　　※※※※　　　※※　　　　　　　※※　　　　
　　　　※※　　　　　　　　　　　　　　　　※※　　　　　　　　　　　　　※※※※　　　　※※　　　　　　　※※　　　　
　　　　※※　　　　　　　　　　　　　　　　※※　　　　　　　　　　　※※※※※　　　　　※※　　　　　　　※※　　　　
　　　　※※　　　　　　　　　　※※※※※※※※　　　　　　　　　※※※※※※　　　　　　※※　　　　　　※※※　　　　
　　　　※※　　　　　　　　　　※※※※※※※　　　　　　　　　※※※※※　　　　　　　　※※※※※※※※※※　　　　　
　　　　※　　　　　　　　　　　　　※※※※　　　　　　　　　　※※※　　　　　　　　　　　※※※※※※※※　　　　　　　　　　
   )";
   _sleep(1500);
   system("cls");
}
//展示菜单
void showMenu()
{
   cout << R"(
       __        __   _                          
       \ \      / /__| | ___ ___  _ __ ___   ___ 
        \ \ /\ / / _ \ |/ __/ _ \| '_ ` _ \ / _ \
         \ V  V /  __/ | (_| (_) | | | | | |  __/
          \_/\_/ \___|_|\___\___/|_| |_| |_|\___|
  _             _     _ ____                           
 / |   __ _  __| | __| |  _ \ ___ _ __ ___  ___  _ __  
 | |  / _` |/ _` |/ _` | |_) / _ \ '__/ __|/ _ \| '_ \ 
 | | | (_| | (_| | (_| |  __/  __/ |  \__ \ (_) | | | |                       添加联系人
 |_|  \__,_|\__,_|\__,_|_|   \___|_|  |___/\___/|_| |_|
 ____        _                   ____                           
|___ \   ___| |__   _____      _|  _ \ ___ _ __ ___  ___  _ __  
  __) | / __| '_ \ / _ \ \ /\ / / |_) / _ \ '__/ __|/ _ \| '_ \ 
 / __/  \__ \ | | | (_) \ V  V /|  __/  __/ |  \__ \ (_) | | | |              显示联系人
|_____| |___/_| |_|\___/ \_/\_/ |_|   \___|_|  |___/\___/|_| |_|
  _____       _      _      _       ____                           
 |___ /    __| | ___| | ___| |_ ___|  _ \ ___ _ __ ___  ___  _ __  
   |_ \   / _` |/ _ \ |/ _ \ __/ _ \ |_) / _ \ '__/ __|/ _ \| '_ \ 
  ___) | | (_| |  __/ |  __/ ||  __/  __/  __/ |  \__ \ (_) | | | |           删除联系人
 |____/   \__,_|\___|_|\___|\__\___|_|   \___|_|  |___/\___/|_| |_|                                                                
  _  _                         _   ____                      _     
 | || |     _____  ____ _  ___| |_/ ___|  ___  __ _ _ __ ___| |__  
 | || |_   / _ \ \/ / _` |/ __| __\___ \ / _ \/ _` | '__/ __| '_ \ 
 |__   _| |  __/>  < (_| | (__| |_ ___) |  __/ (_| | | | (__| | | |           精确搜索
    |_|    \___/_/\_\__,_|\___|\__|____/ \___|\__,_|_|  \___|_| |_|                                                                  
  ____     __                     ____                      _     
 | ___|   / _|_   _ _________   _/ ___|  ___  __ _ _ __ ___| |__  
 |___ \  | |_| | | |_  /_  / | | \___ \ / _ \/ _` | '__/ __| '_ \ 
  ___) | |  _| |_| |/ / / /| |_| |___) |  __/ (_| | | | (__| | | |            模糊搜索
 |____/  |_|  __,_/___/___|\__, |____/ \___|\__,_|_|  \___|_| |_|
                            |___/                                                                                           
   __                         _ _  __       ____                           
  / /_    _ __ ___   ___   __| (_)/ _|_   _|  _ \ ___ _ __ ___  ___  _ __  
 | '_ \  | '_ ` _ \ / _ \ / _` | | |_| | | | |_) / _ \ '__/ __|/ _ \| '_ \ 
 | (_) | | | | | | | (_) | (_| | |  _| |_| |  __/  __/ |  \__ \ (_) | | | |   修改联系人 
  \___/  |_| |_| |_|\___/ \__,_|_|_|  \__, |_|   \___|_|  |___/\___/|_| |_|
                                      |___/                                
  _____        _                 ____                           
 |___  |   ___| | ___  __ _ _ __|  _ \ ___ _ __ ___  ___  _ __  
    / /   / __| |/ _ \/ _` | '__| |_) / _ \ '__/ __|/ _ \| '_ \ 
   / /   | (__| |  __/ (_| | |  |  __/  __/ |  \__ \ (_) | | | |              清空通讯录
  /_/     \___|_|\___|\__,_|_|  |_|   \___|_|  |___/\___/|_| |_|
   ___              _ _   
  / _ \    _____  _(_) |_ 
 | | | |  / _ \ \/ / | __|                                                      退出 
 | |_| | |  __/>  <| | |_  
  \___/   \___/_/\_\_|\__|

----------------------------------------------------------------------------------------------- 
   8  *****开发选项******                 ->                                  快速导入测试数据       
-----------------------------------------------------------------------------------------------     

)";
}
//添加联系人
void addPerson(Addressbooks *adsPerson)
{
   if (adsPerson->m_Size == Max)
   {
      cout << "ERROR:添加失败,通讯录最大人数为100." << endl;
   }
   else
   {
      //姓名
      cout << "请输入姓名" << endl;
      string name;
      cin >> name;
      adsPerson->personArray[adsPerson->m_Size].m_Name = name;
      //性别
      int sex;
      cout << "请输入性别" << endl;
      cout << "1 男" << endl;
      cout << "2 女" << endl;
      while (1)
      {
         string temp;
         cin >> temp;
         if (temp == "男" || temp == "1")
            sex = 1;
         else if (temp == "女" || temp == "2")
            sex = 2;
         else
            sex = 3;
         if (sex == 1 || sex == 2)
         {
            adsPerson->personArray[adsPerson->m_Size].m_Sex = sex;
            break;
         }
         else if (sex == 3)
         {
            cout << "ERROR:请输入1或者2或者男或者女" << endl;
         }
      }
      cout << "请输入年龄" << endl;
      int age;
      while (1)
      {
         cin >> age;
         if (age >= 0 and age <= 100)
         {
            adsPerson->personArray[adsPerson->m_Size].m_Age = age;
            break;
         }
         else
         {
            cout << "ERROR:错误的值，请重新输入." << endl;
         }
      }
      cout << "请输入寝室" << endl;
      string address;
      cin >> address;
      adsPerson->personArray[adsPerson->m_Size].m_Addr = address;
      cout << "请输入电话号码" << endl;
      string phone;
      while (1)
      {
         cin >> phone;
         regex re("1\\d{10}");
         if (regex_match(phone, re) or (phone.size() == 3))
         {
            break;
         }
         else
         {
            cout << "ERROR:电话格式有误,请重新输入." << endl;
         }
      }
      adsPerson->personArray[adsPerson->m_Size].m_Phone = phone;
      adsPerson->m_Size++;
      sort(adsPerson->personArray, adsPerson->personArray + adsPerson->m_Size, cmp);
      cout << "已完成添加." << endl;
      system("pause");
      system("cls");
   }
}
//显示联系人
void showPerson(Addressbooks *adsPerson)
{
   if (adsPerson->m_Size == 0)
   {
      cout << "ERROR:通讯录为空." << endl;
   }
   else
   {
      cout << "姓名"
           << "\t"
           << "性别"
           << "\t"
           << "年龄"
           << "\t"
           << "寝室"
           << "\t"
           << "电话" << endl;
      for (int i = 0; i < adsPerson->m_Size; i++)
      {
         cout << adsPerson->personArray[i].m_Name << "\t"
              << (adsPerson->personArray[i].m_Sex == 1 ? "男" : "女") << "\t"
              << adsPerson->personArray[i].m_Age << "\t" << adsPerson->personArray[i].m_Addr << "\t"
              << adsPerson->personArray[i].m_Phone
              << endl;
      }
   }
   system("pause");
   system("cls");
}
//检测联系人是否存在
pair<int, int> judge(Addressbooks *adsPerson, string name)
{
   pair<int, int> ret;
   ret.first = -1;
   ret.second = -1;
   for (int i = 0; i < adsPerson->m_Size; i++)
   {
      if (name[0] == adsPerson->personArray[i].m_Name[0])
      {
         ret.first = i;
         ret.second = i;
         int j = i + 1;
         while (j <= adsPerson->m_Size && name[0] == adsPerson->personArray[j].m_Name[0])
         {
            ret.second = j;
            j++;
         }
         break;
      }
   }
   return ret;
}

//删除联系人
void deletePerson(Addressbooks *adsPerson)
{
   if (adsPerson->m_Size == 0)
   {
      cout << "ERROR:通讯录为空." << endl;
      system("pause");
      system("cls");
      return;
   }
   showMenu();
   cout << "请输入要删除的联系人" << endl;
   string name;
   cin >> name;
   int ret = judgePro(adsPerson, name);
   if (ret != -1)
   {
      for (int i = ret; i < adsPerson->m_Size; i++)
      {
         adsPerson->personArray[i] = adsPerson->personArray[i + 1];
      }
      adsPerson->m_Size--;
      cout << "删除已完成" << endl;
      system("pause");
      system("cls");
   }
   else
   {
      cout << "ERROR:无效的联系人." << endl;
      system("pause");
      system("cls");
   }
}
//精确查找联系人
void ExactSearch(Addressbooks *adsPerson)
{
   if (adsPerson->m_Size == 0)
   {
      cout << "ERROR:通讯录为空." << endl;
      system("pause");
      system("cls");
      return;
   }
   cout << "请输入要精确查找的学生姓名" << endl;
   string name;
   cin >> name;
   int ret = judgePro(adsPerson, name);
   if (ret != -1 && adsPerson->personArray[ret].m_Name == name)
   {
      cout << "姓名"
           << "\t"
           << "性别"
           << "\t"
           << "年龄"
           << "\t"
           << "寝室"
           << "\t"
           << "电话" << endl;
      cout << adsPerson->personArray[ret].m_Name << "\t";
      cout << (adsPerson->personArray[ret].m_Sex == 1 ? "男" : "女") << "\t";
      cout << adsPerson->personArray[ret].m_Age << "\t";
      cout << adsPerson->personArray[ret].m_Phone << "\t";
      cout << adsPerson->personArray[ret].m_Addr << endl;
      system("pause");
      system("cls");
   }
   else
   {
      cout << "ERROR:结果为空." << endl;
      system("pause");
      system("cls");
   }
}
//模糊查找联系人
void FuzzySearch(Addressbooks *adsPerson)
{
   if (adsPerson->m_Size == 0)
   {
      cout << "ERROR:通讯录为空." << endl;
      system("pause");
      system("cls");
      return;
   }
   cout << "请输入要模糊查找的联系人" << endl;
   string name;
   cin >> name;
   if (name.size() > 2)
   {
      pair<int, int> ret = judge(adsPerson, name);
      if (ret.first != -1 && ret.second != -1)
      {
         cout << "姓名"
              << "\t"
              << "性别"
              << "\t"
              << "年龄"
              << "\t"
              << "寝室"
              << "\t"
              << "电话" << endl;
         for (int k = ret.first; k <= ret.second; k++)
         {
            cout << adsPerson->personArray[k].m_Name << "\t";
            cout << (adsPerson->personArray[k].m_Sex == 1 ? "男" : "女") << "\t";
            cout << adsPerson->personArray[k].m_Age << "\t";
            cout << adsPerson->personArray[k].m_Phone << "\t";
            cout << adsPerson->personArray[k].m_Addr << endl;
         }
         system("pause");
         system("cls");
      }
      else
      {
         cout << "ERROR:结果为空." << endl;
         system("pause");
         system("cls");
      }
   }
   else
   {
      if (mp[name[0]].size() != 0)
      {
         cout << "姓名"
              << "\t"
              << "性别"
              << "\t"
              << "年龄"
              << "\t"
              << "寝室"
              << "\t"
              << "电话" << endl;
         for (int id : mp[name[0]])
         {
            cout << adsPerson->personArray[id].m_Name << "\t";
            cout << (adsPerson->personArray[id].m_Sex == 1 ? "男" : "女") << "\t";
            cout << adsPerson->personArray[id].m_Age << "\t";
            cout << adsPerson->personArray[id].m_Phone << "\t";
            cout << adsPerson->personArray[id].m_Addr << endl;
         }
         system("pause");
         system("cls");
      }
      else
      {
         cout << "ERROR:结果为空." << endl;
         system("pause");
         system("cls");
      }
   }
}
//修改联系人
void modifyPerson(Addressbooks *adsPerson)
{
   if (adsPerson->m_Size == 0)
   {
      cout << "ERROR:通讯录为空." << endl;
      return;
   }
   cout << "请输入要修改的学生联系人" << endl;
   string name;
   cin >> name;
   int ret = judgePro(adsPerson, name);
   if (ret != -1)
   {

      //姓名
      cout << "请输入姓名" << endl;
      string name;
      cin >> name;
      adsPerson->personArray[ret].m_Name = name;
      //性别
      int sex;
      cout << "请输入性别" << endl;
      cout << "1 男" << endl;
      cout << "2 女" << endl;
      while (1)
      {
         string temp;
         cin >> temp;
         if (temp == "男" || temp == "1")
            sex = 1;
         else if (temp == "女" || temp == "2")
            sex = 2;
         else
            sex = 3;
         if (sex == 1 || sex == 2)
         {
            adsPerson->personArray[ret].m_Sex = sex;
            break;
         }
         else
         {
            cout << "ERROR:请输入1或者2或者男或者女" << endl;
         }
      }
      cout << "请输入年龄" << endl;
      int age;
      while (1)
      {
         cin >> age;
         if (age >= 0 and age <= 100)
         {
            adsPerson->personArray[ret].m_Age = age;
            break;
         }
         else
         {
            cout << "ERROR:错误的值，请重新输入." << endl;
         }
      }
      cout << "请输入寝室" << endl;
      string address;
      cin >> address;
      adsPerson->personArray[ret].m_Addr = address;
      cout << "请输入电话" << endl;
      string phone;
      while (1)
      {
         cin >> phone;
         regex re("1\\d{10}");
         if (regex_match(phone, re) or (phone.size() == 3))
         {
            break;
         }
         else
         {
            cout << "ERROR:电话格式有误,请重新输入." << endl;
         }
      }
      adsPerson->personArray[ret].m_Phone = phone;
      sort(adsPerson->personArray, adsPerson->personArray + adsPerson->m_Size, cmp);
      cout << "已完成修改" << endl;
      system("pause");
      system("cls");
   }
   else
   {
      cout << "ERROR:结果为空." << endl;
      system("pause");
      system("cls");
   }
}
void clearPerson(Addressbooks *adsPerson)
{
   if (adsPerson->m_Size == 0)
   {
      cout << "ERROR:通讯录为空." << endl;
      return;
   }
   adsPerson->m_Size = 0;
   cout << "清空成功" << endl;
   system("pause");
   system("cls");
}
//精确查找的判断
int judgePro(Addressbooks *adsPerson, string name)
{
   int low = 0, high = adsPerson->m_Size - 1;
   int mid = 0;
   while (low <= high)
   {
      mid = (low + high) / 2;
      if (adsPerson->personArray[mid].m_Name == name)
         return mid;
      else if (adsPerson->personArray[mid].m_Name > name)
         high = mid - 1;
      else
         low = mid + 1;
   }
   return -1;
}

void FuzzySearchPro(Addressbooks *adsPerson)
{
   if (adsPerson->m_Size == 0)
      return;
   mp.clear();
   for (int i = 0; i < adsPerson->m_Size; i++)
   {
      for (int j = 0; j < adsPerson->personArray[i].m_Name.size(); j++)
      {
         mp[adsPerson->personArray[i].m_Name[j]].push_back(i);
      }
   }
}

//全屏窗口
void full_screen()
{
   HWND hwnd = GetForegroundWindow();
   int cx = GetSystemMetrics(SM_CXSCREEN);
   int cy = GetSystemMetrics(SM_CYSCREEN);

   LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);
   SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);

   SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, 0);
}
