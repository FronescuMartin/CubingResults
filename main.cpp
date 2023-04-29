#include <iostream>
#include <cstring>
#include <cmath>
#include <iomanip>
#include <vector>
#include <cstring>
#include "cubing.h"
using namespace std;

//vector <Competition*> compList;
VectorCompetitii compList;
//vector declarat global deoarece orice obiect Competitor trebuie sa aiba acces la lista de competitii,
//deoarece fiecare competitor are in vectorul de rezultate un pointer catre competitia la care
//s-a obtinut acel rezultat


String::String(){ //constructorul fara parametru pentru string, initializeaza doar caracterul nul
    str=new char[1];
    str[0]='\0';
}
String::String(char* input){ //constructor cu parametru pointer la sir de caractere
    str=new char[strlen(input)+1];
    strcpy(str, input);
    str[strlen(input)]='\0';
}
String::String(const String &s){ //constructor de copiere
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
String& String::operator =(const String &s){ //operator= de copiere
    delete[] str;
    str=new char[strlen(s.str)+1];
    strcpy(str, s.str);
    str[strlen(s.str)]='\0';
    return *this;
}

char* String::findStr(const char ch[]){ //implementare pentru strstr in clasa String
    char *p=strstr(this->str, ch);
    return p;
}


String::~String(){ //destructor
    delete[] str;
}
String String::operator + (const String &s2){ //operatorul + supraincarcat, se aloca un nou spatiu de memorie,
    // in care se copiaza continutul vechi, + continutul de la al doilea argument
    char *tmp_str=new char[strlen(str)+strlen(s2.str)+1];
    strncpy(tmp_str, str, strlen(str));
    strncpy(tmp_str+strlen(str), s2.str, strlen(s2.str));
    strcpy(tmp_str+(strlen(str)+strlen(s2.str)),"\0");
    String tmp(tmp_str);
    delete[] tmp_str; //trebuie dealocat spatiu la care pointa initial tmp_str, pentru a nu duce la memory leak
    return tmp;
}

String String::operator + (char ch){ //operatorul+ supraincarcat pentru concatenarea cu un singur caracter
    char chv[2];
    chv[0]=ch;
    char *tmp_str=new char[strlen(str)+2];
    strncpy(tmp_str, str, strlen(str));
    strcpy(tmp_str+strlen(str), chv);
    strcpy(tmp_str+(strlen(str)+1),"\0");
    String tmp(tmp_str);
    delete[] tmp_str; //trebuie dealocat spatiu la care pointa initial tmp_str, pentru a nu duce la memory leak
    return tmp;
}
ostream& operator <<(ostream &out, String &s){ //operatorul << supraincarcat pentru cout
    out<<s.str;
    return out;
}

//########## PERSON ##########

Person::Person(String _name, String country, int age){
    this->name=_name;
    this->country=country;
    this->age=age;
}
Person::Person(){
    this->name=String("");
    this->country=String("");
    this->age=-1;
}
//########## COMPETITOR ###########

Competitor::Competitor(){ //constructorul fara parametru, seteaza valori default
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
Competitor::Competitor(String _name, String country, int age):Person(_name, country, age){ //constructor cu parametri
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
String Competitor::getName(){
    return this->name;
}
void Competitor::setAge(int newAge){
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

String Competitor::eventNameFromEnum(int e){ //functia primeste un enum de fapt, dar valoarea e transmisa ca intreg
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
    //hasResultInEvent contine true doar daca concurentul are un rezultat in proba respectiva, il folosim
    //pentru a nu intra in elemente din vector nealocate, neexistand valori

    for(int i=0; i<17; i++){
        if(hasResultInEvent[i]==true){
            String tmp=eventNameFromEnum(i);
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
            String tmp=eventNameFromEnum(i);
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
void Competitor::addResultData(Events event, double _times[], int length, int _rank, SingleRecordTypes recordSg, AverageRecordTypes recordAvg, int _comp_id){
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

//##########DELEGAT###########
Delegat::Delegat(String _name, String country, int age, TypesOfDelegate type, string _regions):Person(_name, country, age){
    this->delegateType=type;
    this->regions=_regions;
}
Delegat::Delegat():Person(){
    this->regions="";
}
void Delegat::addCompetitionDelegated(int comp){
    this->competitionsDelegated.push_back(comp);
}
void Delegat::addCompetitionsDelegated(vector<int> comps){
    for(int i=0; i<comps.size(); i++){
        this->competitionsDelegated.push_back(comps[i]);
    }
}
void Delegat::print(){
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

//#########DelegateCompetitor
DelegatCompetitor::DelegatCompetitor(String _name, String country, int age, TypesOfDelegate type, string _regions){
    this->delegateType=type;
    this->regions=_regions;
    this->name=_name;
    this->country=country;
    this->age=age;
}
DelegatCompetitor::DelegatCompetitor():Delegat(), Competitor(){}
void DelegatCompetitor::print(){
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
        String tmp=eventNameFromEnum(results[i].getEvent());
        cout<<tmp<<": ";
        results[i].print();
    }
    cout<<"Cele mai bune rezultate obtinute: "<<'\n';
    //hasResultInEvent contine true doar daca concurentul are un rezultat in proba respectiva, il folosim
    //pentru a nu intra in elemente din vector nealocate, neexistand valori

    for(int i=0; i<17; i++){
        if(hasResultInEvent[i]==true){
            String tmp=eventNameFromEnum(i);
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
            String tmp=eventNameFromEnum(i);
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

//###########DATE############
Date::Date(int _day, Month _month, int _year){ //constructor cu parametri
    this->day=_day;
    this->month=_month;
    this->year=_year;
}

Date::Date(){ //constructor fara parametri, seteaza valori implicite
    this->day=0;
    this->month=0;
    this->year=0;
}

Date::Date(int _day, int _month, int _year){ //constructor echivalent, dar care primeste int in loc de enum pentru luna, in caz ca e nevoie
    //este apelat de Competition prin lista de initializare
    this->day=_day;
    this->month=_month;
    this->year=_year;
}
void Date::init_date(int _day, int _month, int _year){ //initializeaza datele in caz ca e nevoie sa se apeleze constructorul gol,
    //deoarece inca nu sunt cunoscute datale initiale
    this->day=_day;
    this->month=_month;
    this->year=_year;
}

ostream& operator << (ostream &out, Date &d){ //operatorul << supraincarcat, pentru cout
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
Competition::Competition(String _name, int _numberOfCompetitors, int _id, int _day, int _month, int _year):Date(_day, _month, _year){ //apeleaza constructorul din Date prin lista de initializare.
    //constructor cu parametri
    this->name=_name;
    this->numberOfCompetitors=_numberOfCompetitors;
    this->id=_id;
}
Competition::Competition(){
    //constructor fara parametri, seteaza valorile implicite
    this->name="";
    this->numberOfCompetitors=-1;
    this->id=-1;
}

void Competition::init(String _name, int _numberOfCompetitors, int _id){
    //este apelat init in cazul in care se face un vector de obiecte, si atunci initial nu se pot transmite parametrii
    this->name=_name;
    this->numberOfCompetitors=_numberOfCompetitors;
    this->id=_id;
}

void Competition::init(String _name, int _numberOfCompetitors, int _id, int _day, int _month, int _year){
    //la fel ca mai sus, dar in cazul in care se transmite si data competitiei
    this->name=_name;
    this->numberOfCompetitors=_numberOfCompetitors;
    this->id=_id;
    init_date(_day, _month, _year);
}

//getteri pentru datele membre private
int Competition::getId(){
    return this->id;
}
String Competition::getName(){
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
}

//setteri pentru datele membre private
//sunt folositi in cadrul meniului interactiv
void Competition::setName(String newName){
    this->name=newName;
}

void Competition::setNumberOfCompetitors(int n){
    this->numberOfCompetitors=n;
}
void Competition::setDifferentId(int n){
    this->id=n;
}

//########### RESULT ############
Result::Result(Events event, double _times[], int length, int _rank, SingleRecordTypes recordSg, AverageRecordTypes recorAvg, int _comp_id){
    //constructorul cu parametri
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

Result::Result(const Result &r){ //constructorul de copiere
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
    String tmp=competition->getName();
    cout<<tmp<<'\n';
}
double Result::roundTo2DecimalPlaces(double num){
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
    for(int i=0; i<compList.size(); i++){
        if(compList[i]->getId()==this->competitionId){
            this->competition=compList[i];
        }
    }
}

void Result::calculateAverageAndSingle(){
    //single reprezinta cel mai bun rezultat din cele 3 sau 5 din cadrul rezultatului
    //average reprezinta media celor 3 timpi mijlocii in cazul probelor cu 5 timpi
    //sau media celor 3 timpi in cazul probelor cu 3 timpi
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

void VectorCompetitii::add(Competition* c){
    this->push_back(c);
}
VectorCompetitii::~VectorCompetitii(){
    for(int i=0; i<this->size(); i++){
        delete (*this)[i];
    }
}

int main()
{
    vector<Person*> people;
    //date pentru testarea claselor implementate
    //Feliks Zemdegs
    Competitor *c1=new Competitor(String("Feliks Zemdegs"), String("Australia"), 27);

    double Feliks_2x2_1[5]={1.92, 2.88, 1.70, 2.39, 1.56};
    double Feliks_2x2_2[5]={4.46, 1.42, 1.78, 1.42, 1.32};
    double Feliks_3x3_1[5]={7.16, 5.04, 4.67, 6.55, 4.99};
    double Feliks_OneHanded_1[5]={11.21, 7.69, 9.18, 8.64, 13.42};
    double Feliks_7x7_1[5]={118.18, 130.09, 113.62};

    compList.add(new Competition("Canberra Autumn 2018", 108,0,21,4,2018));
    compList.add(new Competition("Australian Nationals 2018", 199,1,6,10,2018));
    compList.add(new Competition("Odd Day in Sydney 2019", 142,2,10,11,2019));
    compList.add(new Competition("Turn Around Tassie 2020", 68,3,12,12,2020));
    compList.add(new Competition("Brilliant Ballarat 2023", 140,4,25,2,2023));



    c1->addResultData(_2x2, Feliks_2x2_1,5,2,No_Single_Record, No_Average_Record, 4);
    c1->addResultData(_2x2, Feliks_2x2_2,5,1,No_Single_Record, CR_Average, 0);
    c1->addResultData(_3x3, Feliks_3x3_1,5,1,No_Single_Record, WR_Average, 2);
    c1->addResultData(OneHanded, Feliks_OneHanded_1,5,1,No_Single_Record, CR_Average, 3);
    c1->addResultData(_7x7, Feliks_7x7_1,3,1,CR_Single, CR_Average, 1);

    c1->calculateRecords();
    c1->findBestResults();
    c1->calculateAverageResult();
    people.push_back(c1);

    people.back()->print();

    //John Doe
    Delegat *delegate1=new Delegat(String("John Doe"), String("Bulgaria"), 43, SeniorDelegate, "Europa");
    people.push_back(delegate1);
    people.back()->print();

    //Max Park
    Competitor *c2=new Competitor(String("Max Park"), String("USA"), 21);

    compList.add(new Competition("Circle City Summer 2022",77,5,6,8,2022));
    compList.add(new Competition("Arizona Speedcubing Spring 2023", 110,6,19,3,2023));
    compList.add(new Competition("Bay Area Speedcubin' 29 PM 2022", 117,7,3,4,2022));


    double Max_3x3_1[5]={3.63, 5.52, 5.66, 5.37, 5.22};
    double Max_4x4_1[5]={17.60, 18.49, 19.37, 23.80, 20.28};
    double Max_4x4_2[5]={16.79, 26.52, 22.85, 20.01, 17.56};

    c2->addResultData(_3x3, Max_3x3_1,5,1,WR_Single, No_Average_Record, 5);
    c2->addResultData(_4x4, Max_4x4_1,5,1,No_Single_Record, WR_Average, 6);
    c2->addResultData(_4x4, Max_4x4_2,5,1,WR_Single, No_Average_Record, 7);

    c2->calculateRecords();
    c2->findBestResults();
    c2->calculateAverageResult();
    people.push_back(c2);

    people.back()->print();

    //Sarah Strong
    DelegatCompetitor* dc1=new DelegatCompetitor(String("Sarah Strong"), String("Canada"), 27, Delegate, "Canada");

    compList.add(new Competition(String("Markham 3x3x3 Morning 2023"), 115, 8, 29, 4, 2023));
    double Sarah_3x3_1[5]={12.49, 15.14, 13.67, 11.42, 11.46};
    dc1->addResultData(_3x3, Sarah_3x3_1,5, 22, No_Single_Record, No_Average_Record, 8);

    dc1->calculateRecords();
    dc1->findBestResults();
    dc1->calculateAverageResult();
    people.push_back(dc1);
    people.back()->print();

    //################# MENIUL INTERACTIV ##################
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
                people.push_back(new Competitor(numeTemp, taraTemp, age));
                cout<<"Apasati 2 pentru a afisa acest concurent, 3 pentru a adauga un rezultat apeland functia addResultData, 0 pentru a va intoarce la meniul principal\n";
                cin>>userInput;
                if(userInput==2){
                    people.back()->print();
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
                        cout<<compList[i]->getId()<<". ";
                        compList[i]->print();
                        cout<<'\n';
                    }
                    int compId;
                    cin>>compId;
                    Competitor* tempPtr=dynamic_cast<Competitor*>(people.back());
                    tempPtr->addResultData(proba,times,times_len,__rank,sgRecord,avgRecord,compId);
                    tempPtr->findBestResults();
                    tempPtr->calculateAverageResult();

                    cout<<"Apasati 2 pentru a afisa acest concurent in urma actualizarii\n";
                    cin>>userInput;
                    if(userInput==2){
                        people.back()->print();
                    }
                }
            } else if(userInput==2){
                cout<<"La care competitor doriti sa adaugati rezultatul?\n";
                vector<Competitor*> actualCompetitors; //vector cu persoanele care sunt chiar concurenti (trebuie schimbat numele vectorului initial).
                for(int i=0; i<people.size(); i++){
                    Competitor* tempPtr=dynamic_cast<Competitor*>(people[i]);
                    if(tempPtr){
                        actualCompetitors.push_back(tempPtr);
                    }
                }
                for(int i=0; i<actualCompetitors.size(); i++){
                    String tmp=actualCompetitors[i]->getName();
                    cout<<i<<". "<<tmp;
                    cout<<'\n';
                }
                cout<<'\n';
                int indexCompetitor;
                cin>>indexCompetitor;
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
                    cout<<compList[i]->getId()<<". ";
                    compList[i]->print();
                    cout<<'\n';
                }
                int compId;
                cin>>compId;
                actualCompetitors[indexCompetitor]->addResultData(proba,times,times_len,__rank,sgRecord,avgRecord,compId);
                actualCompetitors[indexCompetitor]->findBestResults();
                actualCompetitors[indexCompetitor]->calculateAverageResult();

                cout<<"Apasati 2 pentru a afisa acest concurent in urma actualizarii, sau 3 pentru a afisa single-ul si average-ul acestui rezultat ";
                cin>>userInput;
                if(userInput==2){
                    actualCompetitors[indexCompetitor]->print();
                } else if(userInput==3){
                    //competitors[indexCompetitor].getResults()[competitors[indexCompetitor].getResultsLen()-1].calculateAverageAndSingle();
                    cout<<"Single: "<<actualCompetitors[indexCompetitor]->getResults()[actualCompetitors[indexCompetitor]->getResultsLen()-1].getSingle()<<" Average: "<<actualCompetitors[indexCompetitor]->getResults()[actualCompetitors[indexCompetitor]->getResultsLen()-1].getAverage()<<'\n';
                }
            } else if(userInput==3){
                cout<<"Introduceti numele competitiei pe care vreti sa o adaugati ";
                char compName[50];
                cin.get();
                cin.getline(compName,50);
                String compNameStr(compName);
                cout<<"Cati competitori au participat? ";
                int nrCompetitori;
                cin>>nrCompetitori;
                int id=compList[compList.size()-1]->getId()+1;
                cout<<"Introduceti data competitiei, ziua luna an (numere cu spatiu intre ele) ";
                int zi, luna, an;
                cin>>zi>>luna>>an;
                compList.add(new Competition(compNameStr,nrCompetitori,id, zi, luna, an));
                cout<<"Apasati 2 pentru a afisa aceasta competitie\n3 pentru a modifica numele\n4 pentru a modifica numarul de concurenti\n5 pentru a seta un alt id\n";
                cin>>userInput;
                if(userInput==2){
                    compList[compList.size()-1]->printDetailed();
                } else if(userInput==3){
                    cout<<"Introduceti numele nou ";
                    cin.get();
                    cin.getline(compName,50);
                    String compNameStr2(compName);
                    compList[compList.size()-1]->setName(compNameStr2);
                    cout<<"Apasati 2 pentru a afisa competitia ";
                    cin>>userInput;
                    if(userInput==2){
                        compList[compList.size()-1]->printDetailed();
                    }
                } else if(userInput==4){
                    cout<<"Introduceti numarul de concurenti ";
                    cin>>userInput;
                    compList.back()->setNumberOfCompetitors(userInput);
                    cout<<"Apasati 2 pentru a afisa competitia ";
                    cin>>userInput;
                    if(userInput==2){
                        compList.back()->printDetailed();
                    }
                } else if(userInput==5){
                    cout<<"Atentie, id-ul trebuie sa fie diferit fata de cele deja existente in baza de date:\n";
                    for(int i=0; i<compList.size(); i++){
                        cout<<compList[i]->getId()<<". ";
                        compList[i]->print();
                        cout<<'\n';
                    }
                    cout<<"Introduceti noul id ";
                    cin>>userInput;
                    compList.back()->setDifferentId(userInput);
                    cout<<"Apasati 2 pentru a afisa competitia ";
                    cin>>userInput;
                    if(userInput==2){
                        compList.back()->printDetailed();
                    }
                }
            }
        }
    }
    //dezalocare persoane
    for(int i=0; i<people.size(); i++){
        delete people[i];
    }
    return 0;
}
