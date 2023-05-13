#include <iostream>
#include <cstring>
#include <cmath>
#include <iomanip>
#include <vector>
#include <cstring>
#include <exception>
#include <algorithm>
#include <functional>
#include <memory>
#include <thread>
#include "cubing.h"
using namespace std;

//vector <Competition*> compList;
VectorObiecte<shared_ptr<CompetitionInterface>>compList;
//vector declarat global deoarece orice obiect Competitor trebuie sa aiba acces la lista de competitii,
//deoarece fiecare competitor are in vectorul de rezultate un pointer catre competitia la care
//s-a obtinut acel rezultat

//########## PERSON ##########

/*bool any_of_custom(vector<int>v, function<bool(int)> f){ //implementare de functie care primeste o functie lambda ca parametru
    //returneaza true daca functia f aplicata pe oricare element din vector returneaza true
    //altfel returneaza falses
    for(int i=0; i<v.size(); i++){
        if(f(v[i])){
            return true;
        }
    }
    return false;
}*/

Person::Person(const string _name, const string country, const int age){
    if(age==-1){
        throw bad_input("Inputul dat nu este un numar");
    }
    this->name=_name;
    this->country=country;
    this->age=age;

}
Person::Person(){
    this->name="";
    this->country="";
    this->age=-1;
}
//########## COMPETITOR ###########

Competitor::Competitor(){ //constructorul fara parametru, seteaza valori default
    this->results=nullptr;
    this->name="";
    this->country="";
    this->results_len=0;
    this->numberOfNRs=0;
    this->numberOfCRs=0;
    this->numberOfWRs=0;
    for(int i=0; i<17; i++){
        hasResultInEvent[i]=false; //initializarea vectorului care spune daca concurentul are vreun rezultat in proba respectiva
    }
}
Competitor::Competitor(const string _name, const string country, const int age):Person(_name, country, age){ //constructor cu parametri
    this->results=nullptr;
    //this->name=name;
    //this->country=country;
    //this->age=age;
    this->results_len=0;
    this->numberOfNRs=0;
    this->numberOfCRs=0;
    this->numberOfWRs=0;
    for(int i=0; i<17; i++){
        hasResultInEvent[i]=false; //initializarea vectorului care spune daca concurentul are vreun rezultat in proba respectiva
    }
}

Competitor::~Competitor(){ //destructor
    if(results!=nullptr){
        delete[] results;
    }
}
string Competitor::getName(){
    return this->name;
}
void Competitor::setAge(const int newAge){
    this->age=newAge;
}


void Competitor::calculateRecords(){
    //calculeaza numarul de recorduri (NR=national record, CR=continental record, WR=world record)
    //parcurgand vectorul de rezultate din cadrul unui competitor, si numarand fiecare aparitie a unui enum
    //de tip record, fie el la average, fie la single.
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
    return numberOfNRs+numberOfCRs+numberOfWRs;
}

