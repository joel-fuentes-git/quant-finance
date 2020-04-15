/* Monte Carlo method for computing pi 

    Assignment 4 (C/C++)
  Due: Wednesday, July 11 by 6 PM.
  
   The area of the circle is Or2 = O, and the area of the square is (2r)2 = 4. The ratio of the area of the circle to the area of
    the square, O, is given by:
    O = AreaofCircle = Or2 = O AreaofSquare (2r )2 4
   
  Calculating the value of O using Monte Carlo involves the following steps:
    1. Assume the circle is centered at coordinates (0, 0).
    2. Generate N random points with coordinates (x, y) where x and
    y are independently drawn from a uniform distribution over
    the interval [-1, 1].
    3. Determine if each point lies inside the circle or not.
  The value of O can be estimated using the simulation results
    as follows.
    O= M = O N4
    where, N = total number of points generated and M = number of random points inside the circle.
  Write a program to calculate the value of O using information above, for N = 100, 1000 and 10000. Write the results to the standard output.
  Vectorizing/parallelizing code is NOT required.

*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#define SEED 35791246

main(int argc, char* argv)
{
   int niter=0;
   double x,y;
   int i,count=0; /* # of points in the 1st quadrant of unit circle */
   double z;
   double pi;

   printf("Enter the number of iterations used to estimate pi: ");
   scanf("%d",&niter);

   /* initialize random numbers */
   srand(SEED);
   count=0;
   for ( i=0; i<niter; i++) {
      x = (double)rand()/RAND_MAX;
      y = (double)rand()/RAND_MAX;
      z = x*x+y*y;
      if (z<=1) count++;
      }
   pi=(double)count/niter*4;
   printf("# of trials= %d , estimate of pi is %g \n",niter,pi);
}

// initial test output 
// for N = 100 , pi = 2.76
// for N = 1000 , pi = 3.172
// for N = 10000 , pi = 3.1256

