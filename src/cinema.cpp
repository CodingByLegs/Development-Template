
#include "Cinema.h"

/*

*/
TableForDay* Cinema::get_info_for_3days(int day) {
  TableForDay *res;
  int i, k, l, j;
  res = new TableForDay[3];
  i = tableMonth.daysAvable;
  if (tableMonth.daysAvable > 28)
    throw logic_error("Not eneough days to dispaly");
  for (i = 0; i < 3; ++i) {
    for (k = 0; k < tableMonth.table[day + i].countOfFilms; ++k) {
      // day on 1 less then must
      res[i].films[k].duration = tableMonth.table[day + i].films[k].duration;
      res[i].films[k].name = tableMonth.table[day + i].films[k].name;
      res[i].films[k].numOfFilm = tableMonth.table[day + i].films[k].numOfFilm;
      res[i].films[k].numOfHall = tableMonth.table[day + i].films[k].numOfHall;
      res[i].films[k].timeStart = tableMonth.table[day + i].films[k].timeStart;
    }
    for (k = 0; k < 5; ++k) {
      for (l = 0; l < 10; ++l) {
        for (j = 0; j < 15; ++j) {
          res[i].halls[k].hall[l][j] = tableMonth.table[day + i ].halls[k].hall[l][j];
        }
      }
    }
    res[i].countOfFilms = tableMonth.table[day + i].countOfFilms;
  }
  return res;
}

void Cinema::add_new_day(Film *film, int _countOfFilms) {
  int i;
  Hall me;
  if (tableMonth.daysAvable == 0) {
    throw logic_error("Not avable days to add new day");
    return;
  }
  for (i = 0; i < _countOfFilms; ++i)
    tableMonth.table[30 - tableMonth.daysAvable].films[i] = film[i];
  tableMonth.table[30 - tableMonth.daysAvable].countOfFilms = _countOfFilms;
  tableMonth.daysAvable--;
  // rest will be do automaticly
}

void Cinema::move_array() {
  int i, j, k, m, l;
  for (i = 0; i < 30; ++i) {
   tableMonth.table[i].countOfFilms = tableMonth.table[i + 1].countOfFilms;
    for (j = 0; j < tableMonth.table[i + 1].countOfFilms; ++j)
      tableMonth.table[i].films[j] = tableMonth.table[i + 1].films[j];
    for (l = 0; l < 5; ++l)
      for (m = 0; m < 15; ++m)
        for (k = 0; k < 10; ++k)
          tableMonth.table[i].halls[l].hall[m][k].isFree = tableMonth.table[i + 1]
          .halls[l].hall[m][k].isFree;
  }
}

