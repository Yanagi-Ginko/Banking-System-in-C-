#include <iostream>
#include <fstream>
#include <iomanip>
#include <cctype>

using namespace std;


class account{
    int acno;
    char name[30];
    int deposit;
    char type;

    public:
        void create_Account();
        void show_Account();
        void modify_Account();
        void dep(int);
        void draw(int);
        void report();
        int retAcno();
        int retDeposit();
        char retType();
};

void account::create_Account(){
    cout<<"\n Enter The account No. : ";
    cin>>acno;
    cout<<"\n\n Enter the name of the account Holder: ";
    cin.ignore();
    cin.getline(name,30);
    cout<<"\n Enter Type of the account (C/S) : ";
    cin>>type;
    type=toupper(type);
    cout<<"\n Enter The Initial amount (larger than 500 and less then 1000): ";
    cin>>deposit;
    cout<<"\n\n Success Created";
}


void account::show_Account(){
    cout<<"\nAccount No. : "<<acno;
    cout<<"\nAccount Holder: "<<name;
    cout<<"\nType of Account: "<<type;
    cout<<"\nBalance amount: "<<deposit; 
}

void account::modify_Account(){
    cout<<"\nAccount No. : "<<acno;
    cout<<"\nModify Account Holder Name: ";
    cin.ignore();
    cin.getline(name,30);
    cout<<"\nModify Type of the Account : ";
    cin>>type;
    type=toupper(type);
    cout<<"\nModify Balance amount: ";
    cin>>deposit;
}

void account::dep(int charge){
    deposit+= charge;
}

void account::draw(int charge){
    deposit-=charge;
}

void account::report(){
    cout<<acno<<setw(10)<<"  "<<name<<setw(10)<<"  "<<type<<setw(7)<<deposit<<endl;
}

int account::retAcno(){
    return acno;
}

int account::retDeposit(){
    return deposit;
}

char account::retType(){
    return type;
}

void write_Account(){
    account acc;
    ofstream outFile;
    outFile.open("data.dat",ios::binary| ios::app);
    acc.create_Account();
    outFile.write(reinterpret_cast<char *> (&acc), sizeof(account));
    outFile.close();
}

void display(int number){
    account acc;
    bool check = false;
    ifstream inFile;
    inFile.open("data.dat",ios::binary);
    if(!inFile){
        cout<<"File can't be open";
        return;
    }
    cout<<"\n Balance Details\n";
    while(inFile.read(reinterpret_cast<char *> (&acc), sizeof(account))){
        if(acc.retAcno()==number){
            acc.show_Account();
            check=true;
        }
    }
    inFile.close();
    if(check==false)
        cout<<"Account No don't exist!!";
}

void modify_account(int number){
    bool check = false;
    account acc;
    fstream file;
    file.open("data.dat", ios::binary|ios::in|ios::out);
    if(!file){
        cout<<"Couldn't open ";
        return;
    }
    while(!file.eof() && check==false){
		file.read(reinterpret_cast<char *> (&acc), sizeof(account));
		if(acc.retAcno()==number){
			acc.show_Account();
			cout<<"\n\nEnter The New Details of account"<<endl;
			acc.modify_Account();
			int pos=(-1)*static_cast<int>(sizeof(account));
			file.seekp(pos,ios::cur);
		    file.write(reinterpret_cast<char *> (&acc), sizeof(account));
            cout<<"\n\n Record Update";
            check=true;
        }

    }
    file.close();
    if(check==false)
        cout<<"\n\n Record Not Found";
}

void delete_acc(int number){
    account acc;
    ifstream inFile;
    ofstream outFile;
    inFile.open("data.dat",ios::binary);
    if(!inFile){
        cout<<"File couldn't open";
        return;
    }
    outFile.open("temp.dat", ios::binary);
    inFile.seekg(0,ios::beg);
    while(inFile.read(reinterpret_cast<char*> (&acc), sizeof(account))){
        if(acc.retAcno()!=number){
            outFile.write(reinterpret_cast<char*> (&acc),sizeof(account));
        }
    }
    inFile.close();
    outFile.close();
    remove("data.dat");
    rename("temp.dat", "data.dat");
    cout<<"\n Record Delete";
}


