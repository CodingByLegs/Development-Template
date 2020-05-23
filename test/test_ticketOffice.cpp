#include <gtest/gtest.h>
#include "ticketOffice.h"

/*
  ТЕСТЫ
  тесты функций вспомогательных классов
  Тест класса Cinema
    get_info_for_3days
    add_new_day
    move_array
  Тесты класса TicketOffice
    countCost
    disableBook
    reserve_place
    resizeReserved
    addReserve
    disableReserve
*/




TEST(TestClassHall, Assignment) {
  Hall res, a, b;
  res.hall[0][0].isFree = false;
  a.hall[0][0].isFree = false;
  b = a;
  EXPECT_EQ(b, res);
}

TEST(TestClassFilm, AssignmentConstructor) {
  Film res;
  res.name = "A";
  res.duration = 200;
  res.numOfFilm = 0;
  res.numOfHall = 2;
  res.timeStart = 600;
  Film a("A", 2, 600, 200, 0);
  EXPECT_EQ(a, res);
}

TEST(TestClassFilm, Assignment) {
  Film res, b;
  res.name = "A";
  res.duration = 200;
  res.numOfFilm = 0;
  res.numOfHall = 2;
  res.timeStart = 600;
  Film a("A", 2, 600, 200, 0);
  b = a;
  EXPECT_EQ(b, res);
}

TEST(TestClassTableForDay, Assignment) {
  TableForDay res, a, b;
  Film c("A", 2, 600, 200, 0);
  Hall m;
  m.hall[0][0].isFree = false;
  res.countOfFilms = 1;
  res.films[0] = c;
  res.halls[0] = m;
  a.countOfFilms = 1;
  a.films[0] = c;
  a.halls[0] = m;
  b = a;
  EXPECT_EQ(b, res);
}

TEST(TestClassTableFor30Days, Assignment) {
  TableForDay d, f;
  TableFor30Days res, a, b;
  Film c("A", 2, 600, 200, 0);
  Hall m;
  m.hall[0][0].isFree = false;
  d.countOfFilms = 1;
  d.films[0] = c;
  d.halls[0] = m;
  res.daysAvable = 29;
  res.table[0] = d;
  a.daysAvable = 29;
  a.table[0] = d;
  b = a;
  EXPECT_EQ(b, res);
}

TEST(TestClassCinema, get_info_for_3days_not_enough_info) {
  Cinema res, a;
  TableForDay d, f, *b = new TableForDay[1];
  Hall m;
  Film c("A", 2, 600, 200, 0);
  d.countOfFilms = 1;
  d.films[0] = c;
  d.halls[0] = m;
  res.tableToday = d;
  res.tableMonth.table[0] = d;
  a.tableToday = d;
  a.tableMonth.table[0] = d;
  ASSERT_ANY_THROW(a.get_info_for_3days(0));
}

TEST(TestClassCinema, get_info_for_3days) {
  Cinema res, a, b;
  TableForDay d, f;
  Hall m;
  int i;
  Film c("A", 2, 600, 200, 0);
  d.countOfFilms = 1;
  d.films[0] = c;
  d.halls[0] = m;
  for (i = 0; i < 3; ++i) {
    res.tableMonth.table[i] = d;
    a.tableMonth.table[i] = d;
    res.tableMonth.daysAvable--;
    a.tableMonth.daysAvable--;
  }
  b.tableMonth.table = a.get_info_for_3days(0);
  EXPECT_EQ(b.tableMonth.table[0], res.tableMonth.table[0]);
  EXPECT_EQ(b.tableMonth.table[1], res.tableMonth.table[1]);
  EXPECT_EQ(b.tableMonth.table[2], res.tableMonth.table[2]);
}

TEST(TestClassCinema, add_new_day_not_avable_days_to_add) {
  Cinema res;
  Hall m;
  Film c("A", 2, 600, 200, 0), *n = new Film[1];
  int i;
  n[0].duration = 120;
  n[0].name = "B";
  n[0].numOfFilm = 0;
  n[0].numOfHall = 3;
  n[0].timeStart = 700;
  for (i = 0; i < 30; ++i) {
    res.tableMonth.table[i].countOfFilms = 1;
    res.tableMonth.table[i].films[0] = n[0];
    res.tableMonth.daysAvable--;
  }
  ASSERT_ANY_THROW(res.add_new_day(n, 1));
}


TEST(TestClassCinema, add_new_day) {
  Cinema res, a;
  Hall m;
  Film c("A", 2, 600, 200, 0), *n = new Film[1];
  int i;
  n[0].duration = 120;
  n[0].name = "B";
  n[0].numOfFilm = 0;
  n[0].numOfHall = 3;
  n[0].timeStart = 700;
  res.tableMonth.table[0].films[0] = c;
  res.tableMonth.table[0].countOfFilms = 1;
  for (i = 0; i < 5; ++i) {
    res.tableMonth.table[0].halls[i] = m;
    a.tableMonth.table[0].halls[i] = m;
  }
  res.tableMonth.daysAvable--;
  a.tableMonth.table[0].films[0] = n[0];
  a.tableMonth.table[0].countOfFilms = 1;
  a.tableMonth.daysAvable--;
  res.add_new_day(n, 1);
  EXPECT_EQ(a.tableMonth.table[0], res.tableMonth.table[1]);
}

TEST(TestClassCinema, move_array) {
  Cinema res, a;
  Hall m;
  Film c("A", 2, 600, 200, 0), *n = new Film[30];
  int i;
  for (i = 0; i < 30; ++i) {
    n[i].duration = 120 + i;
    n[i].name = "B";
    n[i].numOfFilm = 0;
    n[i].numOfHall = 3;
    n[i].timeStart = 700 + i;
    res.tableMonth.table[i].films[0] = n[i];
    res.tableMonth.daysAvable--;
    a.tableMonth.table[i].films[0] = n[i];
    a.tableMonth.daysAvable--;
  }
  // check equals
  EXPECT_EQ(a.tableMonth.table[29], res.tableMonth.table[29]);
  a.move_array();
  EXPECT_FALSE(a.tableMonth.table[29] == res.tableMonth.table[29]);
}

TEST(TestClassTicketOffice, reserve_place_not_enought_places) {
  TicketOffice res;
  Hall m;
  Film c("A", 2, 600, 200, 0), *n = new Film[1];
  int i, j, result, test;
  n[0].duration = 120;
  n[0].name = "B";
  n[0].numOfFilm = 0;
  n[0].numOfHall = 3;
  n[0].timeStart = 700;
  res.add_new_day(n, 1);
  // reserve 40 of 50 VIP places
  for (i = 0; i < 4; ++i)
    for (j = 0; j < 10; ++j)
      res.tableMonth.table[0].halls[3].hall[i][j].isFree = false;
  result = 10;
  test = res.reserve_place(res.tableMonth.table[0], 20, true, 0, false);
  EXPECT_EQ(test, result);
}


TEST(TestClassTicketOffice, reserve_place) {
  TicketOffice res, test;
  Hall m;
  Film c("A", 2, 600, 200, 0), *n = new Film[1];
  int i, j;
  n[0].duration = 120;
  n[0].name = "B";
  n[0].numOfFilm = 0;
  n[0].numOfHall = 3;
  n[0].timeStart = 700;
  res.add_new_day(n, 1);
  test.add_new_day(n, 1);
  test.reserve_place(test.tableMonth.table[0], 20, true, 0, false);
  for (i = 0; i < 2; ++i)
    for (j = 0; j < 10; ++j)
      res.tableMonth.table[0].halls[3].hall[i][j].isFree = false;
  EXPECT_EQ(res.tableMonth.table[0].halls[3], test.tableMonth.table[0].halls[3]);
}

TEST(TestClassTicketOffice, disable_book_out_of_range_of_tableMonth) {
  TicketOffice res;
  Hall m;
  Film *n = new Film[1];
  int i, j;
  n[0].duration = 120;
  n[0].name = "B";
  n[0].numOfFilm = 0;
  n[0].numOfHall = 3;
  n[0].timeStart = 700;
  res.add_new_day(n, 1);
  res.reserve_place(res.tableMonth.table[0], 20, true, 0, false);
  ASSERT_ANY_THROW(res.disableBook(res.tableMonth.table[2], 2, 20, true, 0));
}

TEST(TestClassTicketOffice, disable_book) {
  TicketOffice res, test;
  Hall m;
  Film c("A", 2, 600, 200, 0), *n = new Film[1];
  int i, j;
  n[0].duration = 120;
  n[0].name = "B";
  n[0].numOfFilm = 0;
  n[0].numOfHall = 3;
  n[0].timeStart = 700;
  res.add_new_day(n, 1);
  test.add_new_day(n, 1);
  test.reserve_place(test.tableMonth.table[0], 20, true, 0, false);
  test.disableBook(test.tableMonth.table[0], 0, 20, true, 0);
  EXPECT_EQ(res.tableMonth.table[0].halls[3], test.tableMonth.table[0].halls[3]);
}


TEST(TestClassTicketOffice, countCost) {
  TicketOffice a;
  int res, test, i;
  Hall m;
  Film c("A", 2, 600, 200, 0), *n = new Film[1];
  n[0].duration = 120;
  n[0].name = "B";
  n[0].numOfFilm = 0;
  n[0].numOfHall = 3;
  n[0].timeStart = 600;
  res = 0.75 * a.hall_1_3_CostVIP * 20;
  a.add_new_day(n, 1);
  a.colibrateDate();
  a.startOffice();
  a.reserve_place(a.tableMonth.table[0], 20, true, 0, false);
  test = a.countCost(20, true, 0, 0);
  EXPECT_EQ(res, test);
}

TEST(TestClassTicketOfficeHelpFunctions, addReserve) {
  TicketOffice res, test;
  Hall m;
  Film c("A", 2, 600, 200, 0), *n = new Film[1];
  n[0].duration = 120;
  n[0].name = "B";
  n[0].numOfFilm = 0;
  n[0].numOfHall = 3;
  n[0].timeStart = 600;
  test.add_new_day(n, 1);
  test.colibrateDate();
  test.startOffice();
  test.addReserve(0, 20, true, false, 0);
  res.longOfreservered = 1;
  res.reserved[0].count = 20;
  res.reserved[0].day = 0;
  res.reserved[0].ID = 1;
  res.reserved[0].IsPaid = false;
  res.reserved[0].IsVip = true;
  res.reserved[0].numOfFilm = 0;
  EXPECT_EQ(res, test);
}

TEST(TestClassTicketOfficeHelpFunctions, disableReserve) {
  TicketOffice res, test;
  Hall m;
  Film c("A", 2, 600, 200, 0), *n = new Film[1];
  n[0].duration = 120;
  n[0].name = "B";
  n[0].numOfFilm = 0;
  n[0].numOfHall = 3;
  n[0].timeStart = 600;
  test.add_new_day(n, 1);
  test.colibrateDate();
  test.startOffice();
  res.add_new_day(n, 1);
  res.colibrateDate();
  res.startOffice();
  test.addReserve(0, 20, true, false, 0);
  res.addReserve(0, 20, true, false, 0);
  test.addReserve(0, 40, false, false, 0);
  test.reserved[1].day = -1;
  test.disableReserve();
  EXPECT_EQ(res, test);
}

TEST(TestClassTicketOfficeHelpFunctions, res) {
  TicketOffice testArr;
  int res, test;
  testArr.colibrateDate();
  testArr.startOffice();
  res = 20;  // +10 in startOffice() and +10 next
  testArr.reserved = testArr.resizeReserved(testArr.reserved);
  test = testArr.sizeOfreservered;
  EXPECT_EQ(res, test);
}

