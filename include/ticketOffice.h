#ifndef INCLUDE_TICKETOFFICE_H_
#define INCLUDE_TICKETOFFICE_H_

#pragma once

#include "Cinema.h"
#include <locale.h>
#include <time.h>
using namespace std;

class TicketOffice: public Cinema {
public:
  time_t t;
  tm* time1;
  int dayToday, dayNow;
  const int hall_1_3_CostUssual = 200;
  const int hall_1_3_CostVIP = 350;
  const int hall_4_5_CostUssual = 300;
  const int hall_4_5_CostVIP = 500;

  void startTimer();
  void menu();
  int TakeOrder(TableForDay tbl, int j, int i, int day);
  void startOffice();
  void colibrateDate();
  void checkDate();
  int checkPlace(int _numOfPlaces, bool VIP, int _numOfFilm);
  int countCost(int _numOfPlaces, bool VIP, int _numOfFilm, int day);
  void disableBook(TableForDay tbl, int day, int _numOfplaces,bool VIP,
    int _numOfFilms);
  int reserve_place(TableForDay tbl, int _numOfPlaces, bool VIP,
    int _numOfFilm, bool check);

};


#endif  // INCLUDE_TICKETOFFICE_H_
