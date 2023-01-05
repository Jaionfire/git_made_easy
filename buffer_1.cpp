#include <iostream>
#include<fstream>
#include<thread>
#include<atomic>
#include<chrono>
#include<time.h>
using namespace std;
fstream fin;
fstream fout;
void process_convolution(int *p);
//void display();
void file_read_write_to_buffer();
int ab[5]={2,3,4,5,6};
int store,cnt1=0;
int *p=new int[5];
int j=0,m=0;
int result[5];
int result1[100];
int main()
{
   thread t1(file_read_write_to_buffer);
   thread t2(process_convolution,std::ref(p));
   t1.join();
   t2.join();
   fout.open("output.txt",ios::out);
   for(int t=1;t<=cnt1;t++)
   {
      fout<<result1[t]<<endl;
   }
   fout.close();
   return 0;
}
void file_read_write_to_buffer()
{
   int k=0,cnt=0;
   char str[5];
   fin.open("input.txt",ios::in);
   //fout.open("output.txt",ios::out);
   if(!fin)
   {cout<<"No such file....."<<endl;}
   else
   {
      while(!fin.eof())
      {
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout<<"hii"<<endl;
        fin.getline(str,5);
        p[k++]=atoi(str);
        cnt1++;
        cnt++;
        if(cnt==5)
        {
         k=0;
        }
        auto start = chrono::steady_clock::now();
        process_convolution(p);
        auto end = chrono::steady_clock::now();
        cout<<chrono::duration_cast<chrono::milliseconds>(end-start).count()<< " milliseconds" << endl;
      }
      fin.close();
      }
}
void process_convolution(int *p)
{
   //cnt1++;
   this_thread::sleep_for(chrono::milliseconds(10));
   this_thread::sleep_for(chrono::milliseconds(1100));
  //cin>>p[0];
   cout<<"hello"<<endl;
   //result[0]=p[0]*ab[0];
   //store=result[0];
   int store1=0;
   for(int i=0;i<5;i++)
   {
     // cnt1++;
      //cin>>p[i];
      store1+=p[i]*ab[i];
      //store1+=store;
      result[i]=store1;
      //store=0;
      store1=0;
   }
   for(int i=0;i<5;i++)
   {
      result1[m]+=result[i];
   }
   m++;
   for(int l=0;l<5;l++)
   {
      cout<<p[l]<<endl;
   }
   cout<<"////////////////.............."<<endl;
  // this_thread::sleep_for(chrono::milliseconds(1100));
}
