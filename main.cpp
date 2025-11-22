// #include <QApplication>
// #include <QPushButton>
// #include "mainwindow.hpp"
#include "Dynamic_array.hpp"
#include "Linked_List.hpp"
// #include "All_test.hpp"
// #include "Matrix.hpp"
#include "Lazy_test.h"
#include <iostream>
//#include <math.h>
using namespace std;

//int eratos() {
//    int n;
//    cout << "n= ";
//    cin >> n;
//    int *a = new int[n + 1];
//    for (int i = 0; i < n + 1; i++) a[i] = i;
//    for (int p = 2; p < n + 1; p++) {
//        if (a[p] != 0) {
//            cout << a[p] << endl;
//            for (int j = p * p; j < n + 1; j += p) a[j] = 0;
//        }
//    }
//    cin.get();
//    cin.get();
//}
//
//int prostie() {
//    int n, div = 2;
//    cout << "N = ";
//    cin >> n;
//    cout << n << " = 1";
//    while (n > 1) {
//        while (n % div == 0) {
//            cout << " * " << div;
//            n = n / div;
//        }
//        div++;
//    }
//    cin.get();
//    cin.get();
//    return 0;
//}
//
//int prostorneprost() {
//    int n;
//    scanf("%d", &n);
//    for (int i = 2; i <= sqrt(n); i++) {
//        if (n % i == 0) {
//            printf("NET");
//            return 0;
//        }
//    }
//    printf("DA");
//    return 0;
//
//}

int main(int argc, char *argv[]) {
    // QApplication a(argc, argv);
    // MainWindow window;
    //     // window.show();
    // a.exec()
    return test(argc, argv);
}
