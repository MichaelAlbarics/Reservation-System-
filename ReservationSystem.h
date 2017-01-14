#include "Flight.h"
/*
  Header file for the REservationSystem
  Student: Aldo Tali
  ID: 21500097
  Bilkent University ComputerEngineering Department
*/

class ReservationSystem {
      public:
             ReservationSystem();
             ~ReservationSystem();

             void addFlight( const int flightNo, const int rowNo, const int seatNo );
             void cancelFlight( const int flightNo );
             void showAllFlights();
             void showFlight( const int flightNo );
             int makeReservation( const int flightNo, const int numPassengers,
                                  const int *seatRow, const char *seatCol );
             void cancelReservation( const int resCode );
             void showReservation( const int resCode );

             bool checkReservation( const int resCode );
             void  setResCode();
             int  getResCode();
// ...
// you may define additional member functions and data members, if necessary.

private: Flight** theFlights;
         int numOfFlights;
         int* resCodes;
         int numOfRes;
         int resCode;
         bool flag;

};


