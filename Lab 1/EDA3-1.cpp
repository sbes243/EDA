#include <iostream>
#include <vector>

int vec1[100]; 

int cont=0;
void insertar(int a){
  if( cont < 100 ) // we can only insert if there is space
  vec1[cont++] = a;
}
int main() {
 insertar(9);
}