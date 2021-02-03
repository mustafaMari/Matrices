#include <iostream>
#include "Matrix.h"
#include "Vector.h"
int main() {
     cout<<"Creating a matrix with the given dimensions (default value is 0 as stated in the constructor): "<<endl;
     Matrix<int> matrix(3,5);
     matrix.printMatrix();
     cout<<"Assigning a value to the a specific index of the matrix"<<endl;
     matrix.setElement(2,4,6);
     matrix.printMatrix();
     cout<<"Creating a vector by selecting the indicated row or column of the matrix"<<endl;
     Vector<int> vector(matrix.getRow(2), matrix.getRowsSize());
     vector.printVector();
     cout<<"Assigning a square matrix of values corresponding to the identity matrix"<<endl;
     size_t size = 3;
     Matrix<double> matrix1 (size , 7.3);
     matrix1.printMatrix();
     cout<<"Creating a matrix from a file: "<<endl;
     Matrix<int> matrix2 (5,3 ,"matrix.txt");
     matrix2.printMatrix();
     cout<<"Creating a matrix from a file: (different type) "<<endl;
     Matrix<float> matrix3 (3,6,"matrix.txt");
     matrix3.printMatrix();
     cout<<"Matrices addition: "<<endl;
     Matrix<int> matrix4(3,3,"matrix.txt");
     matrix2+=matrix4;
     matrix2.printMatrix();
     cout<<"Matrices subtraction: "<<endl;
     matrix2-=matrix4;
     matrix2.printMatrix();
     cout<<"Matrix multiplied by a matrix: "<<endl;
     matrix2*=matrix4;
     matrix2.printMatrix();
     cout<<"Matrix multiplied by a number: "<<endl;
     matrix2*=2;
     matrix2.printMatrix();
     cout<<"Matrix multiplied by a vector: "<<endl;
     Vector<int> vector1(3);
     vector1.setRandom();
     matrix2*=vector1;
     matrix2.printMatrix();
     cout<<"The dotProduct of a row and a column in a matrix: "<<endl;
     int dotProduct = matrix2.dotProduct(0,0);
     cout<<dotProduct<<endl;
     cout<<"The scalar product of 2 vectors: "<<endl;
     Vector<int> vector2(3);
     vector2.setRandom();
     int scalarProduct = vector1.scalarProduct(vector2);
     cout<<scalarProduct<<endl;
     cout<<"Finding the determinate of a 4*4 matrix: "<<endl;
     auto ** matrix5 = new double *[]{
      new double []{2,5,1,3},
      new double []{4.2,1.2,7,9},
      new double []{6.75,8,3,2},
      new double []{7.24,8.65,1,4}
     };
     Matrix<double> matrix6(matrix5,4,4);
     matrix6.printMatrix();
     double determinate = matrix6.det(matrix5,4);
     cout<<"The determinate of the previous matrix is : \n"<<determinate<<endl;
     int ** testTranspose = new int*[]{
            new int[]{1,2,3,4,5},
            new int[]{6,7,8,9,10},
            new int[]{11,12,13,14,15},
            new int[]{16,17,18,19,20},
            new int[]{21,22,23,24,25}
     };
     Matrix<int> matrix7(testTranspose,5,5);
     cout<<"The matrix before transpose: "<<endl;
     matrix7.printMatrix();
     cout<<"The matrix after transpose: "<<endl;
     matrix7.transpose();
     matrix7.printMatrix();
     return 0;
}
