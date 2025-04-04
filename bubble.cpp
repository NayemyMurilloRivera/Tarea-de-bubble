#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>  // Para medir tiempo
using namespace std;
using namespace std::chrono;

const int n_array = 10000;

class Poli {
public:
    virtual bool cambio(int* a, int* b) = 0;
};

class Burbuja {
public:
    void burbuja_directa(int* a, int* b);
    void polimorfismo(int* a, int* b, Poli* poliburbuja);
    void puntero_funcion(int* a, int* b, bool(*d)(int, int));
    void imprimir(int* a, int* b);
};

template<class T>
class descendiente {
public:
    bool operator()(T a, T b) {
        return a < b;
    }
};

template<class T>
class ascen {
public:
    bool operator()(T a, T b) {
        return a > b;
    }
};

template<class T>
class Burbuja_functor {
public:
    T functor;
    Burbuja_functor(T f) : functor(f) {}

    void burbujitancia(int* a, int* b) {
        bool paso = true;
        while (paso) {
            paso = false;
            for (int* i = a; i < b; i++) {
                if (functor(*i, *(i + 1))) {
                    swap(*i, *(i + 1));
                    paso = true;
                }
            }
        }
    }
};

bool cmp(int a, int b) {
    return a > b;
}

bool cmp2(int a, int b) {
    return a < b;
}

void Burbuja::puntero_funcion(int* a, int* b, bool(*d)(int, int)) {
    bool paso = true;
    while (paso) {
        paso = false;
        for (int* i = a; i < b; i++) {
            if (d(*i, *(i + 1))) {
                swap(*i, *(i + 1));
                paso = true;
            }
        }
    }
}

class Policambio2 : public Poli {
public:
    bool cambio(int* a, int* b) override {
        return *a > *b;
    }
};

class Policambio : public Poli {
public:
    bool cambio(int* a, int* b) override {
        return *a < *b;
    }
};

void Burbuja::burbuja_directa(int* a, int* b) {
    bool paso = true;
    while (paso) {
        paso = false;
        for (int* i = a; i < b; i++) {
            if (*i < *(i + 1)) {
                swap(*i, *(i + 1));
                paso = true;
            }
        }
    }
}

void Burbuja::polimorfismo(int* a, int* b, Poli* poliburbuja) {
    bool paso = true;
    while (paso) {
        paso = false;
        for (int* i = a; i < b; i++) {
            if (poliburbuja->cambio(i, i + 1)) {
                swap(*i, *(i + 1));
                paso = true;
            }
        }
    }
}

void Burbuja::imprimir(int* ini, int* fini) {
    for (int* im = ini; im <= fini; im++) {
        cout << *im << " ";
    }
    cout << endl;
}

void generador(int n_array, int* b) {
    for (int i = 0; i < n_array; i++) {
        b[i] = rand() % 1000000 + 1;
    }
}

int main() {
    srand(time(0));
    int* b = new int[n_array];
    int* a = b + n_array - 1;

    Burbuja burb;

    // BURBUJA DIRECTA
    generador(n_array, b);
    cout << "Ordenando con metodo burbuja_directa:" << endl;
    auto start1 = high_resolution_clock::now();
    burb.burbuja_directa(b, a);
    auto end1 = high_resolution_clock::now();
    burb.imprimir(b, a);
    cout << "Tiempo: " << duration_cast<milliseconds>(end1 - start1).count() << " ms\n\n";

    // POLIMORFISMO (mayor a menor)
    generador(n_array, b);
    Policambio2 my;
    cout << "Ordenando con metodo polimorfismo (mayor a menor):" << endl;
    auto start2 = high_resolution_clock::now();
    burb.polimorfismo(b, a, &my);
    auto end2 = high_resolution_clock::now();
    burb.imprimir(b, a);
    cout << "Tiempo: " << duration_cast<milliseconds>(end2 - start2).count() << " ms\n\n";

    // POLIMORFISMO (menor a mayor)
    generador(n_array, b);
    Policambio my2;
    cout << "Ordenando con metodo polimorfismo (menor a mayor):" << endl;
    auto start3 = high_resolution_clock::now();
    burb.polimorfismo(b, a, &my2);
    auto end3 = high_resolution_clock::now();
    burb.imprimir(b, a);
    cout << "Tiempo: " << duration_cast<milliseconds>(end3 - start3).count() << " ms\n\n";

    // PUNTERO A FUNCION
    generador(n_array, b);
    cout << "Ordenando con metodo de puntero a funcion:" << endl;
    bool(*d)(int, int) = &cmp2;
    auto start4 = high_resolution_clock::now();
    burb.puntero_funcion(b, a, d);
    auto end4 = high_resolution_clock::now();
    burb.imprimir(b, a);
    cout << "Tiempo: " << duration_cast<milliseconds>(end4 - start4).count() << " ms\n\n";

    // FUNCTOR
    generador(n_array, b);
    cout << "Ordenando con functores:" << endl;
    ascen<int> as;
    Burbuja_functor<ascen<int>> burbuja_ascendente(as);
    auto start5 = high_resolution_clock::now();
    burbuja_ascendente.burbujitancia(b, a);
    auto end5 = high_resolution_clock::now();
    burb.imprimir(b, a);
    cout << "Tiempo: " << duration_cast<milliseconds>(end5 - start5).count() << " ms\n\n";

    delete[] b;
    return 0;
}