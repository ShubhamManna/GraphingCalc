#include<iostream>
#include<conio.h>
#include<math.h>
#include<string.h>
#include<graphics>
#include<fstream.h>

static int u=10;

void graph(int x, int y)
{
 line(x/2,0,x/2,y);
 line(0,y/2,x,y/2);
 for(int i=0;i<50;i++)
 {
  line(x/2+(i*u),y/2,x/2+(i*u),y/2+5);
  line(x/2-(i*u),y/2,x/2-(i*u),y/2+5);
  line(x/2,y/2+(i*u),x/2-5,y/2+(i*u));
  line(x/2,y/2-(i*u),x/2-5,y/2-(i*u));
 }
}

class history
{
 char date[12],time [10],info[50];
 public:
 void enter(char ch)
 {
  strcpy(date,__DATE__);
  strcpy(time,__TIME__);
  if(ch=='o') strcpy(info," opened calculator ");
  if(ch=='l') strcpy(info," entered equation of line ");
  if(ch=='c') strcpy(info," entered equation of circle ");
  if(ch=='h') strcpy(info," saw history ");
 }
 void disp()
 {
  cout<<date<<"\t"<<time<<"\tYou"<<info<<"\n";
 }
};

class line
{
 float a,b,c;
 int x1,x2,y1,y2;
 public:
 void getval()
 {
  cout<<"\nValue of a: "; cin>>a;
  cout<<"Value of b: "; cin>>b;
  cout<<"Value of c: "; cin>>c;
 }
 void calc()
 {
  cout<<"\nEquation of line: "<<a<<"x+"<<b<<"y+"<<c<<"=0";
  cout<<"\n\nSlope = "<<-a/b;
  cout<<"\nx intercept = "<<-c/a;
  cout<<"\ny intercept = "<<-c/b;
 }
 void dline(int x, int y)
 {
  graph(x,y);
  x1=100; y1=(-c-(a*100))/b;
  x2=-100; y2=(-c-(a*-100))/b;
  line(x/2+(u*x1),y/2-(u*y1),x/2+(u*x2),y/2-(u*y2));
 }
}l1;

class circle
{
 float a,b,c,g,f,r,x1,y1;
 public:
 void getval()
 {
  cout<<"\nValue of a: "; cin>>a;
  cout<<"Value of b: "; cin>>b;
  cout<<"Value of c: "; cin>>c;
 }
 void calc()
 {
  cout<<"\nEquation of circle: x^2+y^2+x("<<a<<")+y("<<b<<")+"<<c;
  g=a/2; f=b/2;
  cout<<"\n\nCentre: "<<"("<<-g<<","<<-f<<")\n";
  r=pow(g,2)+pow(f,2)-c;
  if(r>0)
  cout<<"Radius= "<<sqrt(r)<<"\n";
  else
   if(r<0)
   cout<<"Circle is imaginary\n";
   else
   cout<<"Radius=0 (point circle)\n";
  x1=pow(g,2);
  cout<<"x-intercept= ";
  if(x1==c)
  cout<<"0 [Circle touches x-axis at ("<<-g<<",0)]\n";
  else
   if(x1>c)
   cout<<2*sqrt(x1-c)<<"\n";
   else
    if(x1<c)
    cout<<"Circle does not touch the x-axis\n";
  y1=pow(f,2);
  cout<<"y-intercept= ";
  if(y1==c)
  cout<<"0 [Circle touches y-axis at (0,"<<-f<<")]\n";
  else
   if(y1>c)
   cout<<2*sqrt(y1-c)<<"\n";
   else
    if(y1<c)
    cout<<"Circlr does not touch the y-axis\n";
 }
 void dcircle(int x, int y)
 {
  graph(x,y);
  circle(x/2+(u*-g),y/2-(u*-f),u*sqrt(r));
 }
}c1;

void main()
{
 clrscr();
 int gd=DETECT,gm; char ch;
 initgraph(&gd,&gm,"c:\\TURBOC3\\BGI");
 fstream file("history.txt",ios::in|ios::out|ios::app|ios::binary);
 history h,h1;
 h.enter('o');
 file.write((char*)&h,sizeof(h));

 int x=getmaxx(),y=getmaxy();
 cleardevice();
 rectangle(5,5,x-5,y-5);
 settextstyle(10,0,3);
 outtextxy(50,20,"GEOMETRICAL CALCULATOR");
 settextstyle(6,0,2);
 outtextxy(50,150,"Enter any one of the following:");
 outtextxy(50,200,"For Line: 'l'; For Circle: 'c'; For History: 'h'");
 outtextxy(50,400,"To exit enter any other key");
 cin>>ch;
 cleardevice();

 if(ch=='l'||ch=='L')
 {
  h1.enter('l');
  file.write((char *)&h1,sizeof(h1));
  cout<<"\t\tEnter equation of line in form:\n";
  cout<<"\t\tax+by+c=0";
  l1.getval();
  l1.calc();
  getch();
  l1.dline(x,y);
 }

 if(ch=='c'||ch=='C')
 {
  h1.enter('c');
  file.write((char*)&h1,sizeof(h1));
  cout<<"\t\tEnter equation of circle in the form:\n";
  cout<<"\t\tx^2+y^2+ax+by+c=0";
  c1.getval();
  c1.calc();
  getch();
  c1.dcircle(x,y);
 }

 if(ch=='h'||ch=='H')
 {
  h1.enter('h');
  file.write((char*)&h1,sizeof(h1));
  history h2;
  file.seekg(0);
  while(!file.eof())
  {
   file.read((char*)&h2,sizeof(h2));
   h2.disp();
  }
 }

 file.close();
 getch();
 closegraph();
}

