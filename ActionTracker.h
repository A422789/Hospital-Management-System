#ifndef ACTIONTRACKER_H
#define ACTIONTRACKER_H 
#include "PatientRecord.h"
#include "StaffUser.h"
#include "AccountManager.h"
#include "PatientManager.h"
#include <iostream>
using namespace std;
struct Action{
          string type; 
          string target; 
          PatientRecord pData;
          StaffUser sData;
     };
     struct Node{
        Action data;
        Node* next;
     };
class ActionTracker{
    private:
     Node* top=NULL;
    
     
    public:
     void pushAction(Action a){
            Node* newNode=new Node();
            newNode->data=a;
            newNode->next=top;
            top=newNode;
        }
     Action popAction(){
      if(top==NULL){
        cout<<"No more Actions to Unod!";
        Action emptyAction;
            emptyAction.type = "NONE"; 
            return emptyAction;
     
         }
      Node* temp=top;
      top=top->next;
      Action data=temp->data;
      delete temp;
      return data;
      
        }
    void undo(AccountManager &accManager, PatientManager &paManager){
        Action lastAciton=popAction();
        if(lastAciton.target=="Staff"){
            if(lastAciton.type=="DELETE"){
             //بدي اعمل ادد للنسخة الي عندي من البيانات للستف 
             accManager.addUser(lastAciton.sData);
            }else if(lastAciton.type=="ADD"){
             accManager.deleteUser(lastAciton.sData);
            }else{
                cout<<"last Action type not defind!";
            }
        }else if(lastAciton.target=="Patient"){
             if(lastAciton.type=="DELETE"){
             //بدي اعمل ادد للنسخة الي عندي من البيانات للبيشنت 
             paManager.addPatient(lastAciton.pData);
            }else if(lastAciton.type=="ADD"){
              paManager.deletePatient(lastAciton.pData);
            }else{
                cout<<"last Action type not defind!";
            }
        }else{
            cout<<"last Action target not defined!";
        }
    }
     ~ActionTracker(){
        while (top != NULL) {
        Node* temp = top;
        top = top->next;
        delete temp;
    }
}
};

#endif