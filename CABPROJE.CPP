#include<fstream.h>
#include<conio.h>
#include<process.h>
#include<string.h>
#include<stdio.h>

//class booking
class booking
{
  char car_type[20];
  char name[20];
  int passenger_no;
  float distance;
  float amt;
  int booking_id;
  int charges;
  char pickup_add[20];
  char date[20];
 public:
  void book_cab();
  void display_booking();
  void search_booking();
  void cancel_booking();
  int amt_calc();
  int bid_gen();
};

//class member
class member
{
  char name[20];
  char add[20];
  int memid;
 public:
  void membership();
  void display_record();
  void modify_record();
  void delete_record();
  int memid_gen();
  int retmemid()
  {
    return memid;
  }
};

//global variable
int gm;
//prototypes
void menu();
void booking_menu();
void checkid();
void membermenu();

			      /*IN CLASS FUNCIONS*/

			  /*Members of class booking*/

//1. Amount calculator
int booking::amt_calc()
{
  if(strcmpi("hatchback",car_type)==0)
  {
      amt= 100 + (distance*9);
  }
  else if(strcmpi("sedan",car_type)==0)
  {
      amt= 100 + (distance*12);
  }
  else if(strcmpi("suv",car_type)==0 || strcmpi("luv",car_type)==0)
  {
	  amt = 150 + (distance*30);
  }
  return(amt);
}

//2. Booking id generator
int booking::bid_gen()
{
  ifstream fin("book.dat",ios::binary);
  int rec;
  fin.seekg(0,ios::end);
  rec=fin.tellg()/sizeof(booking);
  fin.close();
  return rec;
}

//3. Book cab
void booking::book_cab()
{
  clrscr();
  char ch;
  fstream file("book.dat",ios::binary|ios::app);
  booking_id=bid_gen()+1;
  cout<<"Your booking id is ";
  cout<<booking_id<<endl;
  cout<<"\n\nEnter no. of passengers";
  cin>>passenger_no;
  if(passenger_no<=3)
  {
    cout<<"\nA Hatchback is recomended for you ! Go for a hatchback?(y/n)";
    cin>>ch;
    if(ch=='y')
    {
      strcpy(car_type,"Hatchback");
    }
    else
    {
      cout<<"\nSelect your ride out o the following:";
      cout<<"\nHatchback";
      cout<<"\nSedan";
      cout<<"\nLUV/XUV";
      gets(car_type);
    }
  }
  else if(passenger_no>3 && passenger_no<=5)
  {
    cout<<"\n A Sedan is rocomended for you ! Go for a Sedan ?(y/n)";
    cin>>ch;
    if(ch=='y')
    {
      strcpy(car_type,"Sedan") ;
    }
    else
    {
      cout<<"\n Select your ride out o the following:";
      cout<<"\nHatchback";
      cout<<"\nSedan";
      cout<<"\nLUV/XUV";
      gets(car_type);
    }
  }
  else if(passenger_no>5 && passenger_no<=10)
  {
    cout<<"\n A LUV/XUV is recomended for you ! Go for a LUV/XUV ?(y/n)";
    cin>>ch;
    if (ch=='y')
    {
      strcpy(car_type,"XUV");
    }
    else
    {
      cout<<"\nSelect your ride out o the following:";
      cout<<"\nHatchback";
      cout<<"\nSedan";
      cout<<"\nLUV/XUV \n";
      gets(car_type);
    }
  }

  cout<<"\n Enter your name \n";
  gets(name);
  cout<<"Enter date of travel \n";
  gets(date);
  cout<<"Enter pickup address \n";
  gets(pickup_add);
  cout<<"Enter distance to be travelled \n";
  cin>>distance;
  if(gm==1)
	  charges=amt_calc();
  else if(gm==2)
  {
	int d=amt_calc()/20;
	charges=amt_calc()-d;
  }
  file.write((char*)this,sizeof(booking));
  file.close();
  cout<<"\n You have successfully booked a cab and BOOKING ID :"<<booking_id;
  cout<<"\n Your Expected amount ="<<charges;
  getch();
  menu();
}

