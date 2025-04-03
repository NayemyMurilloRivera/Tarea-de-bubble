#include <iostream>
#include <cstdlib>
#include <ctime>   
using namespace std;

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
    void burbujitancia(int* a, int* b) {
        bool paso = true;
        while (paso) {
            paso = false;
            for (int* i = a; i < b; i++) {
                if (functor(*i, *(i+1))) {
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
            if (d(*i,(*i+1))){
                swap(*i, *(i + 1));
                paso = true;
            }
        }
    }
}

class Policambio2 : public Poli {
public:
    bool cambio(int* a, int* b) override {
        return *a > *b; // Ordenar de mayor a menor
    }
};

class Policambio : public Poli {
public:
    bool cambio(int* a, int* b) override {
        return *a < *b; // Ordenar de menor a mayor
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

void generador(int n_array, int*b) {
    for (int i = 0; i < n_array; i++) {
        b[i] = rand() % 1000000 + 1;
    }
}

int main() {
    srand(time(0));
    int* b = new int[n_array]; 
    int* a = b + n_array - 1; 
    
    generador(n_array, b);

    Burbuja burb;
    cout << "Ordenando con metodo burbuja_directa:" << endl;
    burb.burbuja_directa(b, a);
    burb.imprimir(b, a);

    generador(n_array, b);

    cout << "Ordenando con metodo polimorfismo (mayor a menor):" << endl;
    Policambio2 my;
    burb.polimorfismo(b, a, &my);
    burb.imprimir(b, a);

    generador(n_array, b);

    cout << "Ordenando con metodo polimorfismo (menor a mayor):" << endl;
    Policambio my2;
    burb.polimorfismo(b, a, &my2);
    burb.imprimir(b, a);

    generador(n_array, b);

    cout << "Ordenando con metodo de puntero a funcion:" << endl;
    bool(*d)(int, int);
    d=&cmp2;
    burb.puntero_funcion(b, a, d);
    burb.imprimir(b, a);

    generador(n_array, b);
    cout << "Ordenando con functores:" << endl;
    ascen<int> as;
    Burbuja_functor<ascen<int>> burbuja_ascendente(as);
    burbuja_ascendente.burbujitancia(b,a);



    delete[] b;
    return 0;

}
