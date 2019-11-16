/*
Student Name:
Student Number:
Project Number: 3
Compile Status: [SUCCESS/FAIL]
Running Status: [SUCCESS/FAIL]
Notes: Anything you want to say about your code that will be helpful in the grading process.
*/
#include "SeatOperations.h"

using namespace std;

SeatOperations::SeatOperations(int N, int M){
    // IMPLEMENT ME!
    for(int i=0;i<N;i++){
        lines[0].push_back(Person());
    }
    for(int k=0;k<M;k++){
        lines[1].push_back(Person());
    }
}

void SeatOperations::addNewPerson(int personType, const string& ticketInfo){
    // IMPLEMENT ME!
    char lineT = ticketInfo[0];
    string seatNmb = ticketInfo.substr(1,ticketInfo.length());
    int ticketN = stoi(seatNmb);
    Person newC = Person();
    newC.seatNumber = ticketN;
    if(lineT=='A'||lineT=='a'){
        newC.line=0;
    }
    else{
        newC.line=1;
    }
    newC.type=personType;
    Person current=newC;
    Person old;
    while(lines[current.line][current.seatNumber%lines[current.line].size()].type!=0){
        if(lines[current.line][current.seatNumber%lines[current.line].size()].type==1){
            if(current.line==0){
                old = lines[1][current.seatNumber%lines[1].size()];
                lines[1][current.seatNumber%lines[1].size()] = current;
                current = old;
                continue;
            }
            else{
                old = lines[0][current.seatNumber%lines[0].size()];
                lines[0][current.seatNumber%lines[0].size()] = current;
                current = old;
                continue;
            }
        }
        else if(lines[current.line][current.seatNumber%lines[current.line].size()].type==2){
            if(current.seatNumber%lines[current.line].size()==0){
                if(current.line==0){
                    old=lines[1][1];
                    lines[1][1] = current;
                    current=old;
                    continue;
                }
                else{
                    old=lines[0][1];
                    lines[0][1] = current;
                    current = old;
                    continue;
                }
            }
            else{
                old=lines[current.line][(current.seatNumber+1)%lines[current.line].size()];
                lines[current.line][(current.seatNumber+1)%lines[current.line].size()] = current;
                current=old;
                continue;
            }
        }
        else{
          if(current.line==0){
              if(current.seatNumber%lines[0].size()==0){
                  old=lines[1][(current.type3LastOperation+1)*(current.type3LastOperation+1)];
                  lines[1][(current.type3LastOperation+1)*(current.type3LastOperation+1)]=current;
                  current.type3LastOperation +=1;
                  current=old;
                  continue;
              }
              if(lines[0].size()>=(current.type3LastOperation+1)*(current.type3LastOperation+1)+(current.seatNumber%lines[0].size())){
                  old=lines[0][(current.seatNumber%lines[0].size())+(current.type3LastOperation+1)*(current.type3LastOperation+1)];
                  lines[0][(current.seatNumber%lines[0].size())+(current.type3LastOperation+1)*(current.type3LastOperation+1)]=current;
                  current.type3LastOperation +=1;
                  current=old;
                  continue;
              }
              else{
                  old=lines[1][(current.type3LastOperation+1)*(current.type3LastOperation+1)+current.seatNumber%lines[0].size()-lines[0].size()];
                  lines[1][(current.type3LastOperation+1)*(current.type3LastOperation+1)+current.seatNumber%lines[0].size()-lines[0].size()]=current;
                  current.type3LastOperation +=1;
                  current=old;
                  continue;
              }
          }
          else{
              if(current.seatNumber%lines[1].size()==0) {
                  old = lines[0][(current.type3LastOperation + 1) * (current.type3LastOperation + 1)];
                  lines[0][(current.type3LastOperation + 1) * (current.type3LastOperation + 1)] = current;
                  current.type3LastOperation +=1;
                  current = old;
                  continue;
              }
              if(lines[1].size()>=(current.type3LastOperation+1)*(current.type3LastOperation+1)+(current.seatNumber%lines[1].size())){
                  old=lines[1][(current.seatNumber%lines[1].size())+(current.type3LastOperation+1)*(current.type3LastOperation+1)];
                  lines[1][(current.seatNumber%lines[1].size())+(current.type3LastOperation+1)*(current.type3LastOperation+1)]=current;
                  current.type3LastOperation += 1;
                  current=old;
                  continue;
              }
              else{
                  old=lines[0][(current.type3LastOperation+1)*(current.type3LastOperation+1)+current.seatNumber%lines[1].size()-lines[1].size()];
                  lines[0][(current.type3LastOperation+1)*(current.type3LastOperation+1)+current.seatNumber%lines[1].size()-lines[1].size()]=current;
                  current.type3LastOperation +=1;
                  current=old;
                  continue;
              }
          }
        }
    }
    lines[current.line][current.seatNumber%lines[current.line].size()]=current;

}

void SeatOperations::printAllSeats(ofstream& outFile){
    for(int i=1;i<N;i++){
        if(lines[0][i].type==0){
            outFile<< 0<< endl;
            continue;
        }
        if(lines[0][i].line==0){
            outFile<< "A";
        }
        else{
            outFile<<"B";
        }
        outFile<<lines[0][i].seatNumber;
    }
    if(lines[0][0].type==0){
        outFile<<0<<endl;
    }
    else{
        outFile<<lines[0][0].seatNumber<<endl;
    }
    for(int i=1;i<M;i++){
        if(lines[1][i].type==0){
            outFile<< 0<< endl;
            continue;
        }
        if(lines[1][i].line==0){
            outFile<< "A"<<endl;
        }
        else{
            outFile<<"B"<<endl;
        }
        outFile<<lines[1][i].seatNumber;
    }
    if(lines[1][0].type==0){
        outFile<<0<<endl;
    }
    else{
        outFile<<lines[1][0].seatNumber<<endl;
    }

}

// YOU CAN ADD YOUR HELPER FUNCTIONS