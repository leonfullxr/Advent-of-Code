#include <fstream>
#include <iostream>
#include <string>


using namespace std;

void solve(string file) {
    fstream input(file);
    char x;
    int a, b, c, d;
    int contiene = 0;
    int part2 = 0;

    while (input >> a >> x >> b >> x >> c >> x >> d) {
        if (a >= c && b <= d || c >= a && d <= b) contiene++;
        if (a >= c && a <= d || b >= c && b <= d || c >= a && d <= b) part2++;
    }
    cout << contiene << endl;
    cout << part2 << endl;
}

int main(int argc, char* argv[]) {
    solve("input.txt");
}
