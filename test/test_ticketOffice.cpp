#include <gtest/gtest.h>
#include "octal.h"

TEST(TestClassHex, Assignment) {
  Octal res("F7A", 3);
  Octal a("F7A", 3);
  Octal b;
  b = a;
  EXPECT_EQ(b, res);
}

TEST(TestClassHex, AddTwoNumbers) {
  Octal res("0", 4);
  Octal resExpct("14E9", 4);
  Octal a("F7A", 3);
  Octal b("56F", 3);
  res = a + b;
  EXPECT_EQ(res, resExpct);
}

TEST(TestClassHex, SubTwoNumbers) {
  Octal res("0", 3);
  Octal resExpct("D21", 3);
  Octal a("E2A", 3);
  Octal b("109", 3);
  res = a - b;
  EXPECT_EQ(res, resExpct);
}

TEST(TestClassHex, AreTwoNumbersEqual) {
  bool x = false;
  Octal a("109", 3);
  Octal b("109", 3);
  if (a == b)
    x = true;
  EXPECT_EQ(x, true);
}

TEST(TestClassHex, CompareWhatIsBigger) {
  bool x = false;
  Octal a("1A9", 3);
  Octal b("109", 3);
  if (a > b)
    x = true;
  EXPECT_EQ(x, true);
}

TEST(TestClassHex, CompareWhatIsLowwer) {
  bool x = false;
  Octal a("109", 3);
  Octal b("10A", 3);
  if (a < b)
    x = true;
  EXPECT_EQ(x, true);
}

TEST(TestClassHex, GetOneNumber) {
  char res;
  char resExpct = '9';
  Octal a("109", 3);
  res = a[0];
  EXPECT_EQ(res, resExpct);
}

TEST(TestClassHex, TryGoOutOfRange) {
  char res = '9';
  char resExpct = '9';
  Octal a("109", 3);
  res = a[5];
  EXPECT_EQ(res, resExpct);
}

TEST(TestClassHex, ReadAndWriteTxt) {
  Octal res ("0", 5);
  Octal resExpct("82AF1", 5);
  ofstream fout("output.txt");
  fout << resExpct;
  fout.close();
  ifstream fin("output.txt");
  fin >> res;
  fin.close();
  EXPECT_EQ(res, resExpct);
}


TEST(TestClassHex, CanAddTwoNegativeNumbers) {
  EXPECT_EQ(add(-5, -5), -10);
  system("pause");
}
