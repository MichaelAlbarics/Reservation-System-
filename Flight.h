/*
  Header file for the Flight class.
  Student: Aldo Tali
  ID: 21500097
  Bilkent University ComputerEngineering Department
*/

#include "AirCraftRow.h"
class Flight{
      public:
      //const char LETTERS[] = {'A','B','C','D','E','F'};
      Flight (const int flightNum, const int rows, const int seatNo);
      ~Flight();

      int getFlight();
      int getTotalSeats();
      int getNumber();

      int reserveSeats(const int flight, int numOfPass,const int *row, const char*col, const int resCode);
      int cancelRes(const int flightNo, const int resCode);

      void showFlight();
      void showSeatings();
      void showRes(const int flightNo,const int resCode);

      bool checkReservation( const int flightNo,const int resCode );

      private:
               int flightNo;
               int numOfRows;
               int seatsInRow;
               AirCraftRow** seating;
};


