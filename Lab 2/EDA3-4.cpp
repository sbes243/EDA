#include <iostream>
typedef int Type;
int *gpVect=NULL;
template <typename Type> class cvector{
private:
Type*m_pVect; 
int m_nCount, 
m_nMax, 
m_nDelta; 


public:
cvector(int delta = 10); 
void Insert(Type &elem); 

void Resize(); 
};
template <typename Type>void cvector<Type>::Resize(){
  m_pVect = (Type *) realloc(gpVect, sizeof(int) *
(m_nMax + m_nDelta));

m_nMax += m_nDelta;
}

template <typename Type> cvector<Type>::cvector(int delta)
{
  m_nDelta =delta;
}
template <typename Type> void cvector<Type>::Insert(Type &elem)
{
if( m_nCount == m_nMax ) 
Resize();
m_pVect[m_nCount++] = elem; 
}

using namespace std;

int main() {
  cvector<int> v1(10);
  int a=4;
  int *b=&a;
  v1.Insert(*b);
    }