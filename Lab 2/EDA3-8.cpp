#include <iostream>

using namespace std;

typedef float (*punt)(float, float);

float suma(float a, float b){
  return a+b;
}
float resta(float a, float b){
  return a-b;
}
float multi(float a, float b){
  return a*b;
}
float dividir(float a, float b){
  if (b <= 0){
    return -1;
  }
  return a/b;
}

int main(){
  punt ops[4] = { &::suma, &::resta, &::multi, &::dividir };
  float a,b,c;
  int opt;
  cin >> a >> b;
  cout << "Operaciones: 0->Suma, 1->Resta, 2->Multiplicación, 3->División: ";
  cin >> opt;
  c = ops[opt](a,b);
  cout << c << endl;
}