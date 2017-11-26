#include <iostream>
#include <string.h>
#define Max 30
using namespace std;
//Simple code in c++ for managing employees in a firm
class General{
public:
    static int emplyees;
    static int emplyeesPermanent;
    static int emplyeesTemporary;
    static void increase(){emplyees++;};
    static void increase2(){emplyeesPermanent++;};
    static void increase3(){emplyeesTemporary++;};
    static void decrease(){emplyees--;}
    static void decrease2(){emplyeesPermanent--;};
    static void decrease3(){emplyeesTemporary--;};
    static void show(){ cout << emplyees <<" "<<emplyeesPermanent<<" "<<emplyeesTemporary<<endl;};
}g;
int General::emplyees = 0;
int General::emplyeesPermanent = 0;
int General::emplyeesTemporary = 0;

class Employee{
    char name[Max];
    char data[Max];
    char post[Max];
    int code;
    virtual void getCode()=0;
public:
    Employee();
    Employee(Employee &p);
    ~Employee();
    void setCode(int x){ code = x;};
    int getCode(){return code;};
    char* getName(){return name;};
    char* getData(){return data;};
    char* getPost(){return post;};
    virtual void Print(){cout << "Name: "<<getName()<<endl;
                        cout <<"Data: "<<getData()<<endl;
                        cout <<"Post: "<<getPost()<<endl;
    };
};

class EmployeePermanent:public Employee{
    int fixedSalary;
    char type[4];
    virtual void getCode();
public:
    EmployeePermanent();
    EmployeePermanent(EmployeePermanent &p);
    ~EmployeePermanent();
    int getSalary(){return fixedSalary;};
    virtual void Print(){
        cout << "Name: "<<getName()<<endl;
        cout <<"Data: "<<getData()<<endl;
        cout <<"Post: "<<getPost()<<endl;
        cout << "Code: "<<getCode()<<endl;
        cout << "Salary: "<<getSalary()<<" "<<type<<endl;
    }
};

class EmployeeTemporary:public Employee{
    int hourWage;
    int nrHours;
    char endingData[Max];
    char type[4];
    virtual void getCode();
public:
    EmployeeTemporary();
    EmployeeTemporary(EmployeeTemporary &p);
    ~EmployeeTemporary();
    int getHourWage(){return hourWage;};
    int getnrHours(){return nrHours;};
    char* getData(){return endingData;};
    virtual void Print(){
        cout << "Name: "<<getName()<<endl;
        cout <<"Data: "<<getData()<<endl;
        cout <<"Post: "<<getPost()<<endl;
        cout << "Code: "<<getCode()<<endl;
        cout << "Wage/Hour: "<<getHourWage()<< " "<<type<<endl;
        cout<< "Number of hours:"<<getnrHours()<<endl;
        cout << "Minimal monthly wage:"<< getHourWage()*getnrHours()<<" "<<type<<endl;
        cout << "Ending data:"<<getData()<<endl;
    }
};
int main()
{
    Employee *p[Max];
    bool b;
    for( int i=0; i<5; i++){
        cout << "Permanent or temporary? "<<endl;
        cin >> b;
        if( b == 0){
            p[i] = new EmployeePermanent;
        }
        if( b == 1){
            p[i] = new EmployeeTemporary;
        }
    }
    g.show();
    for( int i=0; i<3; i++){
        p[i]->Print();
    }
    return 0;
}

Employee::Employee(){
    g.increase();
    char s[Max];
    char vectCif[]="0123456789";
    try{
        cin >> s;
        if( strchr(vectCif, s[0])) throw 'c';
        else throw 1;
    }
    catch(char){
        strcpy(name, s);
    }
    catch(...){
        cout << "Incorrect name. Pass another: "<<endl;
        cin >> s;
        strcpy(name, s);
    }
    try{
        cin >> s;
        if( strlen(s) ==10&& strchr(vectCif, s[0]) != 0) throw 'c';
        else throw 1;
    }
    catch(char){
        strcpy(data, s);
    }
    catch(...){
        cout << "Wrong data"<<endl;
        cin >> s;
        strcpy(data, s);
    }
    cin >> post;
}

Employee::Employee(Employee &p){
    strcpy(name, p.name);
    strcpy(data, p.data);
    strcpy(post, p.post);
}

Employee::~Employee(){g.decrease();}

EmployeePermanent::EmployeePermanent():Employee(){
    cin >> fixedSalary;
    cout<< "lei or euro"<<endl;
    char s[4];
    cin >> s;
    if( strcmp(s, "euro")==0){
        fixedSalary = fixedSalary/4.15;
        strcpy(type, s);
    }
    else{
        strcpy(type, "lei");
    }
    g.increase2();
    getCode();
}

EmployeePermanent::EmployeePermanent(EmployeePermanent &p):Employee(p){
    fixedSalary = p.fixedSalary;
    strcpy(type, p.type);
    getCode();
}

EmployeePermanent::~EmployeePermanent(){ g.decrease2();};

EmployeeTemporary::EmployeeTemporary():Employee(){
    cin >> hourWage;
    cin >> nrHours;
    cin >> endingData;
    g.increase3();
    getCode();
    cout<< "lei or euro"<<endl;
    char s[4];
    cin >> s;
    if( strcmp(s, "euro")){
        hourWage = hourWage/4.15;
        strcpy(type, s);
    }
    else{
        strcpy(type, "lei");
    }
}

EmployeeTemporary::EmployeeTemporary(EmployeeTemporary &p):Employee(p){
    hourWage = p.hourWage;
    nrHours = p.nrHours;
    strcpy(endingData, p.endingData);
    getCode();
    strcpy(type, p.type);
}

EmployeeTemporary::~EmployeeTemporary(){ g.decrease3();}

void EmployeePermanent::getCode(){
    cout << "Offer a code for employee"<<endl;
    cout << "Permanent employees must have a 0 in their code"<<endl;
    int nr;
    bool b=0;
    while( b == 0){
        cin >> nr;
        try{
            if( nr < 0) throw 'c';
            if( nr%10 != 0) throw 1.25;
            else throw 2;
        }
        catch(char){
            cout << "Negative number. Try again"<<endl;
        }
        catch(double){
            cout << "Wrong last digit"<<endl;
        }
        catch(...){
            Employee::setCode(nr);
            b = 1;
        }
    }
}

void EmployeeTemporary::getCode(){
    cout << "Offer a code for an employee"<<endl;
    cout << "Temporary employees must have a digit 1 at the end"<<endl;
    int nr;
    bool b=0;
    while( b == 0){
        cin >> nr;
        try{
            if( nr < 0 && nr !=0) throw 'c';
            if( nr%10 != 1) throw 1.25;
            else throw 2;
        }
        catch(char){
            cout << "The number is negative or 0. Try again"<<endl;
        }
        catch(double){
            cout << "Wrong last digit"<<endl;
        }
        catch(...){
            Employee::setCode(nr);
            b = 1;
        }
    }
}
