#include <iostream>
#include <cmath>
#include <cstdlib>

bool fAmstrong(int bilangan) {
  int bilAsal = bilangan;
  int jlhdigit = 0;
  int jumlah = 0;

  while (bilAsal != 0) {
    bilAsal /= 10;
    ++jlhdigit;
  }

  bilAsal = bilangan;

  while (bilAsal != 0) {
    int digit = bilAsal % 10;
    int pgktDigit = pow(digit, jlhdigit);
    jumlah += pgktDigit;
    std::cout << digit << "^" << jlhdigit << " = " << pgktDigit << std::endl;
    bilAsal /= 10;
  }

  if (jumlah == bilangan) {
    return true;
  } else {
    return false;
  }
}

int main() {
  int bilangan;
  std::cout << "Masukkan sebuah bilangan: ";
  std::cin >> bilangan;

  if (fAmstrong(bilangan)) {
    std::cout << bilangan << " adalah bilangan Armstrong" << std::endl;
  } else {
    std::cout << bilangan << "bukan bilangan Armstrong" << std::endl;
  }

  system("PAUSE");

  return 0;
}
