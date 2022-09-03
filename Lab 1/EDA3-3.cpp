#include <iostream>
#include <stdlib.h>

int *gpVect = NULL; 
struct Vector
{
public:
int *m_pVect=NULL, // Pointer to the buffer
m_nCount, // Control how many elements are actually used
m_nMax, // Control how many are allocated as maximum
m_nDelta; // To control the growing
};

void Resize(Vector *pThis)
{
/*pThis->m_pVect =(int *) realloc(gpVect, sizeof(int) *
(pThis->m_nMax + pThis->m_nDelta));
// The Max has to be increased by delta
pThis->m_nMax += pThis->m_nDelta;*/
}

void Insert(Vector *pThis, int elem)
{
//if( pThis->m_nCount == pThis->m_nMax ){} // Verify the overflow
Resize(pThis); // Resize the vector before inserting elem
// Insert the element at the end of the sequence
pThis->m_pVect[pThis->m_nCount++] = elem;
}



int main() {
  Vector* v1;
  Insert(v1, 4);
}