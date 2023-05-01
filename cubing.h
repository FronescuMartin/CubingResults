#ifndef CUBING_H_INCLUDED
#define CUBING_H_INCLUDED

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

enum TypesOfDelegate{
    SeniorDelegate, JuniorDelegate, Delegate, RegionalDelegate, CandidateDelegate
};

enum Month{
    January=1, February=2, March=3, April=4, May=5, June=6, July=7, August=8, September=9, October=10, November=11, December=12
};

class Date{
protected: //metode si date protected
    int day;
    int month;
    int year;
    Date(int _day, Month _month, int _year);
    Date(int _day, int _month, int _year);
    Date();
    void init_date(int _day, int _month, int _year);
    void print_date();
    friend ostream& operator << (ostream &out, Date &d);
};

class CompetitionInterface{
public:
    virtual void printDetailed()=0;
    virtual string typeOfCompetition()=0;
    virtual ~CompetitionInterface()=default;
};

class Competition:public Date, public CompetitionInterface{ //mostenire
private:
    string name;
    int numberOfCompetitors;
    int id;
    static int static_id;
public:
    Competition();
    Competition(string _name, int _numberOfCompetitors, int _id);
    Competition(string _name, int _numberOfCompetitors, int _day, int _month, int _year);
    ~Competition()=default;
    void init(string _name, int _numberOfCompetitors, int _id);
    void init(string _name, int _numberOfCompetitors, int _id, int _day, int _month, int _year);
    void setName(string newName);
    void setNumberOfCompetitors(int n);
    void setDifferentId(int n);
    int getId();
    string getName();
    void print();
    void printDetailed();
    string typeOfCompetition();
    static int getStaticId();
};

int Competition::static_id=0;

class Tournament:public Date, public CompetitionInterface{ //turneu in fiecare an, stil bracket
private:
    string winner, locationCountry, runnerUp;
    int numberOfCompetitors;
    vector<int> bracket; //va avea 2*numarul de participanti dimensiune, stocand tot bracket-ul in urma finalizarii
    //fiecare participant indexat de la 0 la n-1 unde n nr de participanti
    vector<string>competitors;
public:
    Tournament();
    Tournament(int day, int month, int year, string _winner, string _locationCountry, string _runnerUp, int _numberOfCompetitors, vector<int> _bracket, vector<string>_competitors);
    ~Tournament()=default;
    void printDetailed();
    string typeOfCompetition();

};

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
    double* getTimes();
    int getTimesLen();
};

class Person{
protected: //date membre protected
    string name, country;
    int age;
    Person(string name, string country, int age);
    Person();
public:
    virtual ~Person()=default;
    virtual void print()=0;
    virtual string typeOfPerson()=0;
};

class Competitor:virtual public Person{ //parte din mostenire in diamant
protected:
    int id, numberOfNRs, numberOfCRs, numberOfWRs;
    int results_len;
    Result* results;
    Result* bestResultsSingle[17];
    Result* bestResultsAverage[17];
    double averageResult[17];
    bool hasResultInEvent[17];
public:
    Competitor(string name, string country, int age);
    Competitor();
    ~Competitor();
    void addResultData(Events event, double _times[], int length, int _rank, SingleRecordTypes recordSg=No_Single_Record, AverageRecordTypes recorAvg=No_Average_Record, int _comp_id=-1);
    string getName();
    void setAge(int newAge);
    string eventNameFromEnum(int e);
    void calculateRecords();
    int getNumberOfRecords();
    void findBestResults();
    void calculateAverageResult();
    void print();
    Result* getResults();
    int getResultsLen();
    string typeOfPerson();
};

class Delegat:virtual public Person{ //parte din mostenire in diamant
protected:
    TypesOfDelegate delegateType;
    string regions;
    vector<int>competitionsDelegated; //id-urile competitiilor la care a fost delegat
public:
    Delegat(string name, string country, int age, TypesOfDelegate type, string _regions);
    Delegat();
    ~Delegat(){}
    void addCompetitionDelegated(int comp);
    void addCompetitionsDelegated(vector<int> comps);
    void print();
    string typeOfPerson();
};

class DelegatCompetitor:public Delegat, public Competitor{
private:
    DelegatCompetitor(string name, string country, int age, TypesOfDelegate type, string _regions);
    DelegatCompetitor();
public:
    static DelegatCompetitor* createInstance(string name, string country, int age, TypesOfDelegate type, string _regions); //metoda statica pentru a crea obiectul
    static DelegatCompetitor* createInstance();
    ~DelegatCompetitor(){}
    void print();
    string typeOfPerson();
};



class VectorCompetitii:private vector<CompetitionInterface*>{ //mostenire privata
public:
    using vector<CompetitionInterface*>::operator[];
    using vector<CompetitionInterface*>::size;
    using vector<CompetitionInterface*>::back;

    void add(CompetitionInterface* c);
    ~VectorCompetitii();
};


//EXCEPTII

class bad_input:public exception{
private:
    string message;
public:
    bad_input(string _message);
    const char* what() const throw();
};

#endif // CUBING_H_INCLUDED
