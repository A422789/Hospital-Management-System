#ifndef EMERGENCYROOM_H
#define EMERGENCYROOM_H
#include "PatientRecord.h"
#include <iostream>
using namespace std;
class EmergencyRoom{
 private:
 PatientRecord arr[100];
  int top=-1;
 int size;
 public:
 void setSize(int s){
    size=s;
 }
 int getSize(){
    return size;
 }
 void addCase(PatientRecord p){
         if(top>=99){
            cout<<"The stack is overFlow";
        }else{
           arr[++top]=p;
           setSize(top+1);
        }
 }
 void bubbleSort(){
    for(int i=0;i<top;i++){
        for(int j=0;j<top-i;j++){
            if(arr[j].severity<arr[j+1].severity){
               PatientRecord temp=arr[j];
               arr[j]=arr[j+1];
               arr[j+1]=temp; 
            }
        }
    }
 }
 void displayER(){
    cout<<"====The cases displayed by the highest severity====="<<endl;
    for(int i=0;i<getSize();i++){
        cout<<"The case number("<<i+1<<"):"<<endl;
         cout<<"The Patient severity Number:"<<arr[i].severity<<endl;
        cout<<"The Patient id:"<<arr[i].id<<endl;
        cout<<"The Patient name:"<<arr[i].name<<endl;
        cout<<"The Patient disease:"<<arr[i].disease<<endl;
       
    }
 }
};
#endif