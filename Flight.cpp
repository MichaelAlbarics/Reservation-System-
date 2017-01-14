/*
  The memeber functions for the Flight class.
  A single Flight corresponds to the plane with the rows and columns
  Student: Aldo Tali
  ID: 21500097
  Bilkent University ComputerEngineering Department
*/

#include <iostream>
using namespace std;
#include "Flight.h"
#include <iomanip>

//constructor for the single flight
Flight:: Flight(const int flightNum, const int rows,const int seatNo){
         flightNo = flightNum;
         numOfRows = rows;
         seatsInRow = seatNo;
         seating = new AirCraftRow*[numOfRows];

         //initializes each row of the flight
         for(int i = 0; i < numOfRows; i++){
                 seating[i] = new AirCraftRow(flightNo, i+1,seatNo);
         }
}

//destructor
Flight::~Flight(){
       for (int i = 0; i < numOfRows; i++){
           delete seating[i];
       }
       delete []seating;
}

//returns the number of the flight
int Flight:: getFlight(){
    return flightNo;
}

//returns the number of the total seats in the flight
int Flight:: getTotalSeats(){
    int seats = 0;
    for (int i = 0; i < numOfRows; i++){
        seats = seats + seating[i]->getNoOfFreeSeats();
        }
    return seats;
}

//shows the seating plan for a single flight
void Flight:: showFlight(){
     cout<<endl;
     for (int i = 0; i < numOfRows; i++){
         seating[i]->showSeats();
         cout<<endl;
     }
}

//returns the flight number
int Flight:: getNumber(){
    return flightNo;
}

//shows the seating plan of the plane
void Flight::showSeatings(){
     cout<<endl;
     cout<<"Flight "<<flightNo<<" has "<<getTotalSeats()<<" available seats."<<endl<<endl<<setw(4);
     for (int j = 0; j < seatsInRow; j++){
         cout<<char(j+65)<<setw(2);
     }
     cout<<endl;
     for (int i = 0; i < numOfRows; i++)
     {
         seating[i]->showSeats();
         cout<<endl;
     }
}

//reserves the seats found and the respective indexes of rows row and columns col
int Flight:: reserveSeats(const int flight, const int numOfPass,const int *row,const char* col,const int resCode){
    int p = 1;
    int plural = 0;
    int flag;

    //checks whether there are any non available seats and strores the number of the nin availables
    for (int i = 0; i < numOfPass; i++){
       p = seating[row[i]-1]->checkReservation(flight,col[i],resCode);
       if (p < 0){
        cout<<setw(2)<<row[i]<<col[i]<<setw(2);
        plural++;
       }
    }

    if (plural > 1){
         cout<<" are not available."<<endl<<endl;
         return -1;
    }
    else if (plural == 1){
         cout<<" is not available."<<endl<<endl;
         return -1;
    }
    else {
        for (int j = 0; j < numOfPass; j++){
             flag = seating[row[j]-1]->reserveSeat(flight,col[j],resCode);
        }
            return 1;
    }
}

//cancels a reservation which was made by knowing the reservation code and the flight number
int Flight:: cancelRes(const int flightNo, const int resCode){
     int index = -1;
     int turner = -1;
     for (int i = 0; i < numOfRows; i++){
         index = seating[i]->cancelReserv(resCode);
         if (index > 0)
            turner = 1;
     }
     return turner;
     }

//shows the reservations made in a particular reservation code
void Flight::showRes(const int flightNo,const int resCode){
     cout<< "Reservations under Code "<<resCode<<" in flight "<<flightNo<<":"<<setw(2);
     for (int i = 0; i < numOfRows; i++){
         seating[i]->showReserv(resCode);
     }
     cout<<endl<<endl;

}

//checks whether a reservation on a particular flight and with a resevation code can be made
bool Flight :: checkReservation( const int flightNo,const int resCode ){
     bool flag = false;

     for (int i = 0; i < numOfRows; i++){
          flag = seating[i]->checkRes(resCode);
          if (flag)
          return true;
     }
     return flag;

}

