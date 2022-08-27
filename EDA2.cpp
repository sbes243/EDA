#include <iostream>
#include <stdlib.h>

int *vec1=NULL;
int cont =0;
int memoria=0;

void Resize()
{
  const int delta = 10;
   int *pTemp, i;
   pTemp = new int[memoria + delta]; // Alloc a new vector
   for(i = 0 ; i < memoria ; i++){ // Transfer the elements
   pTemp[i] = vec1[i];
     } // we can also use the function memcpy
   delete [ ] vec1; // delete the old vector
   vec1 = pTemp;
  
}
void Insert(int elem)
{
if( cont == memoria ){ // There is no space at this moment for elem
Resize();
  } // Resize the vector before inserting elem
vec1[cont++] = elem; // Insert the element at the end of the sequence
}


int main() {
  Insert(4);
}
