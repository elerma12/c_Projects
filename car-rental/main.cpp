#include <iostream>
#include <conio.h>
#include <fstream>
#include <windows.h>
#include <string.h>
#include <stdio>
#include <time.h>
#include <cstdlib>



using namespace std;

void customerData();
int carCount();
int custCount();
int rate(int,int);
void newCustData();
void carData();
void admin();
void user();
void menu();
void fullscreen();
void art();
void exitArt();
void newCarData();
void delCar();
void displayCar();
void existingcust();
void load ();
void load_CHECK();
void gotoxy(int ,int );
void time ();
void Boarder();
int countUser();
void tNc();
void readUserPass();
void availCar();
int countAvail();
const string currentDateTime();
const String Date();
void date();
void dispAvailCar();
void GotoXY(int , int);
void load_EXIT();
void load_UPDATE();
void newUserPass();
void password();
void resetAvail();
void showCarData();
void welcome();



struct car
{
  char plate_num[10];
  char brand[20];
  char model[20];
  float capacity;
  char colour[20];
  float rate_per_hour;
  float rate_per_half;
  float rate_per_day;
  char transmission[6];
  
};

struct customer
{
  int id;
  char name[100];
  char phone[15];
  char ic[15];
  char address[1500];
};

struct pass 
{
  int ID;
  char passWord[20];
};

 pass userPass[1000];
 car rent[1000];
 customer cust[1000];
 car avail[1000];


void fullscreen()
{
  keybd_event(VK_MENU, 0x38,0,0);
  keybd_event(VK_RETURN,0x2c,0,0);
  keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
  keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}













  