string Competitor::eventNameFromEnum(const int e){ //functia primeste un enum de fapt, dar valoarea e transmisa ca intreg
    if(e==0) return "2x2";
    if(e==1) return "3x3";
    if(e==2) return "4x4";
    if(e==3) return "5x5";
    if(e==4) return "6x6";
    if(e==5) return "7x7";
    if(e==6) return "Megaminx";
    if(e==7) return "Pyraminx";
    if(e==8) return "One Handed";
    if(e==9) return "Blindfolded";
    if(e==10) return "Square-1";
    if(e==11) return "Multi-Blind";
    if(e==12) return "4x4 Blindfolded";
    if(e==13) return "5x5 Blindfolded";
    if(e==14) return "Skewb";
    if(e==15) return "Fewest Moves Challenge";
    if(e==16) return "Clock";
}
void Competitor::printDetailed(){
    cout<<"Nume: "<<this->name<<'\n';
    cout<<"Tara: "<<this->country<<'\n';
    cout<<"Numar Recorduri: "<<this->getNumberOfRecords()<<'\n';
    cout<<"Toate Rezultatele:\n";
    for(int i=0; i<results_len; i++){
        string tmp=eventNameFromEnum(results[i].getEvent());
        cout<<tmp<<": ";
        results[i].print();
    }
    cout<<"Cele mai bune rezultate obtinute: "<<'\n';
    //hasResultInEvent contine true doar daca concurentul are un rezultat in proba respectiva, il folosim
    //pentru a nu intra in elemente din vector nealocate, neexistand valori

    for(int i=0; i<17; i++){
        if(hasResultInEvent[i]==true){
            string tmp=eventNameFromEnum(i);
            cout<<tmp<<' ';
            cout<<"Single: ";
            float temp=bestResultsSingle[i]->getSingle();
            if(temp<60){
                cout<<temp<<' ';
            } else {
                int mins=floor(temp/60);
                double seconds=temp-mins*60;
                cout<<mins<<':';
                if(seconds<10){
                    cout<<'0';
                }
                cout<<round(seconds*100)/100.0<<' ';
            }
            cout<<" Average: ";
            temp=bestResultsAverage[i]->getAverage();
            if(temp<60){
                cout<<fixed<<setprecision(2)<<temp<<' ';
            } else {
                int mins=floor(temp/60);
                double seconds=temp-mins*60;
                cout<<mins<<':';
                if(seconds<10){
                    cout<<'0';
                }
                cout<<fixed<<setprecision(2)<<round(seconds*100)/100.0<<' ';
            }
            cout<<'\n';
        }
    }
    cout<<'\n';
    cout<<"Timpul mediu pentru fiecare proba:\n";
    for(int i=0; i<17; i++){
        if(hasResultInEvent[i]==true){
            string tmp=eventNameFromEnum(i);
            cout<<tmp<<": ";
            float temp=averageResult[i];
            if(temp<60){
                cout<<temp<<' ';
            } else {
                int mins=floor(temp/60);
                double seconds=temp-mins*60;
                cout<<mins<<':';
                if(seconds<10){
                    cout<<'0';
                }
                cout<<round(seconds*100)/100.0<<' ';
            }
            cout<<'\n';
        }
    }
    cout<<"#################################\n\n";
}
void Competitor::addResultData(const Events event, const double _times[], const int length, const int _rank, const SingleRecordTypes recordSg, const AverageRecordTypes recordAvg, const int _comp_id){
    //functia va adauga in results un nou rezultat cu datele transmise prin argumentele functiei
    //results este alocat dinamic, deci trebuie sa se aloce o noua zona de memorie pentru a stoca atat datele
    //deja existente cat si noul obiect rezultat.
    Result _result(event, _times, length, _rank, recordSg, recordAvg, _comp_id);
    Result* result2=new Result[results_len+1];
    for(int i=0; i<results_len; i++){
        result2[i]=results[i];
    }
    result2[results_len]=_result;
    //results deja pointa catre o zona de memorie, care acum nu mai este folosita, asa ca trebuie dealocata
    //pentru a evita memory leak
    delete[] results;
    results=result2;
    results_len++;
}

