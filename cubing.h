#ifndef CUBING_H_INCLUDED
#define CUBING_H_INCLUDED
#include <iostream>
using namespace std;

class String{
    char *str;
public:
    String();
    String(char *str);
    String(const String &s);
    //void print();
    ~String();
    String operator +(const String &s2);
    String& operator =(const String &s);
    String operator + (char a);
    char* findStr(const char ch[]);
    friend ostream& operator << (ostream &out, String &s);

};

class Competitor{
private:
    String name, country;
    int id, numberOfNRs, numberOfCRs, numberOfWRs, age;
    //Result results[];
    //Competition competitions[];
    //Result bestResults;
public:
    Competitor(String name, String country, int id, int age);
    String getName();
    void setAge(int newAge);
    int numberOfRecords();
    void print();

};
class Result{
private:
    enum Events{
        _2x2, _3x3, _4x4, _5x5, _6x6, _7x7, Megaminx, Pyraminx, OneHanded, Blindfolded, Square_1, MultiBLD, _4BLD, _5BLD, Skewb, FewestMovesChallenge, Clock,
    };
    Events event;
    double *times;
    int times_len;
    double single, average;
    enum RecordTypes{
        NR_Single, NR_Average, CR_Single, CR_Average, WR_Single, WR_Average, No_Record
    };
    RecordTypes record;
    //Competition* competition;
    int rankInRound;
public:
    Result(/*Events event,*/double times[], int length, int _rank/*, RecordTypes record*/);
    ~Result();
    void calculateAverageAndSingle();
    double getAverage();
    double getSingle();
    double roundTo2DecimalPlaces(double num);

};

#endif // CUBING_H_INCLUDED
