#ifndef INCLUDE_CINEMA_H_
#define INCLUDE_CINEMA_H_

#pragma once

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Place {
public:
  bool isFree;
  bool isVIP;
  Place() { isVIP = false; isFree = true; }

};

class Hall {
public:
  Place hall[15][10];
  Hall() {
    int i, j;
    // 50 places is VIP
    for (i = 0; i < 5; ++i)
      for (j = 0; j < 10; ++j)
        hall[i][j].isVIP = true;
  }
  friend bool operator==(Hall const &c1, Hall const &c2);
  Hall& operator=(Hall &c1) {
    int i, j;
    for (i = 0; i < 15; ++i) {
      for (j = 0; j < 10; ++j) {
        hall[i][j].isFree = c1.hall[i][j].isFree;
        hall[i][j].isVIP = c1.hall[i][j].isVIP;
      }
    }
    return *this;
  }
};



class Film {
public:
  string name;
  int numOfHall;
  int timeStart;
  int duration;
  int numOfFilm;

  Film() {
    name = " ";
    numOfHall = -1;
    timeStart = -1;
    duration = -1;
    numOfFilm = -1;
  }
  Film(string _name, int _numOfHall, int _timeStart, int _duration, int _numOfFilm) {
    name = _name;
    numOfHall = _numOfHall;
    timeStart = _timeStart;
    duration = _duration;
    numOfFilm = _numOfFilm;
  }
  Film& operator=(Film &c1) {
    name = c1.name;
    numOfHall = c1.numOfHall;
    timeStart = c1.timeStart;
    duration = c1.duration;
    numOfFilm = c1.numOfFilm;
    return *this;
  }
  friend bool operator==(Film const &c1, Film const &c2);

};



class TableForDay {
public:
  int countOfFilms;
  Film *films;
  Hall halls[5];
  TableForDay() {
    films = new Film[15];
    countOfFilms = 0;
  }
  ~TableForDay() {
    countOfFilms = 0;
    delete[] films;
  }
  TableForDay& operator=(TableForDay &c1) {
    int i;
    countOfFilms = c1.countOfFilms;
    for (i = 0; i < countOfFilms; ++i)
      films[i] = c1.films[i];
    for (i = 0; i < 5; ++i)
      halls[i] = c1.halls[i];
    return *this;
  }
  friend bool operator==(TableForDay const &c1,TableForDay const &c2);
};



class TableFor30Days {
public:
  TableForDay *table;
  int daysAvable;
  TableFor30Days() {
    table = new TableForDay[30];
    daysAvable = 30;
  }
  TableFor30Days& operator=(TableFor30Days &c1) {
    int i, j, k, m, l;
    for (i = 0; i < 30; ++i) {
      table[i].countOfFilms = c1.table[i].countOfFilms;
      for (j = 0; j < c1.table[i].countOfFilms; ++j)
        table[i].films[j] = c1.table[i].films[j];
      for (l = 0; l < 5; ++l)
        table[i].halls[l] = c1.table[i].halls[l];
    }
    return *this;
  }
  ~TableFor30Days() {
    daysAvable = 0;
    delete[] table;
  }
  friend bool operator==(TableFor30Days const &c1, TableFor30Days const &c2);
};

class Cinema {
public:
  TableForDay tableToday;
  TableFor30Days tableMonth;

  //int reserve_place(int _numOfPlaces, bool VIP, int numOfFilm, bool check);
  TableForDay* get_info_for_3days(int day);
  void add_new_day(Film *film, int _countOfFilms);
  void move_array();
};


#endif  // INCLUDE_CINEMA_H_
