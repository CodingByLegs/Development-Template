
#include "ticketOffice.h"

// to set time
void TicketOffice::startTimer() {
  t = time(NULL);
  time1 = localtime(&t);
}

void TicketOffice::menu() {
  setlocale(LC_ALL, "Russian");
  bool flag1, VIP, paid, paid1;
  int choice, i, j, k, count, count1, err, err1, cost;
  flag1 = true;
  cout << "Добро пожаловат в меню!" << endl;
  while (flag1) {
    startTimer();
    cout << "Текущее время: " << time1->tm_hour <<
      ":";
    if (time1->tm_min < 10)
      cout << "0" << time1->tm_min;
    else
      cout << time1->tm_min;
    cout << endl;
    cout << "1. Купить билет на сегодня" << endl;
    cout << "2. Проверить наличие мест на сеанс" << endl;
    cout << "3. Узнать список сеансов на ближайшие три дня" << endl;
    cout << "4. Купить билет на ближайшие три дня" << endl;
    cout << "5. Зарезервировать место" << endl;
    cout << "5. Отменить заказ билетов" << endl;
    cin >> choice;
    switch (choice) {
    case 1:
      k = 0;
      cout << "Список фильмов на сегодня:" << endl;
      for (i = 0; i < tableToday.countOfFilms; ++i) {
        if (tableToday.films[i].timeStart + 10 < time1->tm_hour * 60 +
          time1->tm_min) {
          k++;
          continue;
        }
        cout << i + 1 << ". " << tableToday.films[i].name << "(";
        cout << tableToday.films[i].timeStart / 60 << ":";
        if (tableToday.films[i].timeStart % 60 < 10)
          cout << "0" << tableToday.films[i].timeStart % 60;
        else
          cout << tableToday.films[i].timeStart % 60;
        cout << ")" << endl;
      }
      if (k == tableToday.countOfFilms)
        cout << "В этот день пока нет фильмов" << endl;
      cout << "0. Выход" << endl;
      cin >> choice;
      if (choice == 0)
        break;
      TakeOrder(tableMonth.table[dayToday + choice], choice, i, 0);
      break;
    case 2:
      cout << "Выьерите сеанс:" << endl;
      for (i = 0; i < tableToday.countOfFilms; ++i) {
        cout << i + 1 << ". " << tableToday.films[i].name << "(";
        cout << tableToday.films[i].timeStart / 60 << ":";
        if (tableToday.films[i].timeStart % 60 < 10)
          cout << "0" << tableToday.films[i].timeStart % 60;
        else
          cout << tableToday.films[i].timeStart % 60;
        cout << ")" << endl;
      }
      cout << "0. Выход" << endl;
      cin >> choice;
      if (choice == 0)
        break;
      j = choice;
      cout << "Выберите зону" << endl;
      cout << "1. Обычный" << endl;
      cout << "2. VIP" << endl;
      cout << "3. Комбинированный" << endl;
      cin >> choice;
      if (choice == 1 || choice == 2) {
        cout << "Введите кол-во мест" << endl;
        cin >> count;
        if (choice == 1)
          VIP = false;
        else
          VIP = true;
        err = reserve_place(tableToday, count, VIP, tableToday.films[j - 1].numOfFilm, true);
        if (err != 0) {
          cout << "Не хватает " << err << " мест" << endl;
        }
        else {
          cout << "Есть места в наличии" << endl;
        }
      }
      else {
        cout << "Сначала введите кол-во обынчых билетов, затем кол-во VIP" <<
          " билетов" << endl;
        cin >> count;
        cin >> count1;
        err = reserve_place(tableToday, count, false, tableToday.films[j - 1].numOfFilm, true);
        err1 = reserve_place(tableToday, count1, true, tableToday.films[j - 1].numOfFilm, true);
        if (err != 0 && err1 != 0) {
          cout << "Не хватает " << err << " обычных мест" << endl;
          cout << "Не хватает " << err1 << " VIP мест" << endl;
        }
        else if (err != 0) {
          cout << "Не хватает " << err << " обычных мест" << endl;
          cout << "VIP места есть в наличии" << endl;
        }
        else if (err1 != 0) {
          cout << "Не хватает " << err1 << " VIP мест" << endl;
          cout << "Обычные места есть в наличии" << endl;
        }
        else {
          cout << "Всеч мест хватает" << endl;
        }
      }
      break;
    case 3:
      TableForDay *res;
      res = get_info_for_3days(dayToday);
      int m, day, mount;
      for (m = 0; m < 3; ++m) {
        day = time1->tm_mday + m + 1;
        mount = time1->tm_mon + 1;
        if (day > 30 + (time1->tm_mon + 1) % 2) {
          day = 1;
          mount++;
        }
        cout << day << ".";
        if (mount < 10)
          cout << "0" << mount << endl;
        else
          cout << mount << endl;
        if (res[m].countOfFilms == 0)
          cout << "В этот день пока нет фильмов" << endl;
        else
          cout << "Список фильмов: " << endl;
        for (i = 0; i < res[m].countOfFilms; ++i) {
          cout << i + 1 << ". " << res[m].films[i].name << "(";
          cout << res[m].films[i].timeStart / 60 << ":";
          if (res[m].films[i].timeStart % 60 < 10)
            cout << "0" << res[m].films[i].timeStart % 60;
          else
            cout << res[m].films[i].timeStart % 60;
          cout << ")" << endl;
        }
      }
      cout << endl;
      break;
    case 4:
      // CHTO ETO TAKOE?????
      // POCHEMY IA V ODNOM CICLE ISPOL'ZYU
      // m, A D DRYGOM i ????????
      // KTO IA?
      cout << "Выбирите дату:" << endl;
      for (m = 0; m < 3; ++m) {
        day = time1->tm_mday + m + 1;
        mount = time1->tm_mon + 1;
        if (day > 30 + (time1->tm_mon + 1) % 2) {
          day = 1;
          mount++;
        }
        cout << m + 1 << ". ";
        cout << day << ".";
        if (mount < 10)
          cout << "0" << mount << endl;
        else
          cout << mount << endl;
      }
      cout << "0. Выход";
      cin >> choice;
      if (choice == 0)
        break;
      cout << "Список фильмов" << endl;
      k = 0;
      for (i = 0; i < tableMonth.table[dayToday + choice].countOfFilms; ++i) {
          cout << i + 1 << ". " << tableMonth.table[dayToday + choice]
            .films->name << "(";
          cout << tableMonth.table[dayToday + choice].films[i]
            .timeStart / 60 << ":";
          if (tableMonth.table[dayToday + choice].films[i].timeStart % 60 < 10)
            cout << "0" << tableMonth.table[dayToday + choice]
            .films[i].timeStart % 60;
          else
            cout << tableMonth.table[dayToday + choice].films[i]
            .timeStart % 60;
          cout << ")" << endl;
        cout << "0. Выход" << endl;
      }
      cin >> choice;
      if (choice == 0)
        break;
      TakeOrder(tableMonth.table[dayToday + choice], choice, i, choice);
      break;
    default:
      break;
    }
  }
}

