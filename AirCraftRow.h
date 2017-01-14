#include <string>
/*
  Header file for the AirCraftRow class.
  Student: Aldo Tali
  ID: 21500097
  Bilkent University ComputerEngineering Department
*/
class AirCraftRow{
public:
    AirCraftRow (const int no, const int rowNo, const int seats);
    ~AirCraftRow();

    int getSeats();
    int getNumber();

    int reserveSeat(const int flight, const char seat,const int resCode);
    int cancelReserv(const int resCode);
    int getNoOfFreeSeats();
    int checkReservation (const int flight, const char seat,const int resCode);

    void showReserv(const int resCode);
    bool checkRes(const int resCode);

    void showSeats();

private:
    int flightNo;
    int row;
    int numOfSeats;
    int freeSeats;
    int* seatings;
};


