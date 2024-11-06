#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

double fungPoli(double a, double b, double c, double d, double x) {
    return a * x * x * x + b * x * x + c * x + d;
}

double penAcak(double a, double b, double c, double d, double awal, double akhir, int iterasi) {
     srand(time(0));
     double maksY = fungPoli(a, b, c, d, awal);
     double maksX = awal;
     
     for (int i = 1; i <= iterasi; i++) {
            double x = awal + ((double)rand() / RAND_MAX) * (akhir - awal);
            double hasil = fungPoli(a, b, c, d, x);
            
            if (hasil > maksY) {
                maksY = hasil;
                maksX = x;
            }
        }
        return maksX;
}
int main() {
    double a, b, c, d;
    cout << "Masukkan koefisien a, b, c, dan d: " << endl;
    cin >> a >> b >> c >> d;
    
    double awal, akhir;
    cout << "Masukkan nilai awal dan akhir dari x: " << endl;
    cin >> awal >> akhir;
    
    int iterasi;
    cout << "Masukkan jumlah iterasi: ";
    cin >> iterasi;
    
    double maksX = penAcak(a, b, c, d, awal, akhir, iterasi);
    double maksY = fungPoli(a, b, c, d, maksX);
    
    cout << "Nilai x untuk fungsi maksimum/minimum = " << maksX << endl;
    cout << "Nilai fungsi kuadrat pada x = " << maksX << " adalah " << maksY << endl;
    
    system("PAUSE");
    return 0;
}
