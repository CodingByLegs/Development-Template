#ifndef INCLUDE_TICKETOFFICE_H_
#define INCLUDE_TICKETOFFICE_H_

#pragma once

#include "Cinema.h"
#include <locale.h>
#include <time.h>
using namespace std;


class ReserveredTickets {
public:
  int day;  // 0-30
  int count;
  int numOfFilm;
  int ID;
  bool IsVip;
  bool IsPaid;

  ReserveredTickets() {
    day = 0;
    count = 0;
    numOfFilm = 0;
    IsVip = false;
    IsPaid = false;
    ID = -1;
  }
};



class TicketOffice: public Cinema {
public:
  time_t t;
  tm* time1;
  int dayToday, dayNow;
  ReserveredTickets *reserved;
  int sizeOfreservered, longOfreservered;
  int numOfTicket = 1;
  const int hall_1_3_CostUssual = 200;
  const int hall_1_3_CostVIP = 350;
  const int hall_4_5_CostUssual = 300;
  const int hall_4_5_CostVIP = 500;

  TicketOffice() {
    reserved = new ReserveredTickets[1];
  }
  void startTimer();
  void menu();
  int TakeOrder(TableForDay &tbl, int j, int day, bool willPay);
  void startOffice();
  void colibrateDate();
  void checkDate();
  int countCost(int _numOfPlaces, bool VIP, int _numOfFilm, int day);
  void disableBook(TableForDay &tbl, int day, int _numOfplaces,bool VIP,
    int _numOfFilms);
  int reserve_place(TableForDay &tbl, int _numOfPlaces, bool VIP,
    int _numOfFilm, bool check);
  ReserveredTickets* resizeReserved(ReserveredTickets *arr);
  void addReserve(int _day, int _count, bool _IsVip, bool IsPaid,
    int _numOfFilm);
  void shiftReserve(ReserveredTickets* arr, int shift);
};


#endif  // INCLUDE_TICKETOFFICE_H_
