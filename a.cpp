#include <iostream>

using namespace std;

void print(int n) {
    // cout << n << endl;
    for (int i=sizeof(char)*8-1; i>=0; i--)
        cout << (n>>(1*i) & 1);
    cout << endl;
}

void print(char n) {
    print((int) n);
}

char uni(int n, int m, int bitm) {
    int bitn = sizeof(char)*8 - bitm;
    if ((bitn + bitm > sizeof(char)*8) || (n > ((1<<bitn)-1) || m > ((1<<bitm)-1))) {
        cerr << "problemas com a uniao, abortando..." << endl;
        throw 1;
        // return  0; //vai ficar em 1 char no final
    }
    // print(n);
    // print(n << bitm);
    // print(m);
    return (n << bitm) | m;
}

void sep(char& z, int& n, int& m, int bitm) {
    /** recebe um char que eh a uniao de 2 numeros, o tamanho de bit do menor
     * e coloca o resultado nos parametros n e m recebidos
    */
    int aux = 0;
    int bit = bitm;
    while (bit--) {
        aux <<= 1;
        aux |= 1;
    }
    m = (z & (aux));
    print(z&~aux);
    n = (z & ~aux) >> bitm;

}

int main() {
    int a = 119, b = 7;
    char z = uni(a, b, 3);
    a = 0;
    b = 0;
    print(z);
    sep(z, a, b, 3);
    cout << "a: " << a << " b: " << b << endl;

    return 0;
}