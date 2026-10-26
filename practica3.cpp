#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>

using namespace std;

typedef int T;

vector<vector<T>> Matriz;

int inf = std::numeric_limits<int>::max();

T monedas(const std::vector<int>& V, int M) {
    int n = V.size();

    Matriz.assign(n, vector<T>(M + 1, inf));

    Matriz[0][0] = 0;

    for (int j = 1; j < M + 1; j++) {
        if (j >= V[0] && Matriz[0][j - V[0]] != inf) {
            Matriz[0][j] = 1 + Matriz[0][j - V[0]];
        }
    }

    for (int i = 1; i < n; i++) {
        Matriz[i][0] = 0;
        for (int j = 1; j < M + 1; j++) {
            if (j < V[i] || Matriz[i][j - V[i]] == inf) {
                Matriz[i][j] = Matriz[i - 1][j];
            } else if (Matriz[i - 1][j] != inf) {
                Matriz[i][j] = min(Matriz[i - 1][j], 1 + Matriz[i][j - V[i]]);
            } else {
                Matriz[i][j] = 1 + Matriz[i][j - V[i]];
            }
        }
    }

    return Matriz[n - 1][M];
}

std::vector<int> Sol(const std::vector<int>& V, int M) {
    int n = V.size();
    vector<int> sol(n, 0);

    int i = n - 1;
    int j = M;

    if (Matriz[i][j] == inf) {
        return sol;
    }
	while (j > 0 && i >= 0) {
        if (i > 0 && Matriz[i][j] == Matriz[i - 1][j]) {
            i--; 
        } else {
            sol[i]++;
            j = j - V[i];
        }
    }


    return sol;
}


typedef int T;

std::vector<int> Mochila(int P, const std::vector<int>& precio, const std::vector<int>& peso) {
    int n = precio.size();
    std::vector<int> Posiciones;

    if (n != peso.size()) {
        cout << "El vector de precios y de peso no tienen el mismo numero de elementos\n";
        return Posiciones;
    }
    vector<vector<int>> Mat(P + 1, std::vector<int>(n + 1, 0));

    for (int i = 1; i <= P; i++) {
        for (int j = 1; j <= n; j++) {
            if (peso[j - 1] <= i) {
                Mat[i][j] = max(precio[j - 1] + Mat[i - peso[j - 1]][j - 1], Mat[i][j - 1]);
            } else {
                Mat[i][j] = Mat[i][j - 1];
            }
        }
    }

    int i = P;
    int j = n;

    while (i > 0 && j > 0) {
        if (peso[j - 1] <= i && Mat[i][j] == precio[j - 1] + Mat[i - peso[j - 1]][j - 1] && Mat[i][j] != Mat[i][j - 1]) {
            Posiciones.push_back(j - 1);
            i = i - peso[j - 1];
            j--;
        } else {
            j--;
        }
    }

    return Posiciones;
}

void visualizarMochila(int P, const std::vector<int>& precio, const std::vector<int>& peso, const std::vector<int>& seleccionados) {
    cout << "RESUMEN DE LA MOCHILA\n";
    cout << "Peso maximo: " << P << "\n\n";
    cout << "Elementos disponibles:\n";
    for (int i = 0; i < precio.size(); i++) {
        cout << "  Objeto " << i << " -> Peso: " << peso[i] << "   Precio: " << precio[i] << "\n";
    }
    cout << "\n\n";
    cout << "Elementos seleccionados:\n";
    int pesoTotal = 0;
    int valorTotal = 0;
    if (seleccionados.empty()) {
        cout << "  (Ningun elemento seleccionado)\n";
    } else {
        for (int i = 0; i < seleccionados.size(); i++) {
            cout << "  -> Objeto " << seleccionados[i] << " (Peso: " << peso[seleccionados[i]] << ", Precio: " << precio[seleccionados[i]] << ")\n";
            pesoTotal += peso[seleccionados[i]];
            valorTotal += precio[seleccionados[i]];
        }
    }
    cout << "\nValor total: " << valorTotal << "\n\n";
}


void probarMonedas(int num, const std::vector<int>& V, int M) {                 
    cout << "\nCASO DE PRUEBA " << num << "\n\n";
    cout << "Monedas disponibles: { ";
    for (int i = 0; i < V.size(); ++i) {
        cout << "  " << V[i] << "  ";
  
    }
    cout << "}\nDinero a alcanzar: " << M << "\n\n";

    T min_monedas = monedas(V, M);

    if (min_monedas != inf) {
        vector<int> frecuencias = Sol(V, M);

        cout << " Num minimo de monedas: " << min_monedas << "\n";
        cout << " Contador monedas:\n";
        for (int i = 0; i < V.size(); ++i) {
            if (frecuencias[i] > 0) {
                cout << "   Monedas de " << V[i] << ": " << frecuencias[i] << "\n";
            }
        }
    } else {
        cout << "Imposible dar el cambio exacto\n";
    }
    cout << "\n";
}

int main() {

    probarMonedas(1, {1, 3, 4}, 6);
    probarMonedas(2, {3, 5}, 7);
    probarMonedas(3, {1, 2, 5, 10, 20}, 38);


int capacidad = 8;
    std::vector<int> precios = {10, 15, 40, 50};
    std::vector<int> pesos   = {1,  2,  3,  5};
    visualizarMochila(capacidad, precios, pesos, Mochila(capacidad, precios, pesos));


    return 0;
}
