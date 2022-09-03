// File MyNS.h
namespace MyNS
{
int gnCount; // Global counter
// Some small function implemented inline
double Addition(double a, double b) // Global function
{ return a+b; }
// Some prototypes
long factorial(int n){
  long factorial=1;
for(int i=1;i<=n;i++){
        factorial = factorial * i;
  }
  return factorial;
}; 

}
