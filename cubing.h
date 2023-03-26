#ifndef CUBING_H_INCLUDED
#define CUBING_H_INCLUDED
#include <iostream>
using namespace std;
enum Events{
    _2x2, _3x3, _4x4, _5x5, _6x6, _7x7, Megaminx, Pyraminx, OneHanded, Blindfolded, Square_1, MultiBLD, _4BLD, _5BLD, Skewb, FewestMovesChallenge, Clock
};

enum SingleRecordTypes{
    PR_Single, NR_Single, CR_Single, WR_Single, No_Single_Record
};
enum AverageRecordTypes{
    PR_Average, NR_Average, CR_Average, WR_Average, No_Average_Record
};
class String{
    char *str;
public:
    String();
    String(char *str);
    String(const String &s);
    String(String &&s);
    ~String();
    String operator +(const String &s2);
    String& operator =(const String &s);
    String& operator =(String &&s);
    String operator + (char a);
    char* findStr(const char ch[]);
    friend ostream& operator << (ostream &out, String &s);

};

enum Month{
    January=1, February=2, March=3, April=4, May=5, June=6, July=7, August=8, September=9, October=10, November=11, December=12
};

class Date{
private:
    int day;
    int month;
    int year;
public:
    Date(int _day, Month _month, int _year);
    Date(int _day, int _month, int _year);
    friend ostream& operator << (ostream &out, Date &d);
};
class Competition;

class Result{
private:

    Events event;
    double times[5];
    int times_len;
    double single, average;

    SingleRecordTypes singleRecord;
    AverageRecordTypes averageRecord;
    Competition* competition;
    int competitionId;
    int rankInRound;
public:
    Result();
    Result(const Result &r);
    Result operator=(const Result& r);
    Result(Events event, double _times[], int length, int _rank, SingleRecordTypes recordSg=No_Single_Record, AverageRecordTypes recorAvg=No_Average_Record, int _comp_id=-1);
    void print();
    void calculateAverageAndSingle();
    double getAverage();
    double getSingle();
    void getCompetitionFromCompetitionId();
    SingleRecordTypes getSingleRecord();
    AverageRecordTypes getAverageRecord();
    Events getEvent();
    double roundTo2DecimalPlaces(double num);
    //getCompetitionPointerFromId;
};

class Competitor{
private:
    String name, country;
    int id, numberOfNRs, numberOfCRs, numberOfWRs, age;
    int results_len;
    Result* results;
    int indexCrt=0;
    Result* bestResultsSingle[17];
    Result* bestResultsAverage[17];
    bool hasResultInEvent[17];

public:
    Competitor(String name, String country, int age);
    Competitor();
    ~Competitor();
    //void init();
    void addResultData(Events event, double _times[], int length, int _rank, SingleRecordTypes recordSg=No_Single_Record, AverageRecordTypes recorAvg=No_Average_Record, int _comp_id=-1);
    String getName();
    void setAge(int newAge);
    String eventNameFromEnum(int e);
    void calculateRecords();
    int getNumberOfRecords();
    void findBestResults();
    void print();

};



class Competition{
private:
    String name;
    //Date date;
    int numberOfCompetititors;
    int id;
public:
    Competition();
    Competition(String &&_name, int _numberOfCompetitors, int _id);
    void init(String _name, int _numberOfCompetitors, int _id);
    int getId();
    String getName();
    void print();

};





#endif // CUBING_H_INCLUDED