int TicketOffice::TakeOrder(TableForDay tbl, int j, int i, int day) {
  int choice, err, err1, count, count1, cost;
  bool VIP, paid, paid1;
  cout << "Выберите зону" << endl;
  cout << "1. Обычный" << endl;
  cout << "2. VIP" << endl;
  cout << "3. Комбинированный" << endl;
  cin >> choice;
  paid = false;
  if (choice == 1 || choice == 2) {
    cout << "Введите кол-во билетов" << endl;
    cin >> count;
    if (choice == 1)
      VIP = false;
    else
      VIP = true;
    err = reserve_place(tableToday, count, VIP, tbl.films[j - 1].numOfFilm, false);
    if (err != 0) {
      cout << "К сожалению на этот сенас не хватило " << err << " мест"
        << endl;
      cout << "1. Оплатить " << count - err << " мест" << endl;
      cout << "2. Отменить и вернуться в меню" << endl;
      cin >> choice;
      if (choice == 2) {
        disableBook(tbl, day, count, VIP, tbl.films[j - 1].numOfFilm);
        return -1;
      }
      else
        paid = true;
    }
    else
      paid = true;
  }
  else {
    cout << "Сначала введите кол-во обынчых билетов, затем кол-во VIP" <<
      " билетов" << endl;
    cin >> count;
    err = reserve_place(tableToday, count, false, tbl.films[j - 1].numOfFilm, false);
    cin >> count1;
    err1 = reserve_place(tableToday, count1, true, tbl.films[j - 1].numOfFilm, false);
    if (err != 0) {
      cout << "К сожалению на этот сенас не хватило " << err << " обычных"
        << " мест" << endl;
      cout << "1. Оплатить " << count - err << " мест" << endl;
      cout << "2. Отменить и вернуться в меню" << endl;
      cin >> choice;
      if (choice == 2) {
        disableBook(tbl, day, count, false, tbl.films[j - 1].numOfFilm);
        return -1;
      }
      else
        paid1 = true;
    }
    if (err1 != 0) {
      cout << "К сожалению на этот сенас не хватило " << err1 << " VIP"
        << " мест" << endl;
      cout << "1. Оплатить " << count1 - err1 << " мест" << endl;
      cout << "2. Отменить и вернуться в меню" << endl;
      cin >> choice;
      if (choice == 2) {
        disableBook(tbl, day, count1, true, tbl.films[j - 1].numOfFilm);
        return -1;
      }
      else
        paid1 = true;
    }
    if (err == 0 && err1 == 0)
      paid1 = true;
    if (paid1) {
      cout << "Название фильма: " <<tbl.films[j - 1].name << endl;
      cout << "Начало сеанса: " <<tbl.films[j - 1].timeStart / 60
        << ":";
      if (tableToday.films[j - 1].timeStart % 60 < 10)
        cout << "0" <<tbl.films[j - 1].timeStart % 60 << endl;
      else
        cout <<tbl.films[i].timeStart % 60 << endl;
      cout << "Категория билета: обычный" << endl;
      cout << "Номер зала : " <<tbl.films[j - 1].numOfHall << endl;
      cout << "Кол-во: " << count << endl;
      cost = countCost(1, false,tbl.films[j - 1].numOfFilm, 0);
      cout << "Цена за биоет: " << cost << endl;
      cout << "Категория билета: VIP" << endl;
      cout << "Кол-во: " << count1 << endl;
      cost = countCost(1, true,tbl.films[j - 1].numOfFilm, 0);
      cout << "Цена за биоет: " << cost << endl;
      cost = countCost(count1, true,tbl.films[j - 1].numOfFilm, 0);
      cost += countCost(count1, false,tbl.films[j - 1].numOfFilm, 0);
      cout << "Итоговая цена: " << cost << endl;
      return 0;
    }
  }
  if (paid) {
    cout << "Название фильма: " <<tbl.films[j - 1].name << endl;
    cout << "Начало сеанса: " <<tbl.films[j - 1].timeStart / 60
      << ":";
    if (tableToday.films[j - 1].timeStart % 60 < 10)
      cout << "0" <<tbl.films[j - 1].timeStart % 60 << endl;
    else
      cout <<tbl.films[j - 1].timeStart % 60 << endl;
    cout << "Категория билета: ";
    if (VIP)
      cout << "VIP" << endl;
    else
      cout << "обычный" << endl;
    cout << "Номер зала : " <<tbl.films[j - 1].numOfHall << endl;
    cout << "Кол-во: " << count << endl;
    cost = countCost(1, VIP,tbl.films[j - 1].numOfFilm, 0);
    cout << "Цена билета: " << cost << endl;
    cost = countCost(count, VIP,tbl.films[j - 1].numOfFilm, 0);
    cout << "Итоговая цена: " << cost << endl;
    return 0;
  }
}

