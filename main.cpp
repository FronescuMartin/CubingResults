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
    //cout<<tmp_str<<'\n';
    return tmp;
}
ostream& operator <<(ostream &out, String &s){
    out<<s.str;
    return out;
}
//##########COMPETITOR###########
Competitor::Competitor(String name, String country, int id, int age){
    this->name=name;
    this->country=country;
    this->id=id;
    this->age=age;
}
String Competitor::getName(){
    return this->name;
}
void Competitor::setAge(int newAge){
    this->age=newAge;
}
int Competitor::numberOfRecords(){
    return numberOfNRs+numberOfCRs+numberOfWRs;
}
void Competitor::print(){
    cout<<"Nume: "<<this->name<<'\n';
    cout<<"Tara: "<<this->country<<'\n';
    cout<<"Numar Recorduri: "<<this->numberOfRecords()<<'\n';
}

//###########RESULT############
Result::Result(/*Events event, */double _times[], int length, int _rank/*, RecordTypes record*/){
    //this->event=event;
    this->times_len=length;
    this->times=new double[times_len];
    this->rankInRound=_rank;
    for(int i=0; i<times_len; i++){
        times[i]=_times[i];
        cout<<_times[i]<<'\n';
    }
    //cout<<this->times[2];
    calculateAverageAndSingle();
    //this->record=record;
}

double Result::roundTo2DecimalPlaces(double num){
    return round(num * 100) / 100;
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

Result::~Result(){
    delete[] times;
}

int main()
{
    double temp[5]={1.23,1.24,1.09,1.93,2.21};
    Result r(temp, 5, 2);
    cout<<r.getAverage();

    return 0;
}
