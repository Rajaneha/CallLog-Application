#include<iostream>
#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;
struct node
{
    string phoneNumber;
    string name;
    int time;
    int day,month,year;
    struct node* link;
};
class ll
{
    struct node* start,*ptr,*prev;
public:
    ll()
    {
        start=NULL;
        ptr=NULL;
    }
    void create(string,string ,int ,int,int,int);
    void insertEnd(string ,string,int,int,int,int);
    int del(string);
    int searchbyName(string );
    void displayhistory(node *);
    void display();
    void delLast();
    void searchMonth(int );
    void delFront();
};
class hashtable
{
    ll *table;
    int total;
    int gethash(string);
public:
    hashtable(int n)
    {
        total=26;
        table=new ll[n];
    }
    void insertContact(string ,string ,int,int,int,int );
    void searchHistoryByMonth(int );
    int searchContactbyName(string );
    int removeContact(string);
    void printhistory();
};
class LinkStack
{
    struct node* top;
public:
    LinkStack()
    {
        top=NULL;
    }
    void createTop(string p,string N,int t,int d,int m,int y)
    {
        struct node* n=new node;
        n->phoneNumber=p;
        n->name=N;
        n->time=t;
        n->day=d;
        n->month=m;
        n->year=y;
        n->link=NULL;
        top=n;
    }
    void push(string p,string N,int t,int d,int m,int y)
    {
        if(top==NULL)
        {
            createTop(p,N, t,d,m, y);
        }
        else{
            struct node* n=new node;
            n->phoneNumber=p;
            n->name=N;
            n->time=t;
            n->day=d;
            n->month=m;
            n->year=y;
            n->link=top;
            top=n;
        }
    }
    node* pop()
    {
        if(top==NULL)
            return NULL;
        else
        {
            node* temp=top;
            top=top->link;
            temp->link=NULL;
            delete temp;
        }
        return top;
    }
    void displayTop()
    {
        cout<<setw(20)<<left<<top->name;
        cout<<setw(30)<<top->phoneNumber;
        cout<<setw(2)<<int(top->time)<<setw(20)<<" mins";
        cout<<top->day<<"/"<<top->month<<"/"<<top->year<<endl;
    }
};
void ll::create(string no,string Name,int Time,int dd,int mm,int yy)
{
    struct node* n=new node;
    n->phoneNumber=no;
    n->name=Name;
    n->time=Time;
    n->link=NULL;
    n->day=dd;
    n->month=mm;
    n->year=yy;
    start=n;
}
void ll::insertEnd(string no,string Name,int Time,int dd,int mm,int yy )
{
    ptr=start;
    if(ptr==NULL)
    {
        create( no,Name,Time,dd,mm,yy);
    }
    else
    {
        while(ptr->link!=NULL)
        {
            ptr=ptr->link;
        }
        struct node* n=new node;
        n->phoneNumber=no;
        n->name=Name;
        n->time=Time;
        n->day=dd;
        n->month=mm;
        n->year=yy;
        n->link=NULL;
        ptr->link=n;
    }
}
int ll::searchbyName(string Name)
{
    int f=0;
    ptr=start;
    while(ptr!=NULL)
    {
        if(ptr->name==Name)
        {
            f=1;
            displayhistory(ptr);
            ptr=ptr->link;
        }
        else
            ptr=ptr->link;
    }
    return f;
}
int ll::del(string Name)
{
    int flag=0;
    node *temp;
    ptr=start;

    if(ptr->link==NULL)
    {
        delFront();
        return 1;
    }
    else
    {
        while(ptr->link!=NULL)
        {
            if(ptr->link->name==Name)
            {
                flag=1;
                //cout<<endl<<"Contact found " ;
                temp=ptr->link;
                ptr->link=ptr->link->link;
                delete temp;
            }
            else
            {
                ptr=ptr->link;
            }
        }
    }
    if(start->name==Name)
    {
        delFront();
    }
    return flag;
}
void ll::delLast()
{
    node *temp;
    ptr=start;
    while(ptr->link->link!=NULL){
        ptr=ptr->link;
    }
    temp=ptr->link->link;
    ptr->link=NULL;
    delete temp;
}
void ll::delFront()
{
    ptr=start;
    start=start->link;
    ptr->link=NULL;
    delete(ptr);
}
void ll::searchMonth(int Month)
{
    ptr=start;
    while(ptr!=NULL)
    {
        if(ptr->month==Month)
        {
            displayhistory(ptr);
        }
        ptr=ptr->link;
    }
}
void ll::display()
{
    ptr=start;
    while(ptr!=NULL)
    {
        displayhistory(ptr);
        ptr=ptr->link;
    }
}
void ll::displayhistory(node *ptr)
{
    cout<<setw(20)<<left<<ptr->name;
    cout<<setw(30)<<ptr->phoneNumber;
    cout<<setw(2)<<int(ptr->time)<<setw(20)<<" mins";
    cout<<ptr->day<<"/"<<ptr->month<<"/"<<ptr->year<<endl;
}

int hashtable::gethash(string key)
{
    return int(key[0])-65;
}
void hashtable::insertContact(string no,string Name,int Time,int dd,int mm,int yy )
{
    table[gethash(Name)].insertEnd(no,Name,Time,dd,mm,yy);
}
int hashtable::removeContact(string Name)
{
    int x=gethash(Name);
    int f=table[x].del(Name);
    return f;
}
int hashtable::searchContactbyName(string Name)
{
    int x=gethash(Name);
    int f=table[x].searchbyName(Name);
    return f;
}
void hashtable::searchHistoryByMonth(int Month)
{
    for(int i=0;i<26;i++)
    {
        table[i].searchMonth(Month);
    }
}
void hashtable::printhistory()
{
    cout<<endl<<"-------------------------------------------------------------------------------------------------";
    cout<<endl<<setw(20)<<left<<"NAME"<<setw(30)<<"CONTACT NUMBER"<<setw(25)<<"DURATION"<<setw(30)<<"DATE";
    cout<<endl<<"-------------------------------------------------------------------------------------------------"<<endl;
    for(int i=0;i<total;i++)
    {
        table[i].display();
    }
}

