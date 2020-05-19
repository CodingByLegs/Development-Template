#include "ticketOffice.h"
#include <iostream>

int main() {
  TicketOffice x;
  Film *data;
  string names[5];
  int i;
  /*
  int *arr, *newArr;
  arr = new int[5];
  newArr = new int[5];
  for (int i = 0; i < 5; ++i) {
    arr[i] = i + 1;
    newArr[i] = i + 10;
  }
  newArr[4] = arr[9];
  for (int i = 0; i < 7; ++i)
    cout << newArr[i] << " ";
  cout << endl;
  */
  names[0] = "A";
  names[1] = "B";
  names[2] = "C";
  names[3] = "C";
  names[4] = "N";
  data = new Film[5];
  for (i = 0; i < 5; ++i) {
    data[i].name = names[i];
    data[i].timeStart = 1420 + i * 20;
    data[i].duration = 100 + i * 10;
    data[i].numOfFilm = i;
    data[i].numOfHall = i + 1;
  }
  x.add_new_day(data, 4);
  x.add_new_day(data, 5);
  x.add_new_day(data, 4);
  x.add_new_day(data, 4);
  x.add_new_day(data, 4);
  x.colibrateDate();
  x.startOffice();
  x.menu();
}
