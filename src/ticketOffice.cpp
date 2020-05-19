
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
  int *ticketsNotPaid;
  TableForDay tbl;

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
      TakeOrder(tableToday, choice, dayToday - 1, true);
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
      TakeOrder(tableMonth.table[dayToday + choice - 1], choice,
        dayToday + choice, true);
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
      j = choice;
      TakeOrder(tableMonth.table[dayToday + choice - 1], j,
        dayToday + choice - 1, false);
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
      ticketsNotPaid = new int[longOfreservered];
      for (i = 0; i < longOfreservered; ++i) {
        if (reserved[i].day == dayToday + choice - 2 && !reserved[i].IsPaid) {
          cout << j << ". " << reserved[i].ID << endl;
          ticketsNotPaid[j - 1] = i;
          j++;
        }
      }
      cin >> choice;
      tbl = tableMonth.table[dayToday + k - 1];
      j = reserved[ticketsNotPaid[choice - 1]].numOfFilm;
      cout << "Название фильма: " << tbl.films[j - 1].name << endl;
      cout << "Начало сеанса: " << tbl.films[j - 1].timeStart / 60
        << ":";
      if (tableToday.films[j - 1].timeStart % 60 < 10)
        cout << "0" << tbl.films[j - 1].timeStart % 60 << endl;
      else
        cout << tbl.films[j - 1].timeStart % 60 << endl;
      cout << "Ваш номекр билета: " << reserved[ticketsNotPaid[choice - 1]].ID
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
      cout << "Выбирите номер вашего заказа для оплаты:" << endl;
      j = 1;
      ticketsNotPaid = new int[longOfreservered];
      for (i = 0; i < longOfreservered; ++i) {
        if (reserved[i].day == dayToday + choice - 1 && reserved[i].IsPaid) {
          cout << j << ". " << reserved[i].ID << endl;
          ticketsNotPaid[j - 1] = i;
          j++;
        }
      }
      cin >> choice;
      if (reserved[ticketsNotPaid[choice - 1]].count > 0)
        disableBook(tableMonth.table[dayToday + choice - 2],
          dayToday + choice - 2, reserved[ticketsNotPaid[choice - 1]].count,
          reserved[ticketsNotPaid[choice - 1]].IsVip,
          tableMonth.table[dayToday + choice - 2]
          .films[reserved[ticketsNotPaid[choice - 1]].numOfFilm].numOfFilm);
      else {
        disableBook(tableMonth.table[dayToday + choice - 2],
          dayToday + choice - 2, reserved[ticketsNotPaid[choice - 1]].count * -1,
          reserved[ticketsNotPaid[choice - 1]].IsVip,
          tableMonth.table[dayToday + choice - 2]
          .films[reserved[ticketsNotPaid[choice - 1]].numOfFilm].numOfFilm);

        disableBook(tableMonth.table[dayToday + choice - 2],
          dayToday + choice - 2, reserved[ticketsNotPaid[choice - 1]].count,
          reserved[ticketsNotPaid[choice - 1] + 1].IsVip,
          tableMonth.table[dayToday + choice - 2]
          .films[reserved[ticketsNotPaid[choice - 1] + 1].numOfFilm].numOfFilm);
      }
      cout << "Бронь была снята" << endl;
      break;
    default:
      break;
    }
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
  // убираем резервы за прошлый день
  while (reserved[i].day == dayToday)
    reserved[i++].day = -1;
  shiftReserve(reserved, i);
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
  delete[] arr;
  for (int i = 0; i < sizeOfreservered; ++i) {
    tmp[i].day = arr[i].day;
    tmp[i].count = arr[i].count;
    tmp[i].numOfFilm = arr[i].numOfFilm;
    tmp[i].IsVip = arr[i].IsVip;
    tmp[i].IsPaid = arr[i].IsPaid;
    tmp[i].ID = arr[i].ID;
  }
  sizeOfreservered += 10;
  return tmp;
}
// не присваивает значение коректно
void TicketOffice::addReserve(int _day, int _count, bool _IsVip, bool _IsPaid,
  int _numOfFilm) {
  int i;
  i = ++longOfreservered;
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
// если shift > половины длинны массива, то жопа(
void TicketOffice::shiftReserve(ReserveredTickets* arr, int shift) {
  for (int i = 0; i < sizeOfreservered - shift; ++i) {
    arr[i].count = arr[i + shift].count;
    arr[i].day = arr[i + shift].day;
    arr[i].IsPaid = arr[i + shift].IsPaid;
    arr[i].IsVip = arr[i + shift].IsVip;
    arr[i].numOfFilm = arr[i + shift].numOfFilm;
    arr[i].ID = arr[i + shift].ID;
  }
}