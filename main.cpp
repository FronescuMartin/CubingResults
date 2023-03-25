#include <iostream>
#include <cstring>
#include <cmath>
#include "cubing.h"
using namespace std;

String::String(){
    str=new char[1];
    str[0]='\0';
}
String::String(char* input){
    str=new char[strlen(input)+1];
    strcpy(str, input);
    str[strlen(input)]='\0';
}
String::String(const String &s){
    str=new char[strlen(s.str)+1];
    strcpy(str, s.str);
    str[strlen(s.str)]='\0';
}

String& String::operator =(const String &s){
    delete[] str;
    str=new char[strlen(s.str)+1];
    strcpy(str, s.str);
    str[strlen(s.str)]='\0';
    return *this;
}

char* String::findStr(const char ch[]){
    char *p=strstr(this->str, ch);
    return p;
}


String::~String(){
    delete[] str;
}
String String::operator + (const String &s2){
    //cout<<(strlen(s2.str));
    char *tmp_str=new char[strlen(str)+strlen(s2.str)+1];
    strncpy(tmp_str, str, strlen(str));
    strncpy(tmp_str+strlen(str), s2.str, strlen(s2.str));
    strcpy(tmp_str+(strlen(str)+strlen(s2.str)),"\0");
    String tmp(tmp_str);
    delete[] tmp_str;
    //cout<<tmp_str<<'\n';
    return tmp;
}

String String::operator + (char ch){
    //cout<<(strlen(s2.str));
    char chv[2];
    chv[0]=ch;
    char *tmp_str=new char[strlen(str)+2];
    strncpy(tmp_str, str, strlen(str));
    strcpy(tmp_str+strlen(str), chv);
    strcpy(tmp_str+(strlen(str)+1),"\0");
    String tmp(tmp_str);
    delete[] tmp_str;
    //cout<<tmp_str<<'\n';
    return tmp;
}
ostream& operator <<(ostream &out, String &s){
    out<<s.str;
    return out;
}
//##########COMPETITOR###########
Competitor::Competitor(String name, String country, int id, int age){
    //results=new Result*[results_len];
    this->results=nullptr;
    this->name=name;
    this->country=country;
    this->id=id;
    this->age=age;
    this->results_len=0;
    this->numberOfNRs=0;
    this->numberOfCRs=0;
    this->numberOfWRs=0;

}

Competitor::~Competitor(){
    if(results!=nullptr){
        delete[] results;
    }
}
String Competitor::getName(){
    return this->name;
}
void Competitor::setAge(int newAge){
    this->age=newAge;
}
int Competitor::numberOfRecords(){
    cout<<numberOfNRs<<' '<<numberOfCRs<<' '<<numberOfWRs<<'\n';
    return numberOfNRs+numberOfCRs+numberOfWRs;
}
void Competitor::print(){
    cout<<"Nume: "<<this->name<<'\n';
    cout<<"Tara: "<<this->country<<'\n';
    cout<<"Numar Recorduri: "<<this->numberOfRecords()<<'\n';
    for(int i=0; i<results_len; i++){
        results[i].print();
    }
}
void Competitor::addResultData(Events event, double _times[], int length, int _rank, SingleRecordTypes recordSg, AverageRecordTypes recordAvg, int _comp_id){
    Result _result(event, _times, length, _rank, recordSg, recordAvg, _comp_id);
    Result* result2=new Result[results_len+1];
    for(int i=0; i<results_len; i++){
        result2[i]=results[i];
    }
    result2[results_len]=_result;
    delete[] results;
    results=result2;
    results_len++;
    if(recordSg==NR_Single){
        numberOfNRs++;
    }
    if(recordAvg==NR_Average){
        numberOfNRs++;
    }
    if(recordSg==CR_Single){
        numberOfCRs++;
    }
    if(recordAvg==CR_Average){
        numberOfCRs++;
    }
    if(recordSg==WR_Single){
        numberOfWRs++;
    }
    if(recordAvg==WR_Average){
        numberOfWRs++;
    }

}

void Competitor::addResults(Result _result){
    Result* result2=new Result[results_len+1];
    for(int i=0; i<results_len; i++){
        result2[i]=results[i];
    }
    result2[results_len]=_result;
    delete[] results;
    results=result2;
    results_len++;

    //results[this->indexCrt]=_results;
    //this->indexCrt++;
    //cout<<indexCrt;
}
//###########DATE############
Date::Date(int _day, Month _month, int _year){
    this->day=_day;
    this->month=_month;
    this->year=_year;
}



Date::Date(int _day, int _month, int _year){
    this->day=_day;
    this->month=_month;
    this->year=_year;
}

ostream& operator << (ostream &out, Date &d){
    if(d.day<10){
        out<<'0';
    }
    out<<d.day<<'.';
    if(d.month<10){
        out<<'0';
    }
    out<<d.month<<'.';
    out<<d.year;
    return out;

}
//###########COMPETITION#########
Competition::Competition(String _name, int _numberOfCompetitors, int _id){
    this->name=_name;
    this->numberOfCompetititors=_numberOfCompetitors;
    this->id=_id;
}

//###########RESULT############
Result::Result(Events event, double _times[], int length, int _rank, SingleRecordTypes recordSg, AverageRecordTypes recorAvg, int _comp_id){
    this->event=event;
    this->times_len=length;
    this->rankInRound=_rank;
    this->singleRecord=recordSg;
    this->averageRecord=recorAvg;
    this->competitionId=_comp_id;
    for(int i=0; i<times_len; i++){
        times[i]=_times[i];
        //cout<<_times[i]<<'\n';
    }
    //cout<<this->times[2];
    calculateAverageAndSingle();
    //this->record=record;
}
Result::Result(){
    times_len=0;
}
void Result::print(){
    for(int i=0; i<times_len; i++){
        cout<<times[i]<<' ';
    }
    cout<<'\n';
}
double Result::roundTo2DecimalPlaces(double num){
    return round(num * 100) / 100.0;
}

void Result::calculateAverageAndSingle(){
    double best=times[0], worst=times[0], sum=times[0];
    for(int i=1; i<times_len; i++){
        if(times[i]<best){
            best=times[i];
        } else if (times[i]>worst){
            worst=times[i];
        }
        sum+=times[i];
    }
    if(times_len==5){
        sum=sum-best-worst;
    }
    average=roundTo2DecimalPlaces(sum/3);
    single=best;
}
double Result::getAverage(){
    return this->average;
}

double Result::getSingle(){
    return this->single;
}


int main()
{
    double temp[5]={1.23,1.24,1.09,1.93,2.21};
    Result r(_2x2,temp, 5, 2);
    //cout<<r.getAverage()<<'\n';
    Date d(23, February, 2013);
    //cout<<d;
    //String s1("Feliks Zemdegs");
    //String s2("Australia");
    Competitor c1(String("Feliks Zemdegs"), String("Australia"), 1, 23);
    double tempTimes[5]={1.23,1.24, 1.25, 2.43, 4.53};
    double tempTimes2[5]={2.23,3.24, 1.25, 7.43, 4.53};
    double tempTimes3[5]={6.23,5.24, 1.25, 2.43, 4.53};
    double tempTimes4[5]={1.23,2.24, 1.25, 1.03, 0.93};

    //sa se aloce inauntru!!!
    c1.addResultData(_2x2, tempTimes,5,4,No_Single_Record, WR_Average, 4);
    c1.addResultData(_2x2, tempTimes2,5,4,No_Single_Record, WR_Average, 4);

    c1.print();
    //Result temp2(_2x2, tempTimes,5,4,No_Single_Record, No_Average_Record, 4);
    //Result temp3(_2x2, tempTimes,5,4,No_Single_Record, No_Average_Record, 4);
    //Result temp4(_3x3, tempTimes,5,4,NR_Single, NR_Average, 4);

    //Result* tempArr=new Result*{&temp1, &temp2, &temp3};
    //c1.addResults(temp1);
    //c1.addResults(temp2);
    //c1.addResults(temp3);
    //c1.addResults(temp4);

    //c1.addResults(&temp3);



    return 0;
}
