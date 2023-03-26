#include <iostream>
#include <cstring>
#include <cmath>
#include "cubing.h"
using namespace std;

Competition *compList=new Competition[100];
int numberOfComps=0;


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
    //str[strlen(s.str)]='\0';
}
String::String(String &&s){ //constructor de mutare
    str=s.str;
    s.str=nullptr;
}
String& String::operator =(String &&s){ //operator= de mutare
    str=s.str;
    s.str=nullptr;
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

Competitor::Competitor(){
    this->results=nullptr;
    this->name=String("");
    this->country=String("");
    this->results_len=0;
    this->numberOfNRs=0;
    this->numberOfCRs=0;
    this->numberOfWRs=0;
    for(int i=0; i<17; i++){
        hasResultInEvent[i]=false; //initializarea vectorului care spune daca concurentul are vreun rezultat in proba respectiva
    }
}
//##########COMPETITOR###########
Competitor::Competitor(String name, String country, int age){
    //results=new Result*[results_len];
    this->results=nullptr;
    this->name=name;
    this->country=country;
    this->age=age;
    this->results_len=0;
    this->numberOfNRs=0;
    this->numberOfCRs=0;
    this->numberOfWRs=0;
    for(int i=0; i<17; i++){
        hasResultInEvent[i]=false; //initializarea vectorului care spune daca concurentul are vreun rezultat in proba respectiva
    }
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


void Competitor::calculateRecords(){
    numberOfNRs=0;
    numberOfCRs=0;
    numberOfWRs=0;

    for(int i=0; i<results_len; i++){
        if(results[i].getSingleRecord()==NR_Single){
            numberOfNRs++;
        }
        if(results[i].getAverageRecord()==NR_Average){
            numberOfNRs++;
        }
        if(results[i].getSingleRecord()==CR_Single){
            numberOfCRs++;
        }
        if(results[i].getAverageRecord()==CR_Average){
            numberOfCRs++;
        }
        if(results[i].getSingleRecord()==WR_Single){
            numberOfWRs++;
        }
        if(results[i].getAverageRecord()==WR_Average){
            numberOfWRs++;
        }

    }

}
int Competitor::getNumberOfRecords(){
    //cout<<numberOfNRs<<' '<<numberOfCRs<<' '<<numberOfWRs<<'\n';
    return numberOfNRs+numberOfCRs+numberOfWRs;
}

String Competitor::eventNameFromEnum(int e){ //functia primeste un enum de fapt, dar valoarea e transmisa ca intreg
    // Square_1, MultiBLD, _4BLD, _5BLD, Skewb, FewestMovesChallenge, Clock,
    if(e==0) return String("2x2");
    if(e==1) return String("3x3");
    if(e==2) return String("4x4");
    if(e==3) return String("5x5");
    if(e==4) return String("6x6");
    if(e==5) return String("7x7");
    if(e==6) return String("Megaminx");
    if(e==7) return String("Pyraminx");
    if(e==8) return String("One Handed");
    if(e==9) return String("Blindfolded");
    if(e==10) return String("Square-1");
    if(e==11) return String("Multi-Blind");
    if(e==12) return String("4x4 Blindfolded");
    if(e==13) return String("5x5 Blindfolded");
    if(e==14) return String("Skewb");
    if(e==15) return String("Fewest Moves Challenge");
    if(e==16) return String("Clock");
}
void Competitor::print(){
    cout<<"Nume: "<<this->name<<'\n';
    cout<<"Tara: "<<this->country<<'\n';
    cout<<"Numar Recorduri: "<<this->getNumberOfRecords()<<'\n';
    cout<<"Toate Rezultatele:\n";
    for(int i=0; i<results_len; i++){
        String tmp=eventNameFromEnum(results[i].getEvent());
        cout<<tmp<<": ";
        results[i].print();
    }
    cout<<"Cele mai bune rezultate obtinute: "<<'\n';
    for(int i=0; i<17; i++){
        if(hasResultInEvent[i]==true){
            String tmp=eventNameFromEnum(i);
            cout<<tmp<<' ';
            cout<<"Single: ";
            cout<<bestResultsSingle[i]->getSingle();
            cout<<" Average: ";
            cout<<bestResultsAverage[i]->getAverage();
        }
    }
    cout<<'\n';
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
}

void Competitor::findBestResults(){
    for(int i=0; i<17; i++){ //Verifica pentru toate cele 17 probe cele mai bune rezultate
        double bestSingle=-1, bestAverage=-1;
        for(int j=0; j<results_len; j++){
            if(results[j].getEvent()==i){
                hasResultInEvent[i]=true;
                if(results[j].getSingle()<bestSingle || bestSingle==-1){
                    bestResultsSingle[i]=&results[j];
                    bestSingle=results[j].getSingle();
                }
                if(results[j].getAverage()<bestAverage || bestAverage==-1){
                    bestResultsAverage[i]=&results[j];
                    bestAverage=results[j].getAverage();
                }

            }
        }
    }
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
Competition::Competition(String &&_name, int _numberOfCompetitors, int _id){
    this->name=_name;
    this->numberOfCompetititors=_numberOfCompetitors;
    this->id=_id;
}
Competition::Competition(){
    this->name="";
    this->numberOfCompetititors=-1;
    this->id=-1;
}

void Competition::init(String _name, int _numberOfCompetitors, int _id){
    this->name=_name;
    this->numberOfCompetititors=_numberOfCompetitors;
    this->id=_id;
}
int Competition::getId(){
    return this->id;
}
String Competition::getName(){
    return this->name;
}

void Competition::print(){
    cout<<this->name;
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
    if(competitionId!=-1){
        getCompetitionFromCompetitionId();
    }
    //this->record=record;
}
Result::Result(){
    times_len=0;
}

Result::Result(const Result &r){
    event=r.event;
    //times=r.times;
    times_len=r.times_len;
    for(int i=0; i<times_len; i++){
        times[i]=r.times[i];
    }
    single=r.single;
    average=r.average;
    singleRecord=r.singleRecord;
    averageRecord=r.averageRecord;
    competition=r.competition;
    rankInRound=r.rankInRound;
}

Result Result::operator=(const Result& r){
    event=r.event;
    //times=r.times;
    times_len=r.times_len;
    for(int i=0; i<times_len; i++){
        times[i]=r.times[i];
    }
    single=r.single;
    average=r.average;
    singleRecord=r.singleRecord;
    averageRecord=r.averageRecord;
    competition=r.competition;
    rankInRound=r.rankInRound;
    return *this;
}



void Result::print(){
    for(int i=0; i<times_len; i++){
        cout<<times[i]<<' ';
    }
    cout<<'\n';
    cout<<"Competition: ";
    String tmp=competition->getName();
    cout<<tmp<<'\n';
}
double Result::roundTo2DecimalPlaces(double num){
    return round(num * 100) / 100.0;
}

SingleRecordTypes Result::getSingleRecord(){
    return singleRecord;
}
AverageRecordTypes Result::getAverageRecord(){
    return averageRecord;
}

void Result::getCompetitionFromCompetitionId(){
    for(int i=0; i<numberOfComps; i++){
        if(compList[i].getId()==this->competitionId){
            this->competition=&(compList[i]);
        }
    }
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
Events Result::getEvent(){
    return this->event;
}



int main()
{
    int numberOfCompetitors=0;
    double temp[5]={1.23,1.24,1.09,1.93,2.21};
    Result r(_2x2,temp, 5, 2);
    //cout<<r.getAverage()<<'\n';
    Date d(23, February, 2013);
    //cout<<d;
    //String s1("Feliks Zemdegs");
    //String s2("Australia");
    Competitor c1(String("Feliks Zemdegs"), String("Australia"), 23);
    Competitor competitors[1000];
    competitors[0]=c1;
    numberOfCompetitors++;
    double tempTimes[5]={1.23,1.24, 1.25, 2.43, 4.53};
    double tempTimes2[5]={2.23,3.24, 1.25, 7.43, 4.53};
    double tempTimes3[5]={6.23,5.24, 1.25, 2.43, 4.53};
    double tempTimes4[5]={1.23,2.24, 1.25, 1.03, 0.93};
    //Competition *comp1=new Competition("Test Cubing Open 2013", 56, 1);
    compList[0].init("Test Cubing Open 2013", 56,0);
    compList[1].init("Word Cubing Open 2013", 202,1);
    numberOfComps+=2;
    //sa se aloce inauntru!!!
    competitors[0].addResultData(_2x2, tempTimes,5,4,No_Single_Record, WR_Average, 1);
    competitors[0].addResultData(_2x2, tempTimes2,5,4,WR_Single, No_Average_Record, 2);
    competitors[0].calculateRecords();
    competitors[0].findBestResults();
    competitors[0].print();
    int userInput=1;
    cout<<"\nMeniu\n";
    while(userInput!=0){
        cout<<"Apasati 1 pentru a adauga un obiect nou, 0 pentru a termina executia ";
        cin>>userInput;
        if(userInput==1){
            cout<<"Selectati ce tip de obiect vreti sa adaugati:\n";
            cout<<"1. Competitor\n";
            cout<<"2. Result\n";
            cout<<"3. Competition\n";
            cin>>userInput;
            if(userInput==1){
                char tmp[30], tmp2[30];
                int age;
                cout<<"Numele competitorului: ";
                cin.get();
                cin.getline(tmp, 30);
                String numeTemp(tmp);
                cout<<"Tara competitorului: ";
                cin>>tmp2;
                String taraTemp(tmp2);
                cout<<"Varsta competitorului: ";
                cin>>age;
                Competitor tempCompetitor(numeTemp, taraTemp, age);
                competitors[numberOfCompetitors++]=tempCompetitor;
                cout<<"Apasati 2 pentru a afisa acest concurent, 3 pentru a adauga un rezultat apeland functia addResultData, 0 pentru a va intoarce la meniul principal\n";
                cin>>userInput;
                if(userInput==2){
                    competitors[numberOfCompetitors-1].print();
                } else if(userInput==3){
                    cout<<"La ce proba este acest rezultat?\n";
                    cout<<"Apasati numarul corespunzator:\n";
                    cout<<"0. 2x2\n";
                    cout<<"1. 3x3\n";
                    cout<<"2. 4x4\n";
                    cout<<"3. 5x5\n";
                    cout<<"4. 6x6\n";
                    cout<<"5. 7x7\n";
                    cout<<"6. Megaminx\n";
                    cout<<"7. Pyraminx\n";
                    cout<<"8. One Handed\n";
                    cout<<"9. Blindfolded\n";
                    cout<<"10. Square-1\n";
                    cout<<"11. Multi-Blind\n";
                    cout<<"12. 4x4 Blindfolded\n";
                    cout<<"13. 5x5 Blindfolded\n";
                    cout<<"14. Skewb\n";
                    cout<<"15. Fewest Moves Challenge\n";
                    cout<<"16. Clock\n";
                    cin>>userInput;
                    Events proba=static_cast<Events>(userInput); //convertire din int in enum-ul Events, pentru a putea apela functia
                    cout<<"Cati timpi?\n";
                    cin>>userInput;
                    int times_len=userInput;
                    double times[times_len];
                    cout<<"Introduceti timpii, separati prin spatiu\n";
                    for(int i=0; i<times_len; i++){
                        cin>>times[i];
                    }
                    cout<<"Pe ce loc s-a clasat concurentul cu acest rezultat?\n";
                    int __rank;
                    cin>>__rank;
                    cout<<"Single-ul din acest rezultat este vreun record?\n";
                    cout<<"0. Niciun record\n";
                    cout<<"1. NR Single\n";
                    cout<<"2. CR Single\n";
                    cout<<"3. WR Single\n";
                    cin>>userInput;
                    SingleRecordTypes sgRecord;
                    if(userInput==0){
                        sgRecord=No_Single_Record;
                    } else if(userInput==1){
                        sgRecord=NR_Single;
                    } else if(userInput==2){
                        sgRecord=CR_Single;
                    } else if(userInput==3){
                        sgRecord=WR_Single;
                    }
                    cout<<"Average-ul din acest rezultat este vreun record?\n";
                    cout<<"0. Niciun record\n";
                    cout<<"1. NR Single\n";
                    cout<<"2. CR Single\n";
                    cout<<"3. WR Single\n";
                    cin>>userInput;
                    AverageRecordTypes avgRecord;
                    if(userInput==0){
                        avgRecord=No_Average_Record;
                    } else if(userInput==1){
                        avgRecord=NR_Average;
                    } else if(userInput==2){
                        avgRecord=CR_Average;
                    } else if(userInput==3){
                        avgRecord=WR_Average;
                    }
                    cout<<"La care din aceste competitii a fost obtinut rezultatul? Daca competitia nu apare pe lista, trebuie mai intai adaugata.\n";
                    for(int i=0; i<numberOfComps; i++){
                        cout<<i<<". ";
                        compList[i].print();
                        cout<<'\n';
                    }
                    int compId;
                    cin>>compId;
                    competitors[numberOfCompetitors-1].addResultData(proba,times,times_len,__rank,sgRecord,avgRecord,compId);
                    competitors[numberOfCompetitors-1].findBestResults();
                    cout<<"Apasati 2 pentru a afisa acest concurent in urma actualizarii\n";
                    cin>>userInput;
                    if(userInput==2){
                        competitors[numberOfCompetitors-1].print();
                    }
                }
            }
        }

    }
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
