#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
using namespace std;

const long long MOD = 1000000007;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Abrir el archivo de entrada "A.txt"
    ifstream in("A.txt");
    if (!in) {
        cerr << "Error abriendo el archivo A.txt\n";
        return 1;
    }
    
    while(true){
        int n;
        in >> n;
        if(n == 0) break;
        
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            in >> a[i];
        }
        
        // Si no hay al menos 2 días, no se puede organizar el concurso.
        if(n < 2){
            cout << 0 << "\n";
            continue;
        }
        
        vector<long long> left(n), right(n);
        stack<int> st;
        
        // Calcular left[i]: cantidad de días consecutivos a la izquierda en los que a[i] es el mínimo.
        for (int i = 0; i < n; i++){
            while(!st.empty() && a[st.top()] > a[i]){
                st.pop();
            }
            left[i] = st.empty() ? i + 1 : i - st.top();
            st.push(i);
        }
        
        // Limpiar el stack para reutilizarlo en el cálculo de right.
        while(!st.empty()) st.pop();
        
        // Calcular right[i]: cantidad de días consecutivos a la derecha en los que a[i] es el mínimo.
        for (int i = n - 1; i >= 0; i--){
            while(!st.empty() && a[st.top()] >= a[i]){
                st.pop();
            }
            right[i] = st.empty() ? n - i : st.top() - i;
            st.push(i);
        }
        
        // Calcular la respuesta acumulando la contribución de cada día.
        long long ans = 0;
        for (int i = 0; i < n; i++){
            // left[i] * right[i] da el total de intervalos donde a[i] es el mínimo.
            // Se resta 1 para eliminar el intervalo de un solo día.
            long long countIntervals = left[i] * right[i] - 1;
            // Sólo se consideran aquellos días en los que es posible tener al menos 2 equipos (a[i] >= 2)
            if(a[i] >= 2){
                long long contrib = ((a[i] - 1LL) % MOD) * (countIntervals % MOD) % MOD;
                ans = (ans + contrib) % MOD;
            }
        }
        cout << ans % MOD << "\n";
    }
    
    in.close();
    return 0;
}
