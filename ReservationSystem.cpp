/*
  The memeber functions for the ReservationSystem class.
  A wgole reservation system is a collection of different flights
  Student: Aldo Tali
  ID: 21500097
  Bilkent University ComputerEngineering Department
*/
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <string>
using namespace std;
#include "ReservationSystem.h"

//constructor for the reservation system
ReservationSystem :: ReservationSystem(){
                  resCodes = NULL;
                  numOfRes = 0;
                  resCode = 0;
                  numOfFlights = 0;
                  theFlights = new Flight*[numOfFlights];
}

//destructor
ReservationSystem:: ~ReservationSystem(){
     for (int i = 0; i < numOfFlights; i++){
         delete theFlights[i];
     }
     delete[] theFlights;
     delete[] resCodes;
}

//adds a flight to the system
void ReservationSystem:: addFlight(const int flightNo, const int rowNo, const int seatNo) {

                //checks whether the flight exists already
                for (int i  = 0; i < numOfFlights; i++)
                {
                    if (theFlights[i]->getNumber() == flightNo){
                       cout<<"This flight ("<<flightNo<<") already exists"<<endl;
                       return;
                    }
                }

                //dynamically allocates a temporary array in order to increase the size, and then deallocates the old one
                Flight** temp = new Flight*[numOfFlights+1];
                for(int i = 0; i < numOfFlights; i++){
                        temp[i] = theFlights[i];
                }
                delete[] theFlights;
                temp[numOfFlights] = new Flight(flightNo, rowNo, seatNo);
                theFlights = temp;
                numOfFlights++;

                cout<<"Flight "<<flightNo<<" has been added"<<endl;
}

//displays all the flights that are available
void ReservationSystem:: showAllFlights(){
     if (numOfFlights == 0)
     cout<<"No flights exist yet"<<endl<<endl;
     else{
          cout<<endl;
          cout<< "Flights currently operated: "<<endl;
          for (int i = 0; i < numOfFlights; i++){
              cout <<"Flight " <<setw(2)<<theFlights[i]->getNumber()<<setw(2)<<
              "("<<theFlights[i]->getTotalSeats()<<setw(2)<<" available seats)"<<endl;
              }
          cout<<endl;
     }

}

//determines the reservation codes
void ReservationSystem:: setResCode()
{
     numOfRes = numOfRes +1;
     resCode = resCode +1;
}

//return the reservation codes
int ReservationSystem:: getResCode()
{
     return resCode;
}

//cancels a flight by taking its number as a parameter
void ReservationSystem:: cancelFlight( const int flightNo ){

     //checks to see whether the flight already exists
     int index = -1;
     for (int i= 0; i < numOfFlights; i++ ){
         if (theFlights[i]->getNumber() == flightNo){
            index = i; i = numOfFlights;
         }
     }

     if (index < 0)
        cout<<"The flight with number : "<<flightNo<<" does not exist"<<endl;
     else{
          //creates a temporary double pointer array for the flights and deallocates them when not needed anymore
          //lowers the size of the array by 1
          Flight** temp = new Flight*[numOfFlights - 1];

          for (int i = 0; i < index; i++){
              temp[i] = theFlights[i];
          }
          for (int i = index+1; i <numOfFlights; i++){
              temp[i-1] = theFlights[i];
          }
          delete theFlights[index];
          delete[] theFlights;
          numOfFlights--;
          theFlights = temp;

          cout<<"The "<<flightNo<<" amd all of its reservations are canceled"<<endl<<endl;
     }
}

//displays the data of a flight
void ReservationSystem:: showFlight( const int flightNo ){
     int index = -1;
     for (int i = 0; i < numOfFlights; i++){
         if (theFlights[i]->getNumber() == flightNo) {
            index = i;
            i = numOfFlights;
         }
     }

     if (index < 0)
     cout<<"The flight : "<<flightNo<<" does not exist"<<endl;
     else{
         theFlights[index]->showSeatings();
         cout<<endl;
      }
}

//makes a reservation on the proper given lcations of the rows and columns
int ReservationSystem :: makeReservation( const int flightNo, const int numPassengers,
                      const int *seatRow, const char *seatCol ){

     int index = -1;
     //checks to see whether the chosen flight exists
     for (int i = 0; i < numOfFlights; i++){
         if (theFlights[i]->getNumber() == flightNo) {
            index = i;
            i = numOfFlights;
         }
     }
     if (index < 0){
     cout<<"The flight : "<<flightNo<<" does not exist"<<endl; return -1;}
     else{
            int flag = -1;
            flag = theFlights[index]->reserveSeats(flightNo, numPassengers,seatRow,seatCol,resCode+1);
            if (flag < 0)
            return -1;
            else if (flag >= 0)
            {
                int* temp = new int[numOfRes+1];
                    for (int i = 0; i < numOfRes; i++)
                    {
                        temp[i] = resCodes[i];
                    }
                    temp[numOfRes] = getResCode();
                    resCode++;
                    numOfRes++;
                    delete[] resCodes;
                    //resCodes = new int[numOfRes];
                    resCodes = temp;
                    return resCode;
            }
            else{
                resCode--;
                return -1;
            }

      }
}

//cancels a previoulsy made reservation for a flight
void ReservationSystem :: cancelReservation( const int resCode ){
     int index = -1;
     flag = false;

     //checks to see whether there was a previous reservation with the given code
     for (int i = 0; i < numOfFlights; i++){
          index = theFlights[i]->cancelRes( theFlights[i]->getFlight(), resCode);
          if (index > 0)
             flag = true;
      }

     if (flag)
    {
         int index = 0;
      //   int* temp =new int[numOfRes - 1];
         for (int j =0; j < numOfRes; j++){
             if (resCodes[j] == resCode)
             {
	resCodes[j] = 0;
	break;
             }
            //in case the system needs to have a reuse codes option in the future
            /* else
             {
                 temp[index] = resCodes[j];
                 index++;
             }*/
     }

/*in case the system needs to have a reuse codes option in the future
     delete[] resCodes;
     resCodes = temp;
     numOfRes = numOfRes -1;*/

    }
else  cout<<"No reservations under code "<<resCode<<endl<<endl;
}


//displays a reservation by knowing its reservation code
void ReservationSystem :: showReservation( const int resCode ){
     bool flag = false;
     bool flag2 = false;

     for (int i = 0; i < numOfRes; i++){
        if (resCodes[i] == resCode){
            flag = true;
            i = numOfRes;
        }
     }
     if (!flag) {
     cout<<"No reservations are found under code "<<resCode<<endl<<endl; }
     else{
          for (int i = 0; i < numOfFlights; i++){
               flag2 = theFlights[i]->checkReservation( theFlights[i]->getFlight(), resCode);
               if(flag2)
               theFlights[i]->showRes( theFlights[i]->getFlight(), resCode);
          }
     }
}


