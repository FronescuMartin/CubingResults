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
    const int day;
    const int month;
    const int year;
    Date(const int _day, const Month _month, const int _year);
    Date(const int _day, const int _month, const int _year);
    Date();
    void init_date(const int _day, const int _month, const int _year);
    void print_date();
    friend ostream& operator << ( ostream &out, const Date &d);
};

//design pattern abstract factory
class CompetitionInterface{ //interfata
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
    Competition(const string _name, const int _numberOfCompetitors, const int _id);
    Competition(const string _name, const int _numberOfCompetitors, const int _day, const int _month, const int _year);
    ~Competition()=default;
    void init(const string _name, const int _numberOfCompetitors, const int _id);
    void init(const string _name, const int _numberOfCompetitors, const int _id, const int _day, const int _month, const int _year);
    void setName(const string newName);
    void setNumberOfCompetitors(const int n);
    void setDifferentId(const int n);
    int getId();
    string getName();
    void print();
    void printDetailed();
    string typeOfCompetition();
    static int getStaticId(); //metoda statica, returneaza data statica
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
    Tournament(const int day, const int month, const int year, const string _winner, const string _locationCountry, const string _runnerUp, const int _numberOfCompetitors, const vector<int> _bracket, const vector<string>_competitors);
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
    shared_ptr<Competition> competition;
    int competitionId;
    int rankInRound;
public:
    Result();
    Result(reference_wrapper<const Result> r);
    Result operator=(const Result& r);
    Result(const Events event, const double _times[], const int length, const int _rank, const SingleRecordTypes recordSg=No_Single_Record, const AverageRecordTypes recorAvg=No_Average_Record, const int _comp_id=-1);
    void print();
    void calculateAverageAndSingle();
    double getAverage();
    double getSingle();
    void getCompetitionFromCompetitionId();
    SingleRecordTypes getSingleRecord();
    AverageRecordTypes getAverageRecord();
    Events getEvent();
    double roundTo2DecimalPlaces(const double num);
    double* getTimes();
    int getTimesLen();
};

//design pattern abstract factory
class Person{ //clasa abstracta
protected: //date membre protected
    string name, country;
    int age;
    Person(const string name, const string country, const int age);
    Person();
public:
    virtual ~Person()=default;
    virtual void printDetailed()=0;
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
    Competitor(const string name, const string country, const int age);
    Competitor();
    ~Competitor();
    void addResultData(const Events event, const double _times[], const int length, const int _rank, const SingleRecordTypes recordSg=No_Single_Record, const AverageRecordTypes recorAvg=No_Average_Record, const int _comp_id=-1);
    string getName();
    void setAge(const int newAge);
    string eventNameFromEnum(int e);
    void calculateRecords();
    int getNumberOfRecords();
    void findBestResults();
    void calculateAverageResult();
    void printDetailed();
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
    Delegat(const string name, const string country, const int age, const TypesOfDelegate type, const string _regions);
    Delegat();
    ~Delegat(){}
    void addCompetitionDelegated(const int comp);
    void addCompetitionsDelegated(const vector<int> comps);
    void printDetailed();
    string typeOfPerson();
};

//design pattern static factory method
class DelegatCompetitor:public Delegat, public Competitor{
private:
    DelegatCompetitor(const string name, const string country, const int age, const TypesOfDelegate type, const string _regions);
    DelegatCompetitor();
public:
    static DelegatCompetitor* createInstance(const string name, const string country, const int age, const TypesOfDelegate type, const string _regions); //metoda statica pentru a crea obiectul
    static DelegatCompetitor* createInstance();
    ~DelegatCompetitor(){}
    void printDetailed();
    string typeOfPerson();
};


template<typename T>
class VectorObiecte:private vector<T>{ //mostenire privata
public:
    using vector<T>::operator[];
    using vector<T>::size;
    using vector<T>::back;
    void add(const T c);
};


//EXCEPTII

class bad_input:public exception{
private:
    string message;
public:
    bad_input(const string _message);
    const char* what() const throw();
};

//singleton design pattern
class Menu{
private:
    Menu();
public:
    static Menu& getInstance() {
        static Menu instance;
        return instance;
    }
    void afisare();
};

#endif // CUBING_H_INCLUDED
