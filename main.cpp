#include <stdlib.h>
#include <iostream>
#include "src/sqr.h"

using namespace std;

int main( int argc, const char* argv[] )
{
  if (argc != 2)
    cout << "Uso: demo double\n";
  else
    {
      int a,SQR;
      a = atof(argv[1]);
      SQR = sqrpep(a);
      cout << a << "*" << a << " = " << SQR << endl;
    }
  return 0;
}