void Competitor::findBestResults(){
    for(int i=0; i<17; i++){ //Verifica pentru toate cele 17 probe cele mai bune rezultate (i va fi proba respectiva, chiar daca aceasta este enum in mod normal, valoarea implicita a ei este intreg.
        double bestSingle=-1, bestAverage=-1;
        for(int j=0; j<results_len; j++){
            if(results[j].getEvent()==i){
                hasResultInEvent[i]=true;
                //e important sa stim daca exista rezultat pentru proba respectiva pentru a nu accesa memorie nealocata
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

void Competitor::calculateAverageResult(){ //calculeaza rezultatul mediu al concurentului pentru fiecare proba
    for(int i=0; i<17; i++){ //pentru toate cele 17 probe
        int numOfTimes=0;
        double sum=0;
        for(int j=0; j<results_len; j++){
            if(results[j].getEvent()==i){
                double *temp=results[j].getTimes();
                int len=results[j].getTimesLen();
                for(int k=0; k<len; k++){
                    sum+=temp[k];
                    numOfTimes++;
                }
            }
        }
        averageResult[i]=sum/numOfTimes;
    }
}

//getteri deoarece datele membre sunt private
Result* Competitor::getResults(){
    return results;
}
int Competitor::getResultsLen(){
    return results_len;
}

string Competitor::typeOfPerson(){
    return "Competitor";
}

//##########DELEGAT###########
Delegat::Delegat(const string _name, const string country, const int age, const TypesOfDelegate type, const string _regions):Person(_name, country, age){
    this->delegateType=type;
    this->regions=_regions;
}
Delegat::Delegat():Person(){
    this->regions="";
}
void Delegat::addCompetitionDelegated(const int comp){
    this->competitionsDelegated.push_back(comp);
}
void Delegat::addCompetitionsDelegated(const vector<int> comps){
    for(int i=0; i<comps.size(); i++){
        this->competitionsDelegated.push_back(comps[i]);
    }
}
void Delegat::printDetailed(){
    cout<<"Nume: "<<this->name<<'\n';
    if(delegateType==SeniorDelegate){
        cout<<"Delegat Senior"<<'\n';
    } else if(delegateType==JuniorDelegate){
        cout<<"Delegat Junior"<<'\n';
    } else if(delegateType==CandidateDelegate){
        cout<<"Delegat Candidat"<<'\n';
    } else if(delegateType==RegionalDelegate){
        cout<<"Delegat Regional"<<'\n';
    } else if(delegateType==Delegate){
        cout<<"Delegat"<<'\n';
    }
    cout<<"Regiune Delegata: "<<regions<<'\n';
    cout<<"Tara: "<<this->country<<'\n';
    cout<<"#################################\n\n";

}

string Delegat::typeOfPerson(){
    return "Delegate";
}

//#########DelegateCompetitor
DelegatCompetitor::DelegatCompetitor(const string _name, const string country, const int age, const TypesOfDelegate type, const string _regions){
    this->delegateType=type;
    this->regions=_regions;
    this->name=_name;
    this->country=country;
    this->age=age;
}
DelegatCompetitor::DelegatCompetitor():Delegat(), Competitor(){}
void DelegatCompetitor::printDetailed(){
    cout<<"Nume: "<<this->name<<'\n';
    if(delegateType==SeniorDelegate){
        cout<<"Delegat Senior"<<'\n';
    } else if(delegateType==JuniorDelegate){
        cout<<"Delegat Junior"<<'\n';
    } else if(delegateType==CandidateDelegate){
        cout<<"Delegat Candidat"<<'\n';
    } else if(delegateType==RegionalDelegate){
        cout<<"Delegat Regional"<<'\n';
    } else if(delegateType==Delegate){
        cout<<"Delegat"<<'\n';
    }
    cout<<"Regiune Delegata: "<<regions<<'\n';

    cout<<"Tara: "<<this->country<<'\n';
    cout<<"Numar Recorduri: "<<this->getNumberOfRecords()<<'\n';
    cout<<"Toate Rezultatele:\n";
    for(int i=0; i<results_len; i++){
        string tmp=eventNameFromEnum(results[i].getEvent());
        cout<<tmp<<": ";
        results[i].print();
    }
    cout<<"Cele mai bune rezultate obtinute: "<<'\n';
    //hasResultInEvent contine true doar daca concurentul are un rezultat in proba respectiva, il folosim
    //pentru a nu intra in elemente din vector nealocate, neexistand valori

    for(int i=0; i<17; i++){
        if(hasResultInEvent[i]==true){
            string tmp=eventNameFromEnum(i);
            cout<<tmp<<' ';
            cout<<"Single: ";
            float temp=bestResultsSingle[i]->getSingle();
            if(temp<60){
                cout<<temp<<' ';
            } else {
                int mins=floor(temp/60);
                double seconds=temp-mins*60;
                cout<<mins<<':';
                if(seconds<10){
                    cout<<'0';
                }
                cout<<round(seconds*100)/100.0<<' ';
            }
            cout<<" Average: ";
            temp=bestResultsAverage[i]->getAverage();
            if(temp<60){
                cout<<fixed<<setprecision(2)<<temp<<' ';
            } else {
                int mins=floor(temp/60);
                double seconds=temp-mins*60;
                cout<<mins<<':';
                if(seconds<10){
                    cout<<'0';
                }
                cout<<fixed<<setprecision(2)<<round(seconds*100)/100.0<<' ';
            }
            cout<<'\n';
        }
    }
    cout<<'\n';
    cout<<"Timpul mediu pentru fiecare proba:\n";
    for(int i=0; i<17; i++){
        if(hasResultInEvent[i]==true){
            string tmp=eventNameFromEnum(i);
            cout<<tmp<<": ";
            float temp=averageResult[i];
            if(temp<60){
                cout<<temp<<' ';
            } else {
                int mins=floor(temp/60);
                double seconds=temp-mins*60;
                cout<<mins<<':';
                if(seconds<10){
                    cout<<'0';
                }
                cout<<round(seconds*100)/100.0<<' ';
            }
            cout<<'\n';
        }
    }
    cout<<"#################################\n\n";
}

DelegatCompetitor* DelegatCompetitor::createInstance(const string name, const string country, const int age, const TypesOfDelegate type, const string _regions){
    try{
        return new DelegatCompetitor(name, country, age, type, _regions);
        //return new DelegatCompetitor[1000000000000000000]; //pentru a testa exceptia rearuncata
    } catch (bad_alloc& e){
        cerr<<"Nu s-a putut aloca: "<<e.what()<<'\n';
        runtime_error r("Aceasta persoana nu a putut fi adaugata deoarece nu s-a putut aloca spatiu\n");
        throw r; //arunca o exceptie runtime pentru a fi tratata in main
    }
}

DelegatCompetitor* DelegatCompetitor::createInstance(){
    return new DelegatCompetitor();
}
string DelegatCompetitor::typeOfPerson(){
    return "Delegate Competitor";
}

//###########DATE############
Date::Date(const int _day, const Month _month, const int _year):day(_day), month(_month), year(_year){ //constructor cu parametri
    /*this->day=_day;
    this->month=_month;
    this->year=_year;*/
}

Date::Date():day(0), month(0), year(0){ //constructor fara parametri, seteaza valori implicite
    /*this->day=0;
    this->month=0;
    this->year=0;*/
}

Date::Date(const int _day, const int _month, const int _year):day(_day), month(_month), year(_year){ //constructor echivalent, dar care primeste int in loc de enum pentru luna, in caz ca e nevoie
    //este apelat de Competition prin lista de initializare
}
/*void Date::init_date( const int _day, const int _month, const int _year):day(_day), month(_month), year(_year){ //initializeaza datele in caz ca e nevoie sa se apeleze constructorul gol,
    //deoarece inca nu sunt cunoscute datale initiale
}*/

ostream& operator << (ostream &out, const Date &d){ //operatorul << supraincarcat, pentru cout
    if(d.day<10){
        out<<'0'; //pentru formatare
    }
    out<<d.day<<'.';
    if(d.month<10){
        out<<'0'; //pentru formatare
    }
    out<<d.month<<'.';
    out<<d.year;
    return out;
}

void Date::print_date(){
    if(day<10){
        cout<<'0'; //pentru formatare
    }
    cout<<day<<'.';
    if(month<10){
       cout<<'0'; //pentru formatare
    }
    cout<<month<<'.';
    cout<<year;
    cout<<'\n';
}

//###########COMPETITION############
Competition::Competition(const string _name, const int _numberOfCompetitors, const int _day, const int _month, const int _year):Date(_day, _month, _year){ //apeleaza constructorul din Date prin lista de initializare.
    //constructor cu parametri
    this->name=_name;
    this->numberOfCompetitors=_numberOfCompetitors;
    this->id=getStaticId();
    this->static_id++;
}
Competition::Competition(){
    //constructor fara parametri, seteaza valorile implicite
    this->name="";
    this->numberOfCompetitors=-1;
    this->id=-1;
}

/*void Competition::init(const string _name, const int _numberOfCompetitors, const int _id){
    //este apelat init in cazul in care se face un vector de obiecte, si atunci initial nu se pot transmite parametrii
    this->name=_name;
    this->numberOfCompetitors=_numberOfCompetitors;
    this->id=_id;
}*/

/*void Competition::init(const string _name, const int _numberOfCompetitors, const int _id, const int _day, const int _month, const int _year){
    //la fel ca mai sus, dar in cazul in care se transmite si data competitiei
    this->name=_name;
    this->numberOfCompetitors=_numberOfCompetitors;
    this->id=_id;
    init_date(_day, _month, _year);
}*/

//getteri pentru datele membre private
int Competition::getId(){
    return this->id;
}
string Competition::getName(){
    return this->name;
}

void Competition::print(){
    //printul acesta e apelat in cadrul unui rezultat, pentru a mentiona la ce competitie este obtinut
    cout<<this->name;
}

void Competition::printDetailed(){
    //printul acesta e apelat in cadrul meniului interactiv, la adaugarea unui obiect de timp Competition
    cout<<"Nume: "<<this->name<<'\n';
    cout<<"Numar concurenti: "<<numberOfCompetitors<<'\n';
    cout<<"Data: ";
    print_date(); //apeleaza metoda protected din Date.
    cout<<"\n";
}

//setteri pentru datele membre private
//sunt folositi in cadrul meniului interactiv
void Competition::setName(const string newName){
    this->name=newName;
}

void Competition::setNumberOfCompetitors(const int n){
    this->numberOfCompetitors=n;
}
void Competition::setDifferentId(const int n){
    //verifica daca acest id nu e deja folosit.
    vector<int>tempIndexes;
    for(int i=0; i<compList.size(); i++){
        shared_ptr<Competition> tempPtr=dynamic_pointer_cast<Competition>(compList[i]);
        if(tempPtr){
            tempIndexes.push_back(tempPtr->getId());
        }
    }
    //any_of din <algorithm>
    if(any_of(tempIndexes.begin(), tempIndexes.end(), [n](int y){ return n==y;})){ //functie lambda care verifica daca un element este egal cu n
        throw bad_input("Deja exista o competitie cu acest id");
    } else {
        //daca id-ul nu e deja folosit:
        this->id=n;
    }
}
string Competition::typeOfCompetition(){
    return "WCA Competition";
}

int Competition::getStaticId(){
    return static_id;
}

//########### TOURNAMENT ##############
Tournament::Tournament(const int day, const int month, const int year, const string _winner, const string _locationCountry, const string _runnerUp, const int _numberOfCompetitors, const vector<int> _bracket, const vector<string>_competitors):Date(day, month, year){
    winner=_winner;
    locationCountry=_locationCountry;
    runnerUp=_runnerUp;
    numberOfCompetitors=_numberOfCompetitors;
    bracket=_bracket;
    competitors=_competitors;
}
Tournament::Tournament():Date(){
    winner="";
    runnerUp="";
    numberOfCompetitors=-1;
}
void Tournament::printDetailed(){
    cout<<"Turneul Mondial din "<<year<<'\n';
    cout<<"Numar participanti: "<<numberOfCompetitors<<'\n';
    cout<<"Castigatorul turneului a fost "<<winner<<'\n';
    cout<<"\n";
}

string Tournament::typeOfCompetition(){
    return "Tournament";
}

//########### RESULT ############
Result::Result(const Events event, const double _times[], const int length, const int _rank, const SingleRecordTypes recordSg, const AverageRecordTypes recorAvg, const int _comp_id){
    //constructorul cu parametri
    if(length>5){
        throw bad_input("Nu pot fi mai mult de 5 timpi intr-un rezultat"); //arunca exceptie
    } else if (length<=0){
        throw bad_input("Trebuie sa fie cel putin un timp");
    }
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
Result::Result(){ //constructorul fara parametri
    times_len=0;
}

Result::Result(reference_wrapper<const Result> r){ //constructorul de copiere
    event=r.get().event;
    //times=r.times;
    times_len=r.get().times_len;
    for(int i=0; i<times_len; i++){
        times[i]=r.get().times[i];
    }
    single=r.get().single;
    average=r.get().average;
    singleRecord=r.get().singleRecord;
    averageRecord=r.get().averageRecord;
    competition=r.get().competition;
    rankInRound=r.get().rankInRound;
}

Result Result::operator=(const Result& r){ //operatorul=de copiere supraincarcat
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
    //afiseaza timpii din cadrul obiectului Result
    //realizeaza formatare pentru a afisa corect timpii de peste 1 minut
    //scriind timpii in minute:secunde.sutimi in loc de secunde.sutimi
    //de asemenea afiseaza toti timpii cu 2 zecimale, chiar si in cazul timpilor de forma 2.00 pentru a nu arata 2
    for(int i=0; i<times_len; i++){
        if(times[i]<60){
            cout<<fixed<<setprecision(2)<<times[i]<<' ';
        } else {
            int mins=floor(times[i]/60);
            double seconds=times[i]-mins*60;
            cout<<mins<<':';
            if(seconds<10){
                cout<<'0';
            }
            cout<<fixed<<setprecision(2)<<round(seconds*100)/100.0<<' ';
        }
    }

    cout<<'\n';
    cout<<"Competition: ";
    string tmp=competition->getName();
    cout<<tmp<<'\n'; //polimorfism deoarece ofstream mosteneste ostream care mosteneste ios etc?
}
double Result::roundTo2DecimalPlaces(const double num){
    return round(num * 100) / 100.0;
    //aproximeaza rezultatele la 2 zecimale, folosit pentru calcularea mediei
}

SingleRecordTypes Result::getSingleRecord(){
    return singleRecord;
}
AverageRecordTypes Result::getAverageRecord(){
    return averageRecord;
}

void Result::getCompetitionFromCompetitionId(){
    bool found=false;
    for(int i=0; i<compList.size(); i++){
        shared_ptr<Competition> tempPtr=dynamic_pointer_cast<Competition>(compList[i]);
        if(tempPtr){
            if(tempPtr->getId()==this->competitionId){
                this->competition=tempPtr;
                found=true;
            }
        }
    }
    if(!found){
        throw bad_input("Nu exista competitie cu acest id"); //arunca exceptie
    }
}

void Result::calculateAverageAndSingle(){
    //single reprezinta cel mai bun rezultat din cele 3 sau 5 din cadrul rezultatului
    //average reprezinta media celor 3 timpi mijlocii in cazul probelor cu 5 timpi
    //sau media celor 3 timpi in cazul probelor cu 3 timpi
    double sum=times[0];
    const double best=*min_element(times,times+times_len); //functie din algorithm
    const double worst=*max_element(times, times+times_len); //functie din algorithm
    for(int i=1; i<times_len; i++){
        sum+=times[i];
    }
    if(times_len==5){
        sum=sum-best-worst; //in cazul probelor cu 5 rezultate, se scade timpul cel mai rapid cat si cel mai lent
    }
    average=roundTo2DecimalPlaces(sum/3); //aproximarea deoarece in baza de date totul este stocat cu 2 zecimale
    single=best;
}

//getteri pentru datele membru
double Result::getAverage(){
    return this->average;
}

double Result::getSingle(){
    return this->single;
}
Events Result::getEvent(){
    return this->event;
}

double* Result::getTimes(){
    return this->times;
}

int Result::getTimesLen(){
    return this->times_len;
}

template<typename T>
void VectorObiecte<T>::add(const T c){
    this->push_back(c);
}



bad_input::bad_input(const string _message){
    message=_message;
}
const char* bad_input::what() const throw(){
    return this->message.c_str();
}

template <typename T>
void print_list(reference_wrapper<T> _list){
    for(int i=0; i<_list.get().size(); i++){
        _list.get()[i]->printDetailed();
    }
}

//specializare
void print_list(vector<int> v){
    for(int i=0; i<v.size(); i++){
        cout<<v[i]<<' ';
    }
    cout<<'\n';
}


Menu::Menu(){}

void Menu::afisare(){
    VectorObiecte<shared_ptr<Person>> people;
    compList.add(make_shared<Competition>("Markham 3x3x3 Morning 2023", 115, 29, 4, 2023));
    compList.add(make_shared<Competition>("Canberra Autumn 2018", 108,21,4,2018));
    compList.add(make_shared<Competition>("Australian Nationals 2018", 199,6,10,2018));
    compList.add(make_shared<Competition>("Odd Day in Sydney 2019", 142,10,11,2019));
    compList.add(make_shared<Competition>("Turn Around Tassie 2020", 68,12,12,2020));
    compList.add(make_shared<Competition>("Brilliant Ballarat 2023", 140,25,2,2023));
    compList.add(make_shared<Competition>("Circle City Summer 2022",77,6,8,2022));
    compList.add(make_shared<Competition>("Arizona Speedcubing Spring 2023", 110,19,3,2023));
    compList.add(make_shared<Competition>("Bay Area Speedcubin' 29 PM 2022", 117,3,4,2022));
    //date pentru testarea claselor implementate
    //Feliks Zemdegs
    thread thread1([&]() { //rulare paralela folosind thread-uri
        Competitor *c1=new Competitor("Feliks Zemdegs", "Australia", 27);

        double Feliks_2x2_1[5]={1.92, 2.88, 1.70, 2.39, 1.56};
        double Feliks_2x2_2[5]={4.46, 1.42, 1.78, 1.42, 1.32};
        double Feliks_3x3_1[5]={7.16, 5.04, 4.67, 6.55, 4.99};
        double Feliks_OneHanded_1[5]={11.21, 7.69, 9.18, 8.64, 13.42};
        double Feliks_7x7_1[5]={118.18, 130.09, 113.62};





        c1->addResultData(_2x2, Feliks_2x2_1,5,2,No_Single_Record, No_Average_Record, 4);
        c1->addResultData(_2x2, Feliks_2x2_2,5,1,No_Single_Record, CR_Average, 0);
        c1->addResultData(_3x3, Feliks_3x3_1,5,1,No_Single_Record, WR_Average, 2);
        c1->addResultData(OneHanded, Feliks_OneHanded_1,5,1,No_Single_Record, CR_Average, 3);
        c1->addResultData(_7x7, Feliks_7x7_1,3,1,CR_Single, CR_Average, 1);

        c1->calculateRecords();
        c1->findBestResults();
        c1->calculateAverageResult();
        people.add(shared_ptr<Person>(c1)); //upcasting
    });

    thread thread2([&]() {

        //John Doe
        Delegat *delegate1=new Delegat("John Doe", "Bulgaria", 43, SeniorDelegate, "Europa");
        people.add(shared_ptr<Person>(delegate1)); //upcasting

        //Max Park
        Competitor *c2=new Competitor("Max Park", "USA", 21);




        double Max_3x3_1[5]={3.63, 5.52, 5.66, 5.37, 5.22};
        double Max_4x4_1[5]={17.60, 18.49, 19.37, 23.80, 20.28};
        double Max_4x4_2[5]={16.79, 26.52, 22.85, 20.01, 17.56};

        c2->addResultData(_3x3, Max_3x3_1,5,1,WR_Single, No_Average_Record, 5);
        c2->addResultData(_4x4, Max_4x4_1,5,1,No_Single_Record, WR_Average, 6);
        c2->addResultData(_4x4, Max_4x4_2,5,1,WR_Single, No_Average_Record, 7);

        c2->calculateRecords();
        c2->findBestResults();
        c2->calculateAverageResult();
        people.add(shared_ptr<Person>(c2)); //upcasting
    });
    thread thread3([&]() {

        //Sarah Strong
        try{
            DelegatCompetitor* dc1=DelegatCompetitor::createInstance("Sarah Strong", "Canada", 27, Delegate, "Canada");
            //apelare metoda statica care creaza obiectul
            double Sarah_3x3_1[5]={12.49, 15.14, 13.67, 11.42, 11.46};
            dc1->addResultData(_3x3, Sarah_3x3_1,5, 22, No_Single_Record, No_Average_Record, 8);

            dc1->calculateRecords();
            dc1->findBestResults();
            dc1->calculateAverageResult();
            people.add(shared_ptr<Person>(dc1)); //upcasting
            //people.back()->print();
        } catch(runtime_error &e){
            cerr<<"Eroare: "<<e.what()<<'\n';
        }
    });
    thread1.join();
    thread2.join();
    thread3.join();


    for(int i=0; i<people.size(); i++){
        people[i]->printDetailed(); //polimorfism la executie (people[i] este de tip Person*,
        // elementele pot fi de tipul clasei derivate
    }

    CompetitionInterface *t1=new Tournament(2,1,2013, "Feliks Zemdegs", "USA", "Mats Valk", 4, {0,1,2,3,1,2,2}, {"Rowe Hessler", "Mats Valk", "Feliks Zemdegs", "Sebastian Weyer"}); //upcasting
    CompetitionInterface *t2=new Tournament(5,7,2017, "Feliks Zemdegs", "USA", "Max Park", 4, {0,1,2,3,0,2,0}, {"Feliks Zemdegs", "Mats Valk", "Max Park", "Philipp Weyer"}); //upcasting
    compList.add(shared_ptr<CompetitionInterface>(t1));
    compList.add(shared_ptr<CompetitionInterface>(t2));

    cout<<"Lista de competitii si turnee:\n";
    for(int i=0; i<compList.size(); i++){
        compList[i]->printDetailed(); //polimorfism la executie
    }
    int numberOfWcaCompetitions=0, numberOfTournaments=0;
    for(int i=0; i<compList.size(); i++){
        if(compList[i]->typeOfCompetition()=="WCA Competition"){ //polimorfism la executie
            numberOfWcaCompetitions++;
        } else if (compList[i]->typeOfCompetition()=="Tournament"){ //polimorfism la executie
            numberOfTournaments++;
        }
    }
    cout<<"Numarul de competitii WCA este "<<numberOfWcaCompetitions<<" iar numarul de turnee este "<<numberOfTournaments<<'\n';
    //################# MENIUL INTERACTIV ##################
    int userInput=1;
    cout<<"\nMeniu\n";
    while(userInput!=0){
        cout<<"Apasati:\n1 pentru a adauga un obiect nou,\n2 pentru a afisa toate persoanele,\n3 pentru a afisa toate competitiile (de orice tip),\n0 pentru a termina executia ";
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
                string numeTemp(tmp);
                cout<<"Tara competitorului: ";
                cin>>tmp2;
                string taraTemp(tmp2);
                cout<<"Varsta competitorului: ";
                cin>>age;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    age=-1;
                }
                try{
                    people.add(shared_ptr<Person>(new Competitor(numeTemp, taraTemp, age))); //upcasting

                    cout<<"Apasati 2 pentru a afisa acest concurent, 3 pentru a adauga un rezultat apeland functia addResultData, 0 pentru a va intoarce la meniul principal\n";
                    cin>>userInput;
                    if(userInput==2){
                        people.back()->printDetailed();
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
                        for(int i=0; i<compList.size(); i++){
                            Competition* tempPtr=dynamic_cast<Competition*>(compList[i].get());
                            if(tempPtr){
                                cout<<tempPtr->getId()<<". ";
                                tempPtr->print();
                                cout<<'\n';
                            }
                        }
                        int compId;
                        cin>>compId;
                        Competitor* tempPtr=dynamic_cast<Competitor*>(people.back().get()); //downcasting
                        try{
                            tempPtr->addResultData(proba,times,times_len,__rank,sgRecord,avgRecord,compId);
                            tempPtr->findBestResults();
                            tempPtr->calculateAverageResult();

                            cout<<"Apasati 2 pentru a afisa acest concurent in urma actualizarii\n";
                            cin>>userInput;
                            if(userInput==2){
                                people.back()->printDetailed();
                            }
                        } catch(bad_input& e){
                            cerr<<"Eroare: "<<e.what()<<'\n';
                        }
                    }
                } catch (bad_input &e){
                    cerr<<"Eroare: "<<e.what()<<'\n';
                }
            } else if(userInput==2){
                cout<<"La care competitor doriti sa adaugati rezultatul?\n";
                vector<Competitor*> actualCompetitors; //vector cu persoanele care sunt chiar concurenti (trebuie schimbat numele vectorului initial).
                for(int i=0; i<people.size(); i++){
                    Competitor* tempPtr=dynamic_cast<Competitor*>(people[i].get()); //downcasting
                    if(people[i]->typeOfPerson()=="Competitor"){ //polimorfism la executie
                        actualCompetitors.push_back(tempPtr);
                    }
                }
                for(int i=0; i<actualCompetitors.size(); i++){
                    string tmp=actualCompetitors[i]->getName();
                    cout<<i<<". "<<tmp;
                    cout<<'\n';
                }
                int indexCompetitor;
                cin>>indexCompetitor;
                if(indexCompetitor<0 or indexCompetitor>=actualCompetitors.size()){
                    cerr<<"Index invalid\n";
                    continue;
                }
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
                for(int i=0; i<compList.size(); i++){
                    Competition* tempPtr=dynamic_cast<Competition*>(compList[i].get());
                    if(tempPtr){
                        cout<<tempPtr->getId()<<". ";
                        tempPtr->print();
                        cout<<'\n';
                    }
                }
                int compId;
                cin>>compId;
                try{
                    actualCompetitors[indexCompetitor]->addResultData(proba,times,times_len,__rank,sgRecord,avgRecord,compId);
                    actualCompetitors[indexCompetitor]->findBestResults();
                    actualCompetitors[indexCompetitor]->calculateAverageResult();
                    cout<<"Apasati 2 pentru a afisa acest concurent in urma actualizarii, sau 3 pentru a afisa single-ul si average-ul acestui rezultat ";
                    cin>>userInput;
                    if(userInput==2){
                        actualCompetitors[indexCompetitor]->printDetailed();
                    } else if(userInput==3){
                        //competitors[indexCompetitor].getResults()[competitors[indexCompetitor].getResultsLen()-1].calculateAverageAndSingle();
                        cout<<"Single: "<<actualCompetitors[indexCompetitor]->getResults()[actualCompetitors[indexCompetitor]->getResultsLen()-1].getSingle()<<" Average: "<<actualCompetitors[indexCompetitor]->getResults()[actualCompetitors[indexCompetitor]->getResultsLen()-1].getAverage()<<'\n';
                    }
                } catch(bad_input& e){
                    cerr<<"Eroare: "<<e.what()<<'\n';
                }
            } else if(userInput==3){
                cout<<"Introduceti numele competitiei pe care vreti sa o adaugati ";
                char compName[50];
                cin.get();
                cin.getline(compName,50);
                string compNameStr(compName);
                cout<<"Cati competitori au participat? ";
                int nrCompetitori;
                cin>>nrCompetitori;
                int tempLen=compList.size()-1;
                /*while(compList[tempLen]->typeOfCompetition()!="WCA Competition"){
                    tempLen--;
                } //cautam competitia de tip wca competition cu id-ul cel mai mare, pentru a genera urmatorul id
                int id=dynamic_cast<Competition*>(compList[tempLen])->getId()+1;*/
                cout<<"Introduceti data competitiei, ziua luna an (numere cu spatiu intre ele) ";
                int zi, luna, an;
                cin>>zi>>luna>>an;
                compList.add(make_shared<Competition>(compNameStr,nrCompetitori, zi, luna, an));
                cout<<"Apasati 2 pentru a afisa aceasta competitie\n3 pentru a modifica numele\n4 pentru a modifica numarul de concurenti\n5 pentru a seta un alt id\n";
                cin>>userInput;
                if(userInput==2){
                    dynamic_cast<Competition*>(compList[compList.size()-1].get())->printDetailed();
                } else if(userInput==3){
                    cout<<"Introduceti numele nou ";
                    cin.get();
                    cin.getline(compName,50);
                    string compNameStr2(compName);
                    dynamic_cast<Competition*>(compList[compList.size()-1].get())->setName(compNameStr2);
                    cout<<"Apasati 2 pentru a afisa competitia ";
                    cin>>userInput;
                    if(userInput==2){
                        dynamic_cast<Competition*>(compList[compList.size()-1].get())->printDetailed();
                    }
                } else if(userInput==4){
                    cout<<"Introduceti numarul de concurenti ";
                    cin>>userInput;
                    dynamic_cast<Competition*>(compList.back().get())->setNumberOfCompetitors(userInput);
                    cout<<"Apasati 2 pentru a afisa competitia ";
                    cin>>userInput;
                    if(userInput==2){
                        dynamic_cast<Competition*>(compList.back().get())->printDetailed();
                    }
                } else if(userInput==5){
                    cout<<"Atentie, id-ul trebuie sa fie diferit fata de cele deja existente in baza de date:\n";
                    for(int i=0; i<compList.size(); i++){
                        Competition* tempPtr=dynamic_cast<Competition*>(compList[i].get());
                        if(tempPtr){
                            cout<<tempPtr->getId()<<". ";
                            tempPtr->print();
                            cout<<'\n';
                        }
                    }
                    cout<<"Introduceti noul id ";
                    cin>>userInput;
                    try{
                        dynamic_cast<Competition*>(compList.back().get())->setDifferentId(userInput);
                        cout<<"Apasati 2 pentru a afisa competitia ";
                        cin>>userInput;
                        if(userInput==2){
                            dynamic_cast<Competition*>(compList.back().get())->printDetailed();
                        }
                    } catch(bad_input &e){
                        cerr<<"Eroare: "<<e.what()<<'\n';
                    }
                }
            }
        }
        else if(userInput==2){
            //afiseaza toate persoanele
            cout<<"Lista de persoane:\n";
            print_list(ref(people));
            /*for(int i=0; i<people.size(); i++){
                people[i]->printDetailed(); //polimorfism la executie (people[i] este de tip Person*,
            // elementele pot fi de tipul clasei derivate
            }*/
        } else if (userInput==3){
            //afiseaza toate competitiile, de orice tip
            cout<<"Lista de competitii si turnee:\n";
            print_list(ref(compList));
            /*for(int i=0; i<compList.size(); i++){
                compList[i]->printDetailed(); //polimorfism la executie
            }*/
        }
    }
    //dezalocare persoane
    //nu mai e nevoie deoarece acum people este de tip VectorObiecte care are destructor
    /*for(int i=0; i<people.size(); i++){
        delete people[i]; //se apeleaza destructorul virtual (people[i] poate fi fie *Competitor,
        //fie *Delegat, fie *DelegatComepetitor, toate acestea fiind clase derivate,
        //dar person[i] continand pointer de tip *Person.
    }*/
}

int main()
{
    Menu menu=Menu::getInstance();
    menu.afisare();
    Menu menu2=Menu::getInstance();

    return 0;
}
