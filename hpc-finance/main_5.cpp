// Call option - Monte Carlo method

#include <iostream>
#include <random>
#include <math.h>
#include <chrono>
using namespace std;

/*  double stoc_walk: returns simulated price after periods
    p = price at t=t0
    dr = drift
    vol = volatility
    periods (days)
*/

std::default_random_engine generator;

double stoc_walk(double p,double dr,double vol,int periods)
{
    double mean = 0.0;
    double stdv = 1.0;

    std::normal_distribution<double> distribution(mean,stdv);

    for(int i=0; i < periods; i++)
    {
        double w = distribution(generator);
        p += dr*p + w*vol*p;
    }
    return p;
}

int main()
{
    //Initialize variables

    double s0 = 10.0;           //Initial price
    double drift = 0.001502;    //daily drift
    double volatility = 0.026;  //volatility (daily)
    double r = 0.02;            //Risk free yearly rate
    int days = 255;             //Days
    int N = 1000000;             //Number of Monte Carlo trials
    double zero_trials = 0.0;

    double k = 12.0;             //Strike price

                                 //Initialize random number generator

    //Calculate N payoffs

    double avg = 0.0;

    for(int j=0; j < N; j++)
    {
        double temp = stoc_walk(s0,drift,volatility,days);
        if(temp > k)
        {
            double payoff = temp - k;
            payoff = payoff * exp(-r);
            avg += payoff;
        }
        else
        {
            zero_trials += 1;
        }
    }

    //Average the results

    double price_ = avg/(double)N;

    //Print results

    cout << "Option Pricing: Monte Carlo Plain Vanilla Call" << endl;
    cout << "Option price: " << price_ << endl;
    cout << "Initial price: " << s0 << endl;
    cout << "Strike price: " << k << endl;
    cout << "Daily expected drift: " << drift*100 << "%" << endl;
    cout << "Daily volatility: " << volatility*100 << "%" << endl;
    cout << "Total trials: " << N << endl;
    cout << "Zero trials: " << zero_trials << endl;
    cout << "Percentage of total trials: " << zero_trials/N*100 << "%";

    return 0;
}

// Test output 
// Option Pricing: Monte Carlo Plain Vanilla Call
// Option price: 3.69308                                                                                                                        
// Initial price: 10                                                                                                                            
// Strike price: 12                                                                                                                             
// Daily expected drift: 0.1502%                                                                                                                
// Daily volatility: 2.6%                                                                                                                       
// Total trials: 1000000                                                                                                                        
// Zero trials: 391523                                                                                                                          
// Percentage of total trials: 39.1523%