//4. Display Booking
void booking::display_booking()
{
  clrscr();
  int tempid;
  cout<<"Enter your booking id \n";
  cin>>tempid;
  int flag=0;
  ifstream fin("book.dat",ios::binary);
  while(fin.read((char*)this,sizeof(booking)))
  {
    if(tempid==booking_id)
    {
      flag=1;
      clrscr();
      gotoxy(15,10);
      cout<<"Your id: ";
      gotoxy(23,10);
      cout<<booking_id<<endl;
      gotoxy(15,11);
      cout<<"Booked on the name of:";
      gotoxy(37,11);
      cout<<name<<endl;
      gotoxy(15,12);
      cout<<"Date of travel:";
      gotoxy(30,12);
      cout<<date<<endl;
      gotoxy(15,13);
      cout<<"Car type :";
      gotoxy(25,13);
      cout<<car_type<<endl;
      gotoxy(15,14);
      cout<<"Pickup address:";
      gotoxy(30,14);
      cout<<pickup_add<<endl;
      gotoxy(15,15);
      cout<<"Total fare:";
      gotoxy(30,15);
      cout<<charges;
      getch();
      break;
    }
  }
  fin.close();
  if(flag==0)
  {
    cout<<"\n\n\n\t\t Booking Id not found";
    getch();
  }
    menu();
}

//6.Cancel Booking
void booking::cancel_booking()
{
  int tempid;
  cout<<"Enter your id : \n";
  cin>>tempid;
  ifstream fin("book.dat",ios::binary);
  ofstream fout("temp.dat",ios::binary);
  while(fin.read((char*)this,sizeof(booking)))
  {
    if(tempid!=booking_id)
    {
      fout.write((char*)this,sizeof(booking));
    }
  }
  fin.close();
  fout.close();
  clrscr();
  gotoxy(20,10);
  cout<<"Your booking has been successfully cancelled !";
  getch();
  remove("book.dat");
  rename("temp.dat","book.dat");
  menu();
}
			 /* Member class functions*/

//1. Member id generator
int member::memid_gen()
{
  int temppos;
  ifstream fin("mem.dat",ios::binary);
  fin.seekg(0,ios::end);
  temppos=fin.tellg();
  fin.close();
  return temppos;
}

//2. Membership
void member::membership()
{    clrscr();
  ofstream fout("mem.dat",ios::binary|ios::app);
  cout<<"Enter your name \n";
  gets(name);
  cout<<"Enter your address \n";
  gets(add);
  int pos=memid_gen();
  memid=(pos/sizeof(member))+1000;
  gotoxy(20,10);
  cout<<"Your member id is :"<<endl;
  gotoxy(20,11);
  cout<<memid;
  fout.write((char*)this,sizeof(member));
  fout.close();
  getch();
  membermenu();
}

//3. Display Record
void member::display_record()
{
  clrscr();
  int tempid;
  int flag=0;
  cout<<"Enter your member id \n";
  cin>>tempid;
  ifstream fin("mem.dat",ios::binary);
  while(fin.read((char*)this,sizeof(member)))
  {
    if(memid==tempid)
    {
      flag=1;
      gotoxy(20,10);
      cout<<"Your Id: \n";
      gotoxy(20,11);
      cout<<memid;
      gotoxy(20,12);
      cout<<"Your name: \n";
      gotoxy(20,13);
      cout<<name;
      getch();
      break;
    }
  }
  if(flag==0)
  {
    clrscr();
    gotoxy(20,10);
    cout<<"RECORD NOT FOUND" ;
    getch();
  }
  fin.close();
  membermenu();
}

//4. Delete Record
void member::delete_record()
{
  int tempid;
  cout<<"Enter your id : \n";
  cin>>tempid;
  ifstream fin("mem.dat",ios::binary);
  ofstream fout("temp2.dat",ios::binary);
  while(fin.read((char*)this,sizeof(member)))
  {
    if(tempid!=memid)
    {
      fout.write((char*)this,sizeof(member));
    }
  }
  fin.close();
  fout.close();
  remove("mem.dat");
  rename("temp2.dat","mem.dat");
  cout<<"You are no more a member of E-CABBIE";
  getch();
  membermenu();
}

//5. Modify Record
void member::modify_record()
{
  int tempid,flag=0;
  clrscr();
  cout<<"Enter your id"<<endl;
  cin>>tempid;
  ifstream file("mem.dat",ios::binary);
  ofstream fout("temp2.dat",ios::binary);
  while(file.read((char*)this,sizeof(member)))
  {
	if(tempid==memid)
	 {
		  clrscr();
		  cout<<"Enter your name \n";
		  gets(name);
		  cout<<"Enter your address \n";
		  gets(add);
		  flag=1;
	}
	 fout.write((char*)this,sizeof(member));
   }
  file.close();
  fout.close();
  remove("mem.dat");
  rename("temp2.dat","mem.dat");
  if(flag==0)
    {
      gotoxy(25,10);
      cout<<"RECORD NOT FOUND";
    }
    else
	cout<<"RECORD MODIFY ";
   membermenu();
}

		      /*NOT IN CLASS FUNCTIONS*/
