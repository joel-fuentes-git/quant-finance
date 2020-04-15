/******************************************************************************

                   Assignment 2 (C/C++)
  Due: Tuesday, June 26 by 6 PM.
  Write a function to price European Call options using Black
Scholes formula.
  Use it to price 1 million options.
  Measure time taken to price 1 million options.
  Vectorizing/parallelizing code is NOT required.
  
  Followed closely http://math60082.blogspot.com/2013/02/c-coding-black-scholes-formula.html
  was not able to complete* did not price 1 million options

*******************************************************************************/

#include <iostream>
#include <cmath>
using namespace std;

double normalDistribution(double x)
{
  static const double RT2PI = sqrt(4.0*acos(0.0));
  static const double SPLIT = 10./sqrt(2);
  static const double a[] = {220.206867912376,221.213596169931,112.079291497871,33.912866078383,6.37396220353165,0.700383064443688,3.52624965998911e-02};
  static const double b[] = {440.413735824752,793.826512519948,637.333633378831,296.564248779674,86.7807322029461,16.064177579207,1.75566716318264,8.83883476483184e-02};
  
  const double z = fabs(x);
  double Nz = 0.0;
  
  // if z outside these limits then value effectively 0 or 1 for machine precision
  if(z<=37.0)
  {
    // NDash = N'(z) * sqrt{2\pi}
    const double NDash = exp(-z*z/2.0)/RT2PI;
    if(z<SPLIT)
    {
      const double Pz = (((((a[6]*z + a[5])*z + a[4])*z + a[3])*z + a[2])*z + a[1])*z + a[0];
      const double Qz = ((((((b[7]*z + b[6])*z + b[5])*z + b[4])*z + b[3])*z + b[2])*z + b[1])*z + b[0];
      Nz = RT2PI*NDash*Pz/Qz;
    }
    else
    {
      const double F4z = z + 1.0/(z + 2.0/(z + 3.0/(z + 4.0/(z + 13.0/20.0))));
      Nz = NDash/F4z;
    }
  }
  return x>=0.0 ? 1-Nz : Nz;
}

// return the value of a call option using the black scholes formula
double callOptionPrice(double S,double t,double X,double r,double sigma,double T)
{
  if(S<1.e-14)return 0.; // check if asset worthless
  if(sigma<1.e-14) // check if sigma zero
  {
    if(S<X*exp(-r*(T-t)))return 0.;
    else return S-X*exp(-r*(T-t));
  }
  if(fabs(T-t)<1.e-14) // check if we are at maturity
  {
    if(S<X)return 0.;
    else return S-X;
  }
  // calculate option price
  clock_t startTime = clock();
  double d1=(log(S/X) + (r+sigma*sigma/2.)*(T-t))/(sigma*sqrt(T-t));
  double d2=(log(S/X) + (r-sigma*sigma/2.)*(T-t))/(sigma*sqrt(T-t));
  cout << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << endl;
  return normalDistribution(d1)*S - normalDistribution(d2)*X*exp(-r*(T-t));

}

int main()
{
  cout << "Call Option Price = " << callOptionPrice(1,0,1,0.05,0.2,1) << endl;
  return 0;
}

// test output 
// 2.1e-05 seconds.                                                                                                     
// Call Option Price = 0.104506
