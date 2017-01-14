/*
  The member functions of the AirCraftRow class. The following represents a single
  row in the plane;
  Student: Aldo Tali
  ID: 21500097
  Bilkent University ComputerEngineering Department
*/

#include <iostream>
using namespace std;
#include "AirCraftRow.h"
#include <iomanip>
#include <string>

//constructor for the row of the plane class
AirCraftRow::AirCraftRow(const int no, const int rowNo, const int seat){
      flightNo = no;
      row = rowNo;
      numOfSeats = seat;
      freeSeats = 0;
      seatings = new int[numOfSeats];

      //initializes each seat
      for (int i = 0; i < numOfSeats; i++)
          seatings[i] = 0;
}

//deconstructor
AirCraftRow :: ~AirCraftRow(){
            delete[] seatings;
}

//displays the availability of the seats
void AirCraftRow :: showSeats() {
     cout<<row<<setw(2);
     for (int i = 0; i < numOfSeats; i++){
         if ((int)seatings[i] == 0)
         cout<<"O"<< setw(2);
         else
         cout<<"X"<< setw(2);
         //cout<<seatings[i]<< setw(2);
     }
}

//chekcs whether a reservation can be made
int AirCraftRow:: checkReservation (const int flight, const char seat,const int resCode){
    if (seatings[seat-65] == 0)
       return 1;
    return -1;
}

//reserves a seat under a reservation code if the seat is empty
int AirCraftRow:: reserveSeat(const int flight, const char seat,const int resCode){

    int index = (int) seat - 65;
    //if seat is empty reserve it
    if (seatings[index] <= 0){
       seatings[index] = resCode;
       return 1;
    }
    else {
         return -1;
    }
}

//returns the number of seats in the row
int  AirCraftRow:: getSeats(){
     return numOfSeats;
}

//returns the fliht number
int  AirCraftRow:: getNumber(){
     return flightNo;
}

//cancels a reservation and makes the seats available again
int AirCraftRow:: cancelReserv(const int resCode){
    int  index = -1;
     for ( int i = 0; i < numOfSeats; i++){
          if (seatings[i] == resCode){
             seatings[i] = 0;
             index = 1;
          }
     }
     //freeSeats++;
     return index;
}

//displays the reserved seats
void AirCraftRow :: showReserv(const int resCode){

     //iterates through the seats, an empty seat is an O and an occupied seat is an X
     for ( int i = 0; i < numOfSeats; i++){
          if (seatings[i] == resCode){
             cout<<row<<char(i+65)<<setw(2);
          }
     }
}

//checks whether a reservation of a given code exists
bool AirCraftRow :: checkRes(const int resCode){
     for (int i = 0; i < numOfSeats; i++)
         {
              if ( seatings[i] == resCode){
                 return true;
              }
         }
     return false;
}

//returns the number of available seats in this row
int AirCraftRow :: getNoOfFreeSeats(){
    freeSeats = 0;
    for (int i = 0; i < numOfSeats; i++)
        if (seatings[i] == 0)
        freeSeats++;
    return freeSeats;
}