void display_all(){
    account acc;
    ifstream inFile;
    inFile.open("data.dat", ios::binary);
    if(!inFile){
        cout<<"File couldn't open";
        return;
    }

    cout<<"\n\n\t List of Account";
    cout<<"====================================================\n";
	cout<<"A/c no.      NAME           Type  Balance\n";
	cout<<"====================================================\n";
    while(inFile.read(reinterpret_cast<char*>(&acc),sizeof(account))){
        acc.report();
    }
    inFile.close();
}


void deposit_withdraw(int number, int option){
    int amount;
    bool check = false;
    account acc;
    fstream File;
    File.open("data.dat", ios::binary|ios::in|ios::out);
    if(!File){
        cout<<"File couldn't open";
        return ;
    }
    while(!File.eof() && check==false){
        File.read(reinterpret_cast<char*> (&acc),sizeof(account));
        if(acc.retAcno()==number){
            acc.show_Account();
            if(option==1){
                cout<<"\n\n deposit amount";
                cout<<"\n\n enter the amount to be deposited: ";
                cin>>amount;
                acc.dep(amount);
            }
            if(option==2){
                cout<<"\n\n withdraw amount ";
                cout<<"\n\n enter the amount to be withdraw: ";
                cin>>amount;
                acc.draw(amount);
                int balance = acc.retDeposit()-amount;
                if((balance<500 && acc.retType()=='S')||(balance<1000 && acc.retType()=='C'))
                    cout<<"Insufficience balance";
                else
                    acc.draw(amount);
            }
            int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur);
		    File.write(reinterpret_cast<char *> (&acc), sizeof(account));
            cout<<"\n\n Record Update";
            check=true;
        }
    }
    File.close();
    if(check==false)
        cout<<"\n\n Record not found";
}


void welcome(){
    cout<<"\n\n\n\t Bank System write in C++";
    cout<<"\n\n\t Enter to start: "<<endl;
    cin.get();
}



int main(){
    char ch;
    int number;
    welcome();
    do{
        system("cls");
        cout<<"\n\n\n\t  MAIN MENU";
        cout<<"\n\n\t01. NEW ACCOUNT";
		cout<<"\n\n\t02. DEPOSIT AMOUNT";
		cout<<"\n\n\t03. WITHDRAW AMOUNT";
		cout<<"\n\n\t04. BALANCE ENQUIRY";
		cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t06. CLOSE AN ACCOUNT";
		cout<<"\n\n\t07. MODIFY AN ACCOUNT";
		cout<<"\n\n\t08. EXIT";
		cout<<"\n\n\tSelect Your Option (1-8) ";
        cin>>ch;
        system("cls");
        switch(ch){
            case '1': 
                write_Account(); 
                break;
            case '2': 
                cout<<"\n\n enter the No. of the account : ";
                cin>>number;
                deposit_withdraw(number,1);
                break;

            case '3': 
                cout<<"\n\n enter the No. of the account : ";
                cin>>number;
                deposit_withdraw(number,2);
                break;

            case '4':
                cout<<"\n\n enter the No. of the account : ";
                cin>>number;
                display(number);
                break;
            
            case '5':
                display_all();
                break;
            
            case '6':
                cout<<"\n\n enter the No. of the account : ";
                cin>>number;
                delete_acc(number);
                break;
            
            case '7':
                cout<<"\n\n enter the No. of the account : ";
                cin>>number;
                modify_account(number);
                break;
            
            case '8':
                cout<<"\n\n Thanks for using this systems ";
                break;

            default: cout<<"\n";
        }
        cin.ignore();
        cin.get();

    }while(ch!='8');

    return 0;
}






