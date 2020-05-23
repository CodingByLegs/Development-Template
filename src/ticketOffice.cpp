
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
  int ticketsNotPaid[100];
  TableForDay tbl;
  for (i = 0; i < 100; ++i)
    ticketsNotPaid[i] = -1;
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
    cout << "6. Оплатить зарезервированные билеты" << endl;
    cout << "7. Отменить заказ билетов" << endl;
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
      TakeOrder(tableMonth.table[dayToday - 1], choice, dayToday - 1, true);
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
          cout << "Всех мест хватает" << endl;
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
      cout << "0. Выход" << endl;
      cin >> choice;
      if (choice == 0)
        break;
      choice--;  // необходимо для коректного выбора дальше
      cout << "Список фильмов" << endl;
      k = 0;
      // тк dayToday на 1 больше фактической ячейки массива, а мы смотрим на 1
      // день дальше, чем сегодня, поэтому из dayToday не нужно вычитать 1 
      for (i = 0; i < tableMonth.table[dayToday + choice].countOfFilms; ++i) {
          cout << i + 1 << ". " << tableMonth.table[dayToday + choice]
            .films[i].name << "(";
          cout << tableMonth.table[dayToday + choice].films[i]
            .timeStart / 60 << ":";
          if (tableMonth.table[dayToday + choice].films[i].timeStart % 60 < 10)
            cout << "0" << tableMonth.table[dayToday + choice]
            .films[i].timeStart % 60;
          else
            cout << tableMonth.table[dayToday + choice].films[i]
            .timeStart % 60;
          cout << ")" << endl;
      }
      cout << "0. Выход" << endl;
      cin >> choice;
      if (choice == 0)
        break;
      TakeOrder(tableMonth.table[dayToday + choice - 2], choice,
        dayToday + choice - 2, true);
      break;
    case 5:
      cout << "Выбирите день для бронирования" << endl;
      for (i = 0; i < 4; ++i) {
        day = time1->tm_mday + i;
        mount = time1->tm_mon + 1;
        if (day > 30 + (time1->tm_mon + 1) % 2) {
          day = 1;
          mount++;
        }
        cout << i + 1 << ". ";
        cout << day << ".";
        if (mount < 10)
          cout << "0" << mount << endl;
        else
          cout << mount << endl;
      }
      cout << "0. Выход" << endl;
      cin >> choice;
      if (choice == 0)
        break;
      cout << "Список фильмов" << endl;
      choice--;
      for (i = 0; i < tableMonth.table[dayToday + choice - 1].countOfFilms; ++i) {
        cout << i + 1 << ". " << tableMonth.table[dayToday + choice - 1]
          .films[i].name << "(";
        cout << tableMonth.table[dayToday + choice - 1].films[i]
          .timeStart / 60 << ":";
        if (tableMonth.table[dayToday + choice - 1].films[i].timeStart % 60 < 10)
          cout << "0" << tableMonth.table[dayToday + choice - 1]
          .films[i].timeStart % 60;
        else
          cout << tableMonth.table[dayToday + choice - 1].films[i]
          .timeStart % 60;
        cout << ")" << endl;
      }
      cin >> choice;
      TakeOrder(tableMonth.table[dayToday + choice - 2], choice,
        dayToday + choice - 2, false);
      break;
    case 6:
      cout << "Выбирите день на который бронировали билеты" << endl;
      for (i = 0; i < 4; ++i) {
        day = time1->tm_mday + i;
        mount = time1->tm_mon + 1;
        if (day > 30 + (time1->tm_mon + 1) % 2) {
          day = 1;
          mount++;
        }
        cout << i + 1 << ". ";
        cout << day << ".";
        if (mount < 10)
          cout << "0" << mount << endl;
        else
          cout << mount << endl;
      }
      cout << "0. Выход" << endl;
      cin >> choice;
      k = choice - 1;
      if (choice == 0)
        break;
      cout << "Выбирите номер вашего заказа для оплаты:" << endl;
      j = 1;
      for (i = 0; i < longOfreservered; ++i) {;
        if (reserved[i].day == dayToday + choice - 2 && !reserved[i].IsPaid) {
          cout << j << ". " << reserved[i].ID << endl;
          ticketsNotPaid[j] = i;
          j++;
        }
      }
      cin >> choice;
      choice++;  // to fix bag
      tbl = tableMonth.table[dayToday + k - 1];
      j = reserved[ticketsNotPaid[choice - 1]].numOfFilm + 1;
      cout << "Название фильма: " << tbl.films[j - 1].name << endl;
      cout << "Начало сеанса: " << tbl.films[j - 1].timeStart / 60
        << ":";
      if (tableToday.films[j - 1].timeStart % 60 < 10)
        cout << "0" << tbl.films[j - 1].timeStart % 60 << endl;
      else
        cout << tbl.films[j - 1].timeStart % 60 << endl;
      cout << "Ваш номер билета: " << reserved[ticketsNotPaid[choice - 1]].ID
        << endl;
      if (reserved[ticketsNotPaid[choice - 1]].count > 0) {
        if (reserved[ticketsNotPaid[choice - 1]].IsVip)
          cout << "Категория билета: VIP" << endl;
        else
          cout << "Категория билета: обычный" << endl;
        cout << "Номер зала : " << tbl.films[j - 1].numOfHall << endl;
        cout << "Кол-во: " << reserved[ticketsNotPaid[choice - 1]].count << endl;
        cost = countCost(1,reserved[ticketsNotPaid[choice - 1]].IsVip,
          tbl.films[j - 1].numOfFilm, dayToday + k - 1);
        cout << "Цена за билет: " << cost << endl;
        cost = countCost(reserved[ticketsNotPaid[choice - 1]].count,
          reserved[ticketsNotPaid[choice - 1]].IsVip,
          tbl.films[j - 1].numOfFilm, dayToday + k - 1);
      } else {
        cout << "Категория билета: обычный" << endl;
        cout << "Номер зала : " << tbl.films[j - 1].numOfHall << endl;
        cout << "Кол-во: " << reserved[ticketsNotPaid[choice - 1]].count * -1
          << endl;
        cost = countCost(1, false, tbl.films[j - 1].numOfFilm,
          dayToday + k - 1);
        cout << "Цена за билет: " << cost << endl;
        cout << "Категория билета: VIP" << endl;
        cout << "Кол-во: " << reserved[ticketsNotPaid[choice - 1] + 1].count
          << endl;
        cost = countCost(1, true, tbl.films[j - 1].numOfFilm,
          dayToday + k - 1);
        cout << "Цена за билет: " << cost << endl;
        cost = countCost(reserved[ticketsNotPaid[choice - 1] + 1].count,
          true, tbl.films[j - 1].numOfFilm, dayToday + k - 1);
        cost += countCost(reserved[ticketsNotPaid[choice - 1]].count * -1,
          false, tbl.films[j - 1].numOfFilm, dayToday + k - 1);
      }
      cout << "Итоговая цена: " << cost << endl;
      // отмечаем как оплаченные
      reserved[ticketsNotPaid[choice - 1]].IsPaid = true;
      cout << endl;
      break;
    case 7:
      cout << "Выбирите день на который бронировали билеты" << endl;
      for (i = 0; i < 4; ++i) {
        day = time1->tm_mday + i;
        mount = time1->tm_mon + 1;
        if (day > 30 + (time1->tm_mon + 1) % 2) {
          day = 1;
          mount++;
        }
        cout << i + 1 << ". ";
        cout << day << ".";
        if (mount < 10)
          cout << "0" << mount << endl;
        else
          cout << mount << endl;
      }
      cout << "0. Выход" << endl;
      cin >> choice;
      k = choice - 1;
      if (choice == 0)
        break;
      j = 1;
      for (i = 0; i < longOfreservered; ++i) {
        if (reserved[i].day == dayToday + choice - 2 && !reserved[i].IsPaid) {
          if (j == 1)
            cout << "Выбирите номер вашего заказа для оплаты:" << endl;
          cout << j << ". " << reserved[i].ID << endl;
          ticketsNotPaid[j] = i;
          j++;
        }
      }
      if (j == 1) {
        cout << "На этот день нет забронированных билетов" << endl;
        break;
      }

      cin >> choice;
      reserved[ticketsNotPaid[choice]].day = -1;
      if (reserved[ticketsNotPaid[choice]].count > 0)
        disableBook(tableMonth.table[dayToday + choice - 2],
          dayToday + choice - 2, reserved[ticketsNotPaid[choice]].count,
          reserved[ticketsNotPaid[choice]].IsVip,
          tableMonth.table[dayToday + choice - 2]
          .films[reserved[ticketsNotPaid[choice]].numOfFilm].numOfFilm);
      else {
        disableBook(tableMonth.table[dayToday + choice - 2],
          dayToday + choice - 2, reserved[ticketsNotPaid[choice]].count * -1,
          reserved[ticketsNotPaid[choice]].IsVip,
          tableMonth.table[dayToday + choice - 2]
          .films[reserved[ticketsNotPaid[choice]].numOfFilm].numOfFilm);

        disableBook(tableMonth.table[dayToday + choice - 2],
          dayToday + choice - 2, reserved[ticketsNotPaid[choice]].count,
          reserved[ticketsNotPaid[choice] + 1].IsVip,
          tableMonth.table[dayToday + choice - 2]
          .films[reserved[ticketsNotPaid[choice] + 1].numOfFilm].numOfFilm);
      }
      disableReserve();
      cout << "Бронь была снята" << endl;
      break;
    default:
      break;
    }
    cout << endl;
  }
}

