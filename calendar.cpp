#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <windows.h>
#include <filesystem>

using namespace std;

int a[12][7][6];

int DayWeek(int Day, int Month, int Year) {
 int DaysInYears, AllDays, DaysInMonths, Weeks, DayWeek;
 if (Month < 3) {
 Month = Month+12;
 Year = Year-1;
}
 Month = Month+1;
 DaysInMonths = Month*30.6; 
 DaysInYears = Year*365.25; 
 AllDays = DaysInMonths+DaysInYears+Day-114;
 Weeks = AllDays/7; 
 DayWeek = AllDays - Weeks*7;
 if (DayWeek == 0) DayWeek = 7;
 return DayWeek;
}
int month = 0, year = 0;
bool no_file = true;
char * wrong_month, * wrong_year;
ofstream fout;
char path[100]="";

bool file_is_exist(std::string filePath)
{
    bool isExist = false;
    std::ifstream fin(filePath.c_str());
 
    if(fin.is_open())
        isExist = true;
 
    fin.close();
    return isExist;
}

bool fileparser(){	
	if (strlen(path) == 0){
		cout << "do you want write calendar in file? /yes /no" << endl;
		char ans[5] = "";
		cin >> ans;
		if (strcmp(ans, "/yes") == 0){
			cout << "input path to file:" << endl;
			cin >> path;
		}
		else if (strcmp(ans, "/no") == 0){
			cout << "file wont be create" << endl;
			return true;	
		}
		else{
			cout << "wrong input, restart programm" << endl;
			exit(3);
		}
	}
	//bool exist = std::filesystem::exists(path);
	if (file_is_exist(path)){
		cout << "your file exists you want rewrite it? /yes /no" << endl;
		char ans1[5] = "";
		cin >> ans1;
		if (strcmp(ans1, "/yes") == 0)
			return false;
		else if (strcmp(ans1, "/no") == 0)
			return true; 
		else{
			cout << "wrong input, restart programm" << endl;
			exit(1);
		}                                  
	}
	else{
		cout << "file will be create" << endl;
		fout.open(path);
		if (!fout.is_open()){
			cout << "wrong path to file, restart programm" << endl;
			exit(2);
		}                               
		else{
			return false;
		}
	}
}

int main(int narg, char *argc[]){
	setlocale(LC_ALL,"Rus");
	setlocale(LC_CTYPE,"rus");                              
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	if ((narg > 8) or (narg < 2)){
		//cout << "???????????????? -info ???????? ???????????? ???????????? ?????? ???????????????????????? ????????????????????" << endl;
		cout << "write /info if you want to know how to use calendar" << endl;
		char info[10] = "";
		cin >> info;
		if (strcmp(info, "/info") == 0){
			//cout << "???????????? ???????????????? ??????????: /M 3 ???????????? ???????????????? ??????: /Y 2003 " << endl;
			cout << "first parametr month: /M 3"<< endl;
			cout << "second parametr year: /Y 2003 " << endl;
			cout << "third parametr file: /F ... " << endl;
			cout << "thank you for using my calendar, yours zmil-17";
			exit(1);
		}
		else
			exit(2);
	}
//???????????????????? ?? ???????????????? ???????????? ???? ????????????
	for (int i = 0; i < narg; i++){
		if (strcmp(argc[i], "/M") == 0)
			if (i + 1 < narg){
				month = atoi(argc[i + 1]);
				wrong_month = argc[i + 1];
			}
		if (strcmp(argc[i], "/Y") == 0)
			if (i + 1 < narg){
					year = atoi(argc[i + 1]);
					wrong_year = argc[i + 1];	
				}
		if (strcmp(argc[i], "/F") == 0)
			if (i + 1 < narg){
				strcpy(path, argc[i + 1]);
			}				
	}
	if ((month > 12) or (month < 1)){
		if (year)
		cout << "i read the month: " << wrong_month <<endl;
		cout << "input again";
		exit(3);
	}
	if (!year){
		cout << "i read the year: " << wrong_year <<endl;
		cout << "input again";
		exit(4);
	}
//?????????????????? ?? ???????????????????????? ?????????? ???? ?????? ???????? ?? ???????????? ?????? 
	no_file = fileparser();
	month--;
	int savemonth = month;
	int begin = DayWeek(1, month+1, year);
//?????????????????? ???????????????????? ???? ??????
	int Feb;
	if (((year % 4 == 0) and (year % 100 == 0) and (year % 400 == 0)) or ((year % 4 == 0) and (year % 100 != 0)) 
		or ((year % 4 == 0) and (year % 1000 == 0)))
		Feb = 29;
	else
		Feb = 28;
//???????????? ???????????? ???????????????? ???????? ?? ??????????????
	const char days[7][11] = {"monday", "tuesday" , "wednesday" , "thursday" , "friday" , "saturday" , "sunday"};
	const char months[12][11] = {"january" , "february" , "march" , "april" , 
					"may" , "june" , "july" , "august" ,
					"september" , "october" , "november" , "december"};
	int dayslong[12] = {31, Feb, 31, 30, 
						31, 30, 31, 31,	
						30, 31, 30, 31};
// ???????????????????? ??????????????
	for (int i = 0; i < 12; i++){
		int chislo = 0;
		for(int k = begin - 1; k < 7; k++){
			chislo += 1;
			a[i][k][0] = chislo;
		}
		for (int k = 1; k < 6; k++)
			for (int j = 0; j < 7; j++){
				if (chislo >= dayslong[month]){
					a[i][j][k] = 0;
					continue;
				}
				chislo += 1;
				a[i][j][k] = chislo;
			}
		month++;
		if (month > 11){
			year++;
			month = 0;
		}
		begin = DayWeek(1, month+1, year);
	}	
// ?????????? ??????????????????
	cout << endl << endl;
	for (int i = 0; i < 12; i += 4){
		if (savemonth > 11)
			savemonth = 0;
		cout << "                          " << months[savemonth++] << "     ";
		for(int j = 0; j < 3; j++){
			if (savemonth > 11)
				savemonth = 0;
			cout << setw(37) << right << months[savemonth++]; 
		}
		cout << endl << endl;
		for (int k = 0; k < 7; k++){
			cout << setw(15) << left << days[k];
			for (int j = 0; j < 4; j++){
				for (int p = 0; p < 6; p++){
					if (a[i + j][k][p] != 0){
						cout << setw(2) << a[i + j][k][p]; 
						cout << "    ";
					}
					else{
						cout << "      ";
					}
				}
				cout << "    ";
			}
			cout << '\n';
		}
		cout << '\n';
	}
//???????????? ?? ???????? ???????? no_file = false
	if (!no_file)
	{
		fout.close();
		fout.open(path);
		for (int i = 0; i < 12; i += 4){
			if (savemonth > 11)
				savemonth = 0;
			fout << "                          " << months[savemonth++] << "     ";
			for(int j = 0; j < 3; j++){
				if (savemonth > 11)
					savemonth = 0;
				fout << setw(37) << right << months[savemonth++];
			}
			fout << endl << endl;
			for (int k = 0; k < 7; k++){
				fout << setw(15) << left << days[k];
				for (int j = 0; j < 4; j++){
					for (int p = 0; p < 6; p++){
						if (a[i + j][k][p] != 0){
							fout << setw(2) << a[i + j][k][p]; 
							fout << "    ";
						}
						else{
							fout << "      ";
						}
					}
					fout << "    ";
				}
				fout << '\n';
			}
			fout << '\n';
	}
	fout.close();
	}
	return 0;
}
