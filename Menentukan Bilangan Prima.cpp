#include <iostream>
#include <vector>
#include <cstdlib>
#
bool cekPrima (int bil) {
 if (bil <= 1) {
 return false;
 }
 for (int i = 2; i * i <= bil; ++i) {
 if (bil % i == 0) {
 return false;
 }
 }
 return true;
}
#
std::vector<int> hitFaktor(int bil) {
 std::vector<int> faktor;
 for (int i = 1; i<= bil; ++i) {
 if (bil % i == 0) {
 faktor.push_back(i);
}
 }
 return faktor;
}
#
int main() {
 int bil;
 std::cout << "Masukkan sebuah bilangan: ";
 std::cin >> bil;
 if (cekPrima (bil)) {
 std::cout << bil << " adalah bilangan prima." << std::endl;
 } else {
 std::cout << bil << " bukan bilangan prima." << std::endl;
 std::cout << "Faktor dari " << bil << ": ";
 std::vector<int> faktor = hitFaktor (bil) ;
 for (int i = 0; i < faktor.size () ; ++i) {
 std::cout << faktor[i] << " ";
 }
 std::cout << std::endl;
 }
 system("PAUSE") ;
 return 0;
}