int TicketOffice::TakeOrder(TableForDay &tbl, int j, int day, bool willPay) {
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
    err = reserve_place(tbl, count, VIP, tbl.films[j - 1].numOfFilm, false);
    if (err != 0) {
      if (count - err != 0) {
        cout << "К сожалению на этот сенас не хватило " << err << " мест"
          << endl;
        if (willPay)
          cout << "1. Оплатить " << count - err << " мест" << endl;
        else
          cout << "1. Зарезервировать" << endl;
        cout << "2. Отменить и вернуться в меню" << endl;
        count -= err;
      } else {
        cout << "К сожелению, места на сеанс закончились" << endl;
        return -1;
      }
      cin >> choice;
      if (choice == 2) {
        disableBook(tbl, day, count - err, VIP, tbl.films[j - 1].numOfFilm);
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
    err = reserve_place(tbl, count, false, tbl.films[j - 1].numOfFilm, false);
    cin >> count1;
    err1 = reserve_place(tbl, count1, true, tbl.films[j - 1].numOfFilm, false);
    if (err != 0) {
      if (count - err != 0) {
        cout << "К сожалению на этот сенас не хватило " << err << " обычных"
          << " мест" << endl;
        if (willPay)
          cout << "1. Оплатить " << count - err << " мест" << endl;
        else
          cout << "1. Зарезервировать" << endl;
        cout << "2. Отменить и вернуться в меню" << endl;
        count -= err;
      } else {
        cout << "К сожелению, места на сеанс закончились" << endl;
        return -1;
      }
      cin >> choice;
      if (choice == 2) {
        disableBook(tbl, day, count - err, false, tbl.films[j - 1].numOfFilm);
        return -1;
      } else
        paid1 = true;
    }
    if (err1 != 0) {
      if (count1 - err1 != 0) {
        cout << "К сожалению на этот сенас не хватило " << err1 << " VIP"
          << " мест" << endl;
        if (willPay)
          cout << "1. Оплатить " << count - err << " мест" << endl;
        else
          cout << "1. Зарезервировать" << endl;
        cout << "2. Отменить и вернуться в меню" << endl;
        count1 -= err1;
      } else {
        cout << "К сожелению, места на сеанс закончились" << endl;
        return -1;
      }
      cin >> choice;
      if (choice == 2) {
        disableBook(tbl, day, count1 - err1, true, tbl.films[j - 1].numOfFilm);
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
        cout <<tbl.films[j -1].timeStart % 60 << endl;
      cout << "Ваш номекр билета: " << numOfTicket << endl;
      cout << "Категория билета: обычный" << endl;
      cout << "Номер зала : " <<tbl.films[j - 1].numOfHall << endl;
      cout << "Кол-во: " << count << endl;
      cost = countCost(1, false,tbl.films[j - 1].numOfFilm, 0);
      cout << "Цена за билет: " << cost << endl;
      cout << "Категория билета: VIP" << endl;
      cout << "Кол-во: " << count1 << endl;
      cost = countCost(1, true,tbl.films[j - 1].numOfFilm, 0);
      cout << "Цена за билет: " << cost << endl;
      cost = countCost(count, true,tbl.films[j - 1].numOfFilm, 0);
      cost += countCost(count1, false,tbl.films[j - 1].numOfFilm, 0);
      cout << "Итоговая цена: " << cost << endl;
      // резервируем эти места
      if (willPay) {
        addReserve(day, -1*count, false, true, tbl.films[j - 1].numOfFilm);
        addReserve(day, count1, true, true, tbl.films[j - 1].numOfFilm);
      } else {
        // система для хранения комбинированного заказа у первой части кол-во
        // со знаком минус
        addReserve(day, -1 * count, false, false, tbl.films[j - 1].numOfFilm);
        addReserve(day, count1, true, true, tbl.films[j - 1].numOfFilm);
      }
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
    cout << "Ваш номекр билета: " << numOfTicket << endl;
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
    if (willPay)
      addReserve(day, count, VIP, true, tbl.films[j - 1].numOfFilm);
    else
      addReserve(day, count, VIP, false, tbl.films[j - 1].numOfFilm);
    return 0;
  }
}

int TicketOffice::countCost(int _numOfPlaces, bool VIP, int _numOfFilm, int day) {
  int i;
  double koef, cost;
  startTimer();
  day--;
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
  return (int)(cost * _numOfPlaces);
}

void TicketOffice::startOffice() {
  int i, j, k;
  tableToday.countOfFilms = tableMonth.table[dayToday - 1].countOfFilms;
  for (i = 0; i < tableToday.countOfFilms; ++i)
    tableToday.films[i] = tableMonth.table[dayToday - 1].films[i];
  for (i = 0; i < 5; ++i) {
    for (j = 0; j < 15; ++j) {
      for (k = 0; k < 10; ++k) {
        if (!tableMonth.table[dayToday - 1].halls[i].hall[j][k].isFree)
          tableToday.halls[i].hall[j][k].isFree = false;
      }
    }
  }
  sizeOfreservered = 0;
  longOfreservered = 0;
  reserved = resizeReserved(reserved);
}

void TicketOffice::colibrateDate() {
  startTimer();
  dayToday = 1;
  dayNow = time1->tm_mday;
}

void TicketOffice::checkDate() {
  // if month changed time1->tm_mday = 1
  int i, j, k;
  i = 0;
  // убираем резервы за прошлый день ---------- Работает не совсм коректно
  while (reserved[i].day == dayToday)
    reserved[i++].day = -1;
  disableReserve();
  if (dayNow != time1->tm_mday) {
    dayToday++;
    dayNow = time1->tm_mday;
    if (dayToday > 30)
      dayToday = 1;
    tableToday.countOfFilms = tableMonth.table[dayToday - 1].countOfFilms;
    for (i = 0; i < tableToday.countOfFilms; ++i)
      tableToday.films[i] = tableMonth.table[dayToday - 1].films[i];
    for (i = 0; i < 5; ++i)
      for (j = 0; j < 15; ++j)
        for (k = 0; k < 10; ++k)
          if (!tableMonth.table[dayToday - 1].halls[i].hall[j][k].isFree)
            tableToday.halls[i].hall[j][k].isFree = false;
    move_array();  // подвинуть массив

  }
}

void TicketOffice::disableBook(TableForDay &tbl, int day, int _numOfPlaces,
  bool VIP, int _numOfFilm) {
  int i, j, count = 0;
  if (day > 30 - tableMonth.daysAvable) {
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

int TicketOffice::reserve_place(TableForDay &tbl ,int _numOfPlaces, bool VIP,
  int _numOfFilm, bool check) {
  int i, j, count = 0;
  if (VIP) {
    for (i = 0; i < 5; ++i) {
      for (j = 0; j < 10; ++j) {
        if (tbl.halls[tbl.films[_numOfFilm].numOfHall].hall[i][j].isFree) {
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

ReserveredTickets* TicketOffice::resizeReserved(ReserveredTickets *arr) {
  ReserveredTickets *tmp = new ReserveredTickets[sizeOfreservered + 10];
  for (int i = 0; i < sizeOfreservered; ++i) {
    tmp[i].day = arr[i].day;
    tmp[i].count = arr[i].count;
    tmp[i].numOfFilm = arr[i].numOfFilm;
    tmp[i].IsVip = arr[i].IsVip;
    tmp[i].IsPaid = arr[i].IsPaid;
    tmp[i].ID = arr[i].ID;
  }
  sizeOfreservered += 10;
  delete[] arr;
  return tmp;
}

void TicketOffice::addReserve(int _day, int _count, bool _IsVip, bool _IsPaid,
  int _numOfFilm) {
  int i;
  i = longOfreservered++;
  if (sizeOfreservered == i)
    reserved = resizeReserved(reserved);
  reserved[i].day = _day;
  reserved[i].count = _count;
  reserved[i].IsPaid = _IsPaid;
  reserved[i].IsVip = _IsVip;
  reserved[i].numOfFilm = _numOfFilm;
  reserved[i].ID = numOfTicket;
  numOfTicket++; 
}

void TicketOffice::disableReserve() {
  int i, j = 0;
  for (i = 0; i < sizeOfreservered; ++i)
    if (reserved[i].day != -1) {
      reserved[j].day = reserved[i].day;
      reserved[j].count = reserved[i].count;
      reserved[j].ID = reserved[i].ID;
      reserved[j].IsPaid = reserved[i].IsPaid;
      reserved[j].IsVip = reserved[i].IsVip;
      reserved[j].numOfFilm = reserved[i].numOfFilm;
      j++;
    }
}


bool operator==(Film const &c1, Film const &c2) {
  if (c1.duration != c2.duration || c1.name != c2.name
    || c1.numOfFilm != c2.numOfFilm || c1.numOfHall != c2.numOfHall
    || c1.timeStart != c2.timeStart)
    return false;
  return true;
}

bool operator==(Hall const &c1, Hall const &c2) {
  int i, j;
  for (i = 0; i < 15; ++i) {
    for (j = 0; j < 10; ++j) {
      if (c1.hall[i][j].isFree != c2.hall[i][j].isFree
        || c1.hall[i][j].isVIP != c2.hall[i][j].isVIP) {
        return false;
      }

    }
  }
  return true;
}

bool operator==(TableForDay const &c1, TableForDay const &c2) {
  int i;
  if (c1.countOfFilms != c2.countOfFilms)
    return false;
  for (i = 0; i < c1.countOfFilms; ++i)
    if (!(c1.films[i] == c2.films[i]))
      return false;
  for (i = 0; i < 5; ++i)
    if (!(c1.halls[i] == c2.halls[i]))
      return false;
  return true;
}

bool operator==(TableFor30Days const &c1, TableFor30Days const &c2) {
  int i, j, k, m, l;
  for (i = 0; i < 30; ++i) {
    if (!(c1.table[i].countOfFilms == c2.table[i].countOfFilms))
      return false;
    for (j = 0; j < c1.table[i].countOfFilms; ++j)
      if (!(c1.table[i].films[j] == c2.table[i].films[j]))
        return false;
    for (l = 0; l < 5; ++l)
      if (!(c1.table[i].halls[l] == c2.table[i].halls[l]))
        return false;

  }
  return true;
}

bool operator==(TicketOffice const &c1, TicketOffice const &c2) {
  int lg, i;
  if (c1.longOfreservered < c2.longOfreservered)
    lg = c1.longOfreservered;
  else
    lg = c2.longOfreservered;
  for (i = 0; i < lg; ++i)
    if (c1.reserved[i].count != c2.reserved[i].count
      || c1.reserved[i].day != c2.reserved[i].day
      || c1.reserved[i].ID != c2.reserved[i].ID
      || c1.reserved[i].IsPaid != c2.reserved[i].IsPaid
      || c1.reserved[i].IsVip != c2.reserved[i].IsVip
      || c1.reserved[i].numOfFilm != c2.reserved[i].numOfFilm)
      return false;
  if (lg == c1.longOfreservered) {
    for (i; i < c2.longOfreservered; ++i)
      if (c2.reserved[i].day != -1)
        return false;
  } else {
    for (i; i < c1.longOfreservered; ++i)
      if (c1.reserved[i].day != -1)
        return false;
  }
  return true;
}