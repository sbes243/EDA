#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <vector>

using namespace std;
unsigned t0, t1;

class punto {
public:
    int x;
    int y;
    int z;
    punto() {
        x = 0;
        y = 0;
        z = 0;
    }

};

void g1000(vector<punto>& v1) {
    srand(time(NULL));
    punto p1;
    for (int i = 0; i < 1000; i++) {
        p1.x = rand() % (201 - 0);
        p1.x = rand() % (201 - 0);
        p1.x = rand() % (201 - 0);
        v1.push_back(p1);
    }
}
void g10000(vector<punto>& v1) {
    srand(time(NULL));
    punto p1;
    for (int i = 0; i < 10000; i++) {
        p1.x = rand() % (301 - 0);
        p1.x = rand() % (301 - 0);
        p1.x = rand() % (301 - 0);
        v1.push_back(p1);
    }
}
void g50000(vector<punto>& v1) {
    srand(time(NULL));
    punto p1;
    for (int i = 0; i < 50000; i++) {
        p1.x = rand() % (501 - 0);
        p1.x = rand() % (501 - 0);
        p1.x = rand() % (501 - 0);
        v1.push_back(p1);
    }
}
double calculardist(vector<punto> v1) {
    t0 = clock();
    vector<float> distancia;
    for (int i = 1; i < v1.size(); i++) {
        float a = sqrt(pow(v1[0].x - v1[i].x, 2) + pow(v1[0].y - v1[i].y, 2) + pow(v1[0].z - v1[i].z, 2));
        distancia.push_back(a);
    }
    t1 = clock();
    double time = (double(t1 - t0) / CLOCKS_PER_SEC);
    return time;
}
int main() {
    vector<punto> p1;
    vector<punto> p2;
    vector<punto> p3;
    g1000(p1);
    g10000(p2);
    g50000(p3);
    cout << "tiempo de vector de 1000:" << calculardist(p1) << endl;
    cout << "tiempo de vector de 10000:" << calculardist(p2) << endl;
    cout << "tiempo de vector de 50000:" << calculardist(p1) << endl;
}