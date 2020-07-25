#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

void Print_data(string (name)[100],float earn,float tax1,float tax2,float year_status,float result);
void Input_data_person(string (&name)[100],float &wage,float &hour,int &allow,char (&marital)[5],float &year_status);//it's function returns values to main function as links
void calculate_results(float wage,float hour,int allow,char (marital)[5],float &year_status,float &earn,float &tax2,float &tax1,float &result);//"year_status" reference to annual income
void Federaltax_M(int *allow,float *earn,float *ptrtax1,float *ptrtax2,float *year_status);//sub-functions "calculate_results"
void Federaltax_S(int *allow,float *earn,float *ptrtax1,float *ptrtax2,float *year_status);

int main()
{
    float hours,wage,year_status,earn,tax1,tax2,result;
    string name[100];
    char marital[5];
    int allow;
    Input_data_person(name,wage,hours,allow,marital,year_status);
    calculate_results(wage,hours,allow,marital,year_status,earn,tax2,tax1,result);
    Print_data(name,earn,tax1,tax2,year_status,result);
    return 0;
}

void Input_data_person(string(&name)[100],float &wage,float &hour,int &allow,char (&marital)[5],float &year_status)
{
    cout << "Name: ";
    cin>>*name;
    cout << "Hourly Wage:";
    cin>>wage;
    cout << "Hours worked:";
    cin>>hour;
    cout << "Withholding Allowances:";
    cin>>allow;
    cout << "Marital status:";
    cin>>marital;
    cout << "Year-to-date:";
    cin>>year_status;
}

void calculate_results(float wage,float hour,int allow,char (marital)[5],float &year_status,float &earn,float &tax2,float &tax1,float &result)//Tax1-FICA tax,Tax2-Income Tax withheld
{
    earn=hour*wage;
    year_status=year_status+earn;//add current earnings to annual income
    tax2=earn-80.6*allow;//subtract from current earnings with withholding allowance(for sub-functions)
    if(marital[0]=='M')
    {
        Federaltax_M(&allow,&earn,&tax1,&tax2,&year_status);//sub-function call
    }
    else if(marital[0]=='S')
    {
      Federaltax_S(&allow,&earn,&tax1,&tax2,&year_status);
    }
    tax1=round(tax1*100.0)/100.0;
    tax2=round(tax2*100.0)/100.0;
    result=earn-tax1-tax2;//Amount of check
}

void Federaltax_M(int *allow,float *earn,float *ptrtax1,float *ptrtax2,float *year_status)
{
    if(*year_status<132900)
   *ptrtax1=*earn*0.062;//FICA tax

   else if(*year_status>=132900)
    *ptrtax1=0;

   if(*ptrtax2<227)//Income tax withheld
    *ptrtax2=0;

   else if(*ptrtax2>=227&&*ptrtax2<600)
       *ptrtax2=(*ptrtax2-227)*0.1;

   else if(*ptrtax2>=600&&*ptrtax2<1745)
    *ptrtax2=(*ptrtax2-600)*0.12+37.3;

   else if(*ptrtax2>=1745&&*ptrtax2<3469)
    *ptrtax2=(*ptrtax2-1745)*0.22+174.7;

   else if(*ptrtax2>=3469&&*ptrtax2<6409)
    *ptrtax2=(*ptrtax2-3469)*0.24+553.1;

   else if(*ptrtax2>=6409&&*ptrtax2<8077)
    *ptrtax2=(*ptrtax2-6409)*0.32+1259.66;

    else if(*ptrtax2>=8077&&*ptrtax2<12003)
    *ptrtax2=(*ptrtax2-8077)*0.35+1793.42;

    else if(*ptrtax2>=12003)
    *ptrtax2=(*ptrtax2-12003)*0.37+3167.52;


}

void Federaltax_S(int *allow,float *earn,float *ptrtax1,float *ptrtax2,float *year_status)
{
    *ptrtax1=*earn*0.062;
   if(*ptrtax2<73)
    *ptrtax2=0;

   else if(*ptrtax2>=73&&*ptrtax2<260)
       *ptrtax2=(*ptrtax2-73)*0.1;

   else if(*ptrtax2>=260&&*ptrtax2<832)
    *ptrtax2=(*ptrtax2-260)*0.12+18.7;

   else if(*ptrtax2>=832&&*ptrtax2<1692)
    *ptrtax2=(*ptrtax2-832)*0.22+87.34;

   else if(*ptrtax2>=1692&&*ptrtax2<3164)
    *ptrtax2=(*ptrtax2-1692)*0.24+276.54;

   else if(*ptrtax2>=3164&&*ptrtax2<3998)
    *ptrtax2=(*ptrtax2-3164)*0.32+629.82;

    else if(*ptrtax2>=3998&&*ptrtax2<9887)
    *ptrtax2=(*ptrtax2-3998)*0.35+896.7;

    else if(*ptrtax2>=9887)
    *ptrtax2=(*ptrtax2-9887)*0.37+2957.85;

}

void Print_data(string (name)[100],float earn,float tax1,float tax2,float year_status,float result)
{
    cout << "___________________________" << endl;
    cout << "Name: " << *name << endl;
    cout << "Current Earnings: "  << earn << endl;
    cout << "Year-to-date: " << year_status << endl;
    cout << "FICA tax: " << tax1 << endl;
    cout << "Income Tax Withheld: " << tax2 << endl;
    cout << "Amount of check: " << result << endl;
    cout << "___________________________";

}

