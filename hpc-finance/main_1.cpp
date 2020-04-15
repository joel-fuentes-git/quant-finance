// *******************************************************************************
// Assignment 1 (C/C++)
  // Due: Tuesday, June 26 by 6 PM.
  //Write a function to multiply two NxN matrices.
  //Use the function you wrote to multiply two 100x100 matrices.
  //Measure execution time.
  //Vectorizing/parallelizing code is NOT required.
  //There are many ways to represent a matrix. Any method, including the following, is acceptable.
 // use a library: e.g. Eigen
  // use std::vector:
      //using matrix = std::vector<std::vector<float>>;
      //or
      //typedef std::vector<std::vector<float>> matrix;...

#include<iostream>
using namespace std; 

int main ()
{
    int r1, c1, r2, c2, i, j, k; // r for rows, c for columns
    int A[5][5], B[5][5], C[5][5];
    cout << "Enter # of rows & columns of matrix A: ";
    cin >> r1 >> c1;
    cout << "Enter # of rows & columns of matrix B: ";
    cin >> r2 >> c2; 
    if (c1 != r2)
    {
        cout << "Error. Matrices cannot be multiplied because of the dimensions!";
        exit(0);
    }	
    cout << "Enter elements of matrix A: ";
    for (i = 0; i < r1; i++)
        for (j = 0; j < c1; j++)
            cin >> A[i][j];
    cout << "Enter elements of matrix B: ";
    for (i = 0; i < r2; i++)
        for (j = 0; j < c2; j++)
            cin >> B[i][j];		
    clock_t startTime = clock();
    for (i = 0; i < r1; i++)
    {
        for (j = 0; j < c2; j++)
        {
            C[i][j] = 0;
            for (k = 0; k < r2; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    cout << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << endl;
    cout << "Product of matrices\n";
    for (i = 0; i < r1; i++)
    {    
        for (j = 0; j < c2; j++)
            cout << C[i][j] << "  ";
        cout << "\n";
    }
      return 0;
}
// output for the multiplication of two matrices and the time of execution
 // Enter # of rows & columns of matrix A: 2 2                                                                                              
 // Enter # of rows & columns of matrix B: 2 2                                                                                              
 // Enter elements of matrix A: 2 3 4 5                                                                                                     
 // Enter elements of matrix B: 2 3 4 5                                                                                                     
 // 2e-06 seconds.                                                                                                                          
 // Product of matrices                                                                                                                     
// 16  21                                                                                                                                  
// 28  37 

