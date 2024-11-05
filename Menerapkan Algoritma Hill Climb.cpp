#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

double fKuadrat (double x, double a,double b,double c) {
    return a * x * x + b * x + c;
}

pair <double,double> hClimbing (double a,double b, double c) {
    srand(static_cast<unsigned>(time(0)));
    double x = (double) rand() / RAND_MAX * 200 - 100;
    double deltax = 0.01;
    double nilai = fKuadrat (x, a, b, c) ;
    double nilai_kiri = fKuadrat (x - deltax, a, b, c);
    double nilai_kanan = fKuadrat (x + deltax, a, b, c);

    while (nilai_kiri > nilai || nilai_kanan > nilai) {
        if (nilai_kiri > nilai_kanan) {
            x -= deltax;
            nilai = nilai_kiri;
        } else {
            x += deltax;
            nilai = nilai_kanan;
        }
       nilai_kiri = fKuadrat(x - deltax, a, b, c);  
       nilai_kanan = fKuadrat(x + deltax, a, b, c);
    }
        return make_pair(x, nilai);
}
    
int main () {
    double a, b, c;
    cout << "Masukkan nilai a :";
    cin >> a;
    cout << "Masukkan nilai b :";
    cin >> b;
    cout << "Masukkan nilai c :";
    cin >> c;
    pair<double, double> result = hClimbing(a, b, c);
    double x_maks = result.first;
    double nilai_maks = result.second;
    cout << "Nilai x untuk hasil maksimum: " << x_maks << endl;
    cout << "Nilai maksimum f (x): " << nilai_maks << endl;
    system ("PAUSE");
    return 0;
}
