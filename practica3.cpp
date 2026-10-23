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


        //visualizador hecho por IA


void probarCaso(int id, const std::vector<int>& V, int M) {                 
    cout << "========================================\n";
    cout << "CASO DE PRUEBA #" << id << "\n";
    cout << "========================================\n";
    cout << "Monedas disponibles: { ";
    for (size_t k = 0; k < V.size(); ++k) {
        cout << V[k] << (k + 1 < V.size() ? ", " : " ");
    }
    cout << "}\nMonto a alcanzar   : " << M << "\n\n";

    T min_monedas = monedas(V, M);

    if (min_monedas != inf) {
        vector<int> frecuencias = Sol(V, M);

        cout << "✓ Num. minimo de monedas: " << min_monedas << "\n";
        cout << "✓ Desglose por moneda   :\n";
        for (size_t k = 0; k < V.size(); ++k) {
            if (frecuencias[k] > 0) {
                cout << "   - Monedas de " << V[k] << ": " << frecuencias[k] << "\n";
            }
        }
    } else {
        cout << "✗ Resultado: IMPOSIBLE dar el cambio exacto con las monedas disponibles.\n";
    }
    cout << "\n";
}

int main() {

    probarCaso(1, {1, 3, 4}, 6);


    probarCaso(2, {3, 5}, 7);


    probarCaso(3, {1, 2, 5, 10, 20}, 43);

    return 0;
}