int TicketOffice::countCost(int _numOfPlaces, bool VIP, int _numOfFilm, int day) {
  int i, cost;
  double koef;
  startTimer();
  for (i = 0; i < tableMonth.table[dayToday + day].countOfFilms; ++i) {
    if (tableMonth.table[dayToday + day].films[i].numOfFilm == _numOfFilm) {
      if (tableMonth.table[dayToday + day].films[i].timeStart >= 420
        && tableMonth.table[dayToday + day].films[i].timeStart < 719)
        koef = 0.75;
      else if (tableMonth.table[dayToday + day].films[i].timeStart >= 1080
        && tableMonth.table[dayToday + day].films[i].timeStart < 1450
        || tableMonth.table[dayToday + day].films[i].timeStart >= 0
        && tableMonth.table[dayToday + day].films[i].timeStart <= 240)
        koef = 1.5;
      else
        koef = 1;
      if (tableToday.films[i].numOfHall > 3) {
        if (VIP)
          cost = hall_4_5_CostVIP * koef;
        else
          cost = hall_4_5_CostUssual * koef;
      }
      else {
        if (VIP)
          cost = hall_1_3_CostVIP * koef;
        else
          cost = hall_1_3_CostUssual * koef;
      }
      break;
    }
  }
  return cost * _numOfPlaces;
}

void TicketOffice::startOffice() {
  int i, j, k;
  tableToday.countOfFilms = tableMonth.table[dayToday - 1].countOfFilms;
  for (i = 0; i < tableToday.countOfFilms; ++i)
    tableToday.films[i] = tableMonth.table[dayToday - 1].films[i];
  for (i = 0; i < 5; ++i)
    for (j = 0; j < 15; ++j)
      for (k = 0; k < 10; ++k)
        if (!tableMonth.table[dayToday - 1].halls[i].hall[j][k].isFree)
          tableToday.halls[i].hall[j][k].isFree = false;
}

void TicketOffice::colibrateDate() {
  startTimer();
  dayToday = 1;
  dayNow = time1->tm_mday;
}

void TicketOffice::checkDate() {
  // if month changed time1->tm_mday = 1
  int i, j, k;
  if (dayNow != time1->tm_mday) {
    dayToday++;
    dayNow = time1->tm_mday;
    if (dayToday > 30) {
      dayToday = 1;
      //tableMonth = move_array();
      // подвинуть массив
    } else {
      tableToday.countOfFilms = tableMonth.table[dayToday - 1].countOfFilms;
      for (i = 0; i < tableToday.countOfFilms; ++i)
        tableToday.films[i] = tableMonth.table[dayToday - 1].films[i];
      for (i = 0; i < 5; ++i)
        for (j = 0; j < 15; ++j)
          for (k = 0; k < 10; ++k)
            if (!tableMonth.table[dayToday - 1].halls[i].hall[j][k].isFree)
              tableToday.halls[i].hall[j][k].isFree = false;
    }
  }
}

// работает некорктно
void TicketOffice::disableBook(TableForDay tbl, int day, int _numOfPlaces,
  bool VIP, int _numOfFilm) {
  int i, j, count = 0;
  if (day > tableMonth.daysAvable) {
    throw logic_error("Out of range");
    return;
  }
  if (VIP) {
    for (i = 0; i < 5; ++i) {
      for (j = 0; j < 10; ++j) {
        if (!tbl.halls[tbl.films[_numOfFilm].numOfHall].hall[i][j].isFree) {
          tbl.halls[tbl.films[_numOfFilm].numOfHall].hall[i][j].isFree = true;
          if (++count == _numOfPlaces)
            return;
        }
      }
    }
  } else {
    for (i = 5; i < 15; ++i) {
      for (j = 0; j < 10; ++j) {
        if (!tbl.halls[tbl.films[_numOfFilm].numOfHall].hall[i][j].isFree) {
          tbl.halls[tbl.films[_numOfFilm].numOfHall].hall[i][j].isFree = true;
          if (++count == _numOfPlaces)
            return;
        }
      }
    }
  }
}
// номально не резервирует =(
int TicketOffice::reserve_place(TableForDay tbl ,int _numOfPlaces, bool VIP,
  int _numOfFilm, bool check) {
  int i, j, count = 0;
  if (VIP) {
    for (i = 0; i < 5; ++i) {
      for (j = 0; j < 10; ++j) {
        if (tbl.halls[tbl.films[_numOfFilm].numOfHall]
          .hall[i][j].isFree) {
          if (!check)
            tbl.halls[tbl.films[_numOfFilm].numOfHall]
            .hall[i][j].isFree = false;
          if (++count == _numOfPlaces)
            return 0;
        }
      }
    }

  }
  else {
    for (i = 5; i < 15; ++i) {
      for (j = 0; j < 10; ++j) {
        if (tbl.halls[tbl.films[_numOfFilm].numOfHall]
          .hall[i][j].isFree) {
          if (!check)
            tbl.halls[tbl.films[_numOfFilm].numOfHall]
            .hall[i][j].isFree = false;
          if (++count == _numOfPlaces)
            return 0;
        }
      }
    }
  }
  return _numOfPlaces - count;
}
