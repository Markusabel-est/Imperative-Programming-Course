#include <iostream>
#include <algorithm>
#include <cmath>
#include <stdio.h>

using namespace std;



void inclusion (double e, double v)
{
    // we declare variables here
    double a = 0.0;
    double b = max(v, 1.0);
    double x = (a+b)/2;
    int count_inc = 0;
    
    // if the number is zero then the square root is always zero
    if(a*a == v){
        
        cout << "Inclusion square root of v is " << a << endl;
        return;
    }
    // if the number is one then the square root is always one
    if(b*b == v){
        cout << "Inclusion square root of v is " << b << endl;
        return;
    }

    // output for the values of n, an, xn, bn
    cout << "n\t" << "an\t" << "xn\t" << "bn" << endl;
    cout << 0 << "\t" << a << "\t" << x << "\t" << b << endl;

    // while loop goes until The final value xn satisfies the property |xn · xn − v| ≤ ε
    while(abs((x * x) - v) > e){
        if(x * x < v){
            a = x;
        }
        else{
            b = x;
        }
        x = (a+b)/2;
        
        count_inc++;
        // outputs the values of n, an, xn, bn for every while loop
        cout << count_inc << "\t" << a << "\t" << x << "\t" << b << endl;
        count_inc++;

    }

    cout << "Inclusion square root of " << v << " is " << x << endl;
}

/********************************************************************
    Assignment part 3: Newton-Raphson
********************************************************************/
void newton_raphson (double e, double v)
{
    // we declare variables
    double x = max(v,1.0);
    int count_newton = 0;
    //output for variables n and xn
    cout << "n\t" << "xn\t"<< endl;
     cout << 0 <<"\t" << v <<"\t"<< endl;

    // while loop goes until The final value xn satisfies the property |xn · xn − v| ≤ ε
    while(abs((x * x) - v) > e){
        x = x - (((x*x) - v) / (2*x));

        count_newton++;
        cout << count_newton << "\t" << x << endl;
        
    }

    cout << "Newton Raphson square root of " << v << " is " << x << " for e = " << e << endl;
}

int main ()
{
    // If v = 0, since a starts at 0, a*a = v so the edge case is true. then the inclusion square root will be 0
    inclusion(0.1, 0);
    
    // Since the maximum between 1.0 and 1 is still 1.0, b = 1.0 which means the edge case, b*b = v is true so
    inclusion(0.1, 1);
    
    // b = 1.0 a = 0, x0 = 0.5
    // check if |x0 * x0 - 0.5| > 0.1 this is true so we move on to iteration 1
    // check if x0 * x0 < v this is true so a1 = 0.5 b1 = 1 and x1 = 0.75
    // check if |x1 * x1 - 0.5| > 0.1 this is false so the Inclusive root of 0.5 is 0.75
    inclusion(0.1, 0.5);

    // a0 = 0, b0 = 25, x0 = 12.5
    // check if |x0 * x0 - 25| > 0.1 this is true so we move on to iteration 1
    // check if x0 * x0 < v this is false so a1 = 0  b1 = 12.5 and x1 = 6.25
    // Continue iterating until the square root is reached with |x0 * x0 - 25| < 0.1
    inclusion(0.1, 25);

    // a0 = 0, b0 = 60, x0 = 30
    // check if |x0 * x0 - 60| > 0.1 this is true so we move on to iteration 1
    // check if x0 * x0 < v this is false so a1 = 0  b1 = 30 and x1 = 15
    // Continue iterating until the square root is reached with |x0 * x0 - 60| < 0.1
    inclusion(0.1, 60);

    // x0 = 1
    // x1 = x0 - (((x0*x0) - v) / (2*x0)) = 0.5
    // check for x1*x1 - v > 0.1 is true so 
    // x2 = x1 - (((x1*x1) - v) / (2*x1)) = 0.25
    // check for x1*x1 - v > 0.1 false so the square root of 0 is 0.25 because 0.25 is close enough to 0
    newton_raphson(0.1, 0);

    // x0 = 1
    // x1 = x0 - (((x0*x0) - v) / (2*x0)) = 1
    // check for x1*x1 - v > 0.1 is false so the Newton raphson square root of 1 is 1
    newton_raphson(0.1, 1);

    // x0 = 1
    // x1 = x0 - (((x0*x0) - v) / (2*x0)) = 0.75
    // check for x1*x1 - v > 0.1 is false so the Newton raphson square root of 0.5 is 0.75
    newton_raphson(0.1, 0.5);

   
    // x0 = 25
    // x1 = x0 - (((x0*x0) - v) / (2*x0)) = 13
    // check for x1*x1 - v > 0.1 is true so 
    // x2 = x1 - (((x1*x1) - v) / (2*x1)) = 7.4615
    // check for x2*x2 - v > 0.1 is true so 
    // x3 = x2 - (((x2*x2) - v) / (2*x2)) = 5.406
    // check for x3*x3 - v > 0.1 is true so 
    // x4 = x3 - (((x3*x3) - v) / (2*x3)) = 5.015
    // check for x4*x4 - v > 0.1 is false so  the Newton raphson square root of 25 is 5.015
    newton_raphson(0.1, 25);

    // x0 = 60
    // x1 = x0 - (((x0*x0) - v) / (2*x0)) = 30.5
    // check for x1*x1 - v > 0.1 is true so 
    // x2 = x1 - (((x1*x1) - v) / (2*x1)) = 16.173
    // check for x2*x2 - v > 0.1 is true so 
    // x3 = x2 - (((x2*x2) - v) / (2*x2)) = 9.967
    // check for x3*x3 - v > 0.1 is true so 
    // x4 = x3 - (((x3*x3) - v) / (2*x3)) = 7.985
    // check for x4*x4 - v > 0.1 is true so 
    // x5 = x4 - (((x4*x4) - v) / (2*x4)) = 7.75
    // check for x5*x5 - v > 0.1 is false so the Newton raphson square root of 60 is 7.75
    newton_raphson(0.1, 60);
    return 0;

    // for the square root of 60 the inclusion method does it in 22 steps and the other Newton-Raphson in 6 steps.
    // for the square root of 25 the inclusion method does it in 18 steps and the other Newton-Raphson in 6 steps.
    // for the square root of 0.5 the inclusion method does it in 3 steps and the other Newton-Raphson in 3 steps.

}