int main()
{
    int ch1,ch2,ch3,Time;
    string name,number,Name;
    int dd,mm,yy;
    int Month;
    hashtable phn(26);
    LinkStack s;
    ifstream ifile;
    ifile.open("Contacts.txt");

    while(ifile>>name>>number>>Time>>dd>>mm>>yy)
    {
        phn.insertContact(number,name,Time,dd,mm,yy);
        s.push(number,name,Time,dd,mm,yy);
    }
    ifile.close();
    do{
        cout<<endl<<"=============================CALL LOG APPLICATION==================================";
        cout<<endl<<"1) Add History";
        cout<<endl<<"2) View History";
        cout<<endl<<"3) View recents";
        cout<<endl<<"0 -> exit";
        cout<<endl<<"Enter your choice : ";
        cin>>ch1;
        if(ch1==1)
        {
            do{
                cout<<endl<<"=======APPENDING THE HISTORY========";
                ofstream ofile("Contacts.txt",ios::app);
                cout<<endl<<"Enter name of the contact : ";
                cin>>name;
                cout<<"Enter the phone number : ";
                cin>>number;
                cout<<"Enter the duration of call : ";
                cin>>Time;
                cout<<"Enter the date:  (dd/mm/yyyy) ";
                cin>>dd>>mm>>yy;
                ofile<<name<<" "<<number<<" "<<Time<<" "<<dd<<" "<<mm<<" "<<yy<<endl;
                phn.insertContact(number,name,Time,dd,mm,yy);
                s.push(number,name,Time,dd,mm,yy);
                ofile.close();
                cout<<endl<<"Do you want to add another history?(1 -> yes/ 2 -> No)";
                cin>>ch3;
            }while(ch3!=2);
        }
        else if(ch1==2)
        {
            do
            {
                cout<<endl<<"=====MENU=====";
                cout<<endl<<"1) Delete History";
                cout<<endl<<"2) Search by Contact name";
                cout<<endl<<"3) Displaying All Contact";
                cout<<endl<<"4) History of a month ";
                cout<<endl<<"5) History month wise";
                cout<<endl<<"0 -> Exit";
                cout<<endl<<"Enter your choice : ";
                cin>>ch2;
                if(ch2==1)
                {
                    int rc;
                    cout<<endl<<"Enter Contact name to be deleted : ";
                    cin>>Name;
                    rc=1;
                    rc=phn.removeContact(Name);
                    fstream f,f2;
                    f.open("Contacts.txt",ios::in);
                    f2.open("temp.txt",ios::out|ios::app);
                    while(f>>name>>number>>Time>>dd>>mm>>yy)
                    {
                        if(name==Name)
                            continue;
                        else
                            f2<<name<<" "<<number<<" "<<Time<<" "<<dd<<" "<<mm<<" "<<yy<<endl;
                    }
                    f.close();
                    f2.close();
                    remove("Contacts.txt");
                    rename("temp.txt","Contacts.txt");

                }
                else if(ch2==2)
                {
                    cout<<endl<<"Enter Name to be searched : ";
                    cin>>name;
                    phn.searchContactbyName(name);
                }
                else if (ch2==3)
                {
                    cout<<endl<<"=====DISPLAYING ALL IN ALPHABETICAL ORDER======"<<endl;
                    phn.printhistory();
                }
                else if(ch2==4)
                {
                    cout<<endl<<"Enter Month to be searched : "<<endl;
                    cin>>Month;
                    cout<<endl<<"-------------------------------------------------------------------------------------------------";
                    cout<<endl<<setw(20)<<left<<"NAME"<<setw(30)<<"CONTACT NUMBER"<<setw(25)<<"DURATION"<<setw(30)<<"DATE";
                    cout<<endl<<"-------------------------------------------------------------------------------------------------"<<endl;
                    phn.searchHistoryByMonth(Month);
                }
                else if(ch2==5)
                {
                    cout<<endl<<"======MONTH WISE HISTORY======="<<endl;
                    cout<<endl<<"-------------------------------------------------------------------------------------------------";
                    cout<<endl<<setw(20)<<left<<"NAME"<<setw(30)<<"CONTACT NUMBER"<<setw(25)<<"DURATION"<<setw(30)<<"DATE";
                    cout<<endl<<"-------------------------------------------------------------------------------------------------"<<endl;
                    for(int i=1;i<=12;i++)
                    {
                        phn.searchHistoryByMonth(i);
                    }
                }
            }while(ch2!=0);
        }
        else if(ch1==3)
        {
            int recents;
            cout<<endl<<"How many recent history contacts you want to view?";
            do
            {
                cout<<endl<<"Enter here : ";
                cin>>recents;
                if(recents <0)
                {
                    cout<<endl<<"Please enter a positive value";
                }
            }while(recents<0);
            node* temp;
            cout<<endl<<"-------------------------------------------------------------------------------------------------";
            cout<<endl<<setw(20)<<left<<"NAME"<<setw(30)<<"CONTACT NUMBER"<<setw(25)<<"DURATION"<<setw(30)<<"DATE";
            cout<<endl<<"-------------------------------------------------------------------------------------------------"<<endl;
            for(int i=0;i<recents;i++)
            {
                s.displayTop();
                temp=s.pop();
                if(temp==NULL)
                {
                    cout<<endl<<"All contacts are displayed";
                    break;
                }
            }
        }
    }while(ch1!=0);
}

