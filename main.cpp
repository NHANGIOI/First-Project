#include <iostream>
#include <windows.h>
#include <fstream>
#include <filesystem>
#include <ctime>
#include <string>
#define FOR(i,a,b)	for(int i=(a);i<=(b);i++)
#define FORD(i,a,b)	for(int i=(a);i>=(b);i--)
#define endl '\n'
using namespace std;
void setwindowsize(short width,short height){
	HANDLE hStdout=GetStdHandle(STD_OUTPUT_HANDLE);
	
	SMALL_RECT WindowSize;
	WindowSize.Top=0;
	WindowSize.Left=0;
	WindowSize.Right=width;
	WindowSize.Bottom=height;
	
	SetConsoleWindowInfo(hStdout,1, &WindowSize);
}
void setbuffersize(short width,short weight){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD newSize;
    newSize.X = width; 
    newSize.Y = weight;
    SetConsoleScreenBufferSize(hConsole, newSize);
}
void banchangesize(){
	HWND hWnd = GetConsoleWindow();
    SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
}
void ShowScrollbar(BOOL Show){
    HWND hWnd = GetConsoleWindow();
    ShowScrollBar(hWnd, SB_BOTH, Show);
}
void init(){
	setwindowsize(60,15);
	setbuffersize(60,15);
	banchangesize();
	ShowScrollbar(0);
}
struct date{
		int hour,day,month,year;
	};
date check_day(int &part_money){
	int ko_nhuan[12]={31,59,90,120,151,181,212,243,273,304,334,365};
	int nhuan[12]={31,60,91,121,152,182,213,244,274,305,335,366};
	ifstream fin("C:/Users/Public/SMMS/data.txt");
	//get time now
	time_t currentTime = time(NULL);
    string currentTimeString = ctime(&currentTime);
	tm *timeinfo = std::localtime(&currentTime);
	date now;	now.hour=timeinfo->tm_hour;	now.day=timeinfo->tm_mday;	now.month=timeinfo->tm_mon+1;	now.year=timeinfo->tm_year+1900;
	date part,root;	
	fin>>part.hour>>part.day>>part.month>>part.year;
	fin>>part_money;
	fin.close();
	root.hour=0;root.day=1;root.month=1;root.year=part.year;
	//logic
	int time_part,time_now;//số h mà tại thời điểm part và now tính từ root
	if(part.year%4!=0){
		time_part=part.hour+part.day*24+ko_nhuan[part.month-1]*24;
		time_now=now.hour+now.day*24+ko_nhuan[now.month-1]*24+(now.year-part.year)*8783;
	}else{
		time_part=part.hour+part.day*24+nhuan[part.month-1]*24;
		time_now=now.hour+now.day*24+nhuan[now.month-1]*24+(now.year-part.year)*8784;
	}
	//cout<<endl<<time_part<<" "<<time_now;
	if((time_now-time_part)<24)	exit(0);
	else{
		now.hour=16;
		return now;
	}
}
void check_file(){
	filesystem::path directoryPath("C:/Users/Public/SMMS");
	if(!(filesystem::is_directory(directoryPath))){
		try {
			filesystem::create_directory(directoryPath);
			} catch (const std::filesystem::filesystem_error& e) {
			cerr << "error: " << e.what() << endl;
			exit(0);
    	}
	}
	ifstream fileExist("C:/Users/Public/SMMS/data.txt");
	if(!(fileExist.good())){
		ofstream file_create("C:/Users/Public/SMMS/data.txt");
		if(file_create.is_open()){
			file_create<<16<<" "<<1<<" "<<1<<" "<<2023<<endl<<0;
		}else	cerr<<"error in create new file data"<<endl,exit(0);
	}
}
signed main() 
{
	int money;
	check_file();
	date temp_date=check_day(money);
	init();
	cout<<endl<<endl;
	FOR(i,1,14)	cout<<" ";	cout<<"Savings Money Management Sotfware"; 	FOR(i,1,13)	cout<<" ";	cout<<endl;
	FOR(i,1,28)	cout<<"=";	cout<<"SMMS"; 	FOR(i,1,28)	cout<<"=";	cout<<endl;
	FOR(i,1,14)	cout<<" ";	cout<<"HOW MUCH MONEY DO YOU HAVE TODAY?"; 	FOR(i,1,13)	cout<<" ";	cout<<endl<<endl;
	//cout<<"==========================================================="<<endl;
	cout<<"      PUT IN : PRESS S       ==      PUT OUT : PRESS R      "<<endl;
	char choose;
	while(true){
		cout<<endl<<"input:";cin>>choose;
		if((choose=='S')||(choose=='s')||(choose=='R')||(choose=='r'))	break;
		cout<<"Press wrong PLS try again";
	}
	FOR(i,1,60)	cout<<"=";	cout<<endl;
	int tempm;
	
	if(choose=='S'||choose=='s'){
		while(true){
			cout<<"Enter the amount send:";	cin>>tempm;
			char check_sure;
			cout<<"Are you sure(Y|N):";	cin>>check_sure;
			if(check_sure=='Y'||check_sure=='y')	break;
		}
		money+=tempm;
	}else{
		while(true){
			cout<<"Enter the amount received:";	cin>>tempm;
			char check_sure;
			cout<<"Are you sure(Y|N):";	cin>>check_sure;
			if(check_sure=='Y'||check_sure=='y')	break;
		}
		money-=tempm;
	}
	ofstream fout("C:/Users/Public/SMMS/data.txt");
	fout<<temp_date.hour<<" "<<temp_date.day<<" "<<temp_date.month<<" "<<temp_date.year<<endl;
	fout<<money;
	FOR(i,1,60)	cout<<"=";	cout<<endl;
	cout<<"Account savings money balance: "<<money<<endl;
	cout<<"money repair for phone: "<<money-64<<endl;
	system("pause");
	fout.close();
	//cout<<"=                                                          ="<<endl;
	return 0;
}