//1.Member Menu
void membermenu()
{
     member M;
     int mem_choice;
     clrscr();
      gotoxy(20,10);
      cout<<"1. Become a member ";
      gotoxy(20,11);
      cout<<"2. Display record ";
      gotoxy(20,12);
      cout<<"3. Modify my record ";
      gotoxy(20,14);
      cout<<"4. Delete my record ";
      gotoxy(20,15);
      cout<<"5. Goto main menu ";
      gotoxy(20,16);
      cout<<"Enter your choice : ";
      cin>>mem_choice ;
      if(mem_choice==1)
	M.membership();
      else if(mem_choice==2)
	M.display_record();
      else if(mem_choice==3)
	M.modify_record();
      else if(mem_choice==4)
	M.delete_record();
      else if(mem_choice==5)
	menu();
}

//2. Check id
void checkid()
{
  clrscr();
  int idt;
  int flag=0;
  member M;
  booking b;
  char ch;
   cout<<"Enter your member id \n";
    cin>>idt;
    ifstream fin("mem.dat",ios::binary);
   while(fin.read((char*)&M,sizeof(M)))
   {
	    if(idt==M.retmemid())
	    {
	      flag=1;
	    }
    }
    fin.close();
    if(flag==1)
    {
      clrscr();
      gm=2;
      b.book_cab();
   }
   else
   {
     clrscr();
     gotoxy(20,10);
     cout<<"NO SUCH RECORD EXIST";
     }
     getch();
     menu();
   }

//3.Booking Menu
void booking_menu()
{
  int book;
  booking B;
  clrscr();
  gotoxy(20,10);
  cout<<"1. Book as a guest \n";
  gotoxy(20,11);
  cout<<"2. Book as a member \n";
  gotoxy(20,12);
  cout<<"3.  main menu \n";
  gotoxy(20,15);
  cout<<"Enter your choice \n";
  cin>>book;
  if(book==1)
  {
    gm=1;
    B.book_cab();
  }
  else if(book==2)
  {
	checkid();
  }
  else if(book==3)
  {
    menu();
  }
}

//4. Menu
void menu()
{
  clrscr();
  booking B;
  int ur_choice;
  do
  {
  clrscr();
  gotoxy(15,8);
  cout<<"Welcome to E-CABBIE:Move It Your Way ! ";
  gotoxy(20,10);
  cout<<"1.Book a cab \n";
  gotoxy(20,11);
  cout<<"2. Display my booking \n";
  gotoxy(20,12);
  cout<<"3. Cancel my booking \n";
  gotoxy(20,13);
  cout<<"4. Member Menu \n";
  gotoxy(20,14);
  cout<<"5. Exit \n";
  gotoxy(20,15);
  cout<<"Enter your choice \n";
  cin>>ur_choice;
  if(ur_choice==1)
  {
    booking_menu();
  }
  else if(ur_choice==2)
  {
	 B.display_booking();
  }
  else if(ur_choice==3)
  {
	  B.cancel_booking();
  }
  else if(ur_choice==4)
  {
	 membermenu();
  }
  else if(ur_choice==5)
  {
   exit(0);
  }
 }while(ur_choice!=5);
}

//5. Password
void password()
{
	char str[4];
	clrscr();
	gotoxy(10,10);
	cout<<"enter password :";
	str[0]=getch();
	cout<<"*";
	str[1]=getch();
	cout<<"*";
	str[2]=getch();
	cout<<"*";
	if(str[0]=='1' && str[1]=='2' && str[2]=='3')
	{
		gotoxy(10,12);
		cout<<"correct passowrd";
		gotoxy(20,22);
		cout<<"press any key to cont....";

		getch();
		menu();
	}
	else
	{
		cout<<"\n incorrect passowrd";
		getch();
	}
}

//6. Program Maker
void prog_maker()
{
  clrscr();
  cout<<"THIS PROGRAM IS MADE BY: \n\n\n";
  cout<<"\t\t\tRISHABH MALHOTRA\n\n";
  cout<<"\t\t\t      AND\n\n";
  cout<<"\t\t\tPRIYESH SHARMA";
  cout<<"\n\n\t\t\t       OF\n\n";
  cout<<"\t\t\t   CLASS XII C";
  getch();
}

				    /*MAIN*/

void main()
{
  prog_maker();
  password();
}
