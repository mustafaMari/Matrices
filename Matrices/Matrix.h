//
// Created by Mufasa on 1/2/2021.
//
#ifndef MATRICES_MATRIX_H
#define MATRICES_MATRIX_H
#include <iostream>
#include <fstream>
#include "Vector.h"
//#include <type_traits>
using namespace std;
template <typename T>

class Matrix {

public:
    Matrix(int rowsNumber, int columnNumber);
    Matrix(size_t size, T value);
    Matrix(T** matrix, int rows, int columns);
    ~Matrix();
    void printMatrix();
    Matrix(int f_rows, int f_columns,const string& fileName);
    bool operator==(const Matrix<T>&other);
    Matrix<T>& operator=(const Matrix<T>&);
    Matrix<T>(const Matrix<T>&);
    Matrix<T>& operator+=(const Matrix<T> &cMatrix);
    Matrix<T>& operator-=(const Matrix<T> &cMatrix);
    Matrix<T>& operator*=(T number);
    Matrix<T>& operator*=(const Matrix<T> &cMatrix);
    Matrix<T>& operator*=(const Vector<T> &vector);
    Matrix<T> &transpose();
    // for the same matrix
    T dotProduct(int rowIndex, int columnIndex);
    T* getColumn(int index);
    T* getRow(int index);

     int getColumnSize();
    int getRowsSize(){
        return columns;
    }
    T det(T** matrix, int size);
    T getElem(int rowIndex, int columnIndex);
    bool setElement(int rowIndex, int columnIndex, T value);



private:
    T** matrix;
    int rows;
    int columns;
    T ** creatAMatrix(int rows1, int columns1);
    T**  removeColumnAndRow(T** matrix,int Rowindex,int ColumnIndex, int size);

};
template <typename T>
Matrix<T>::Matrix(int rowsNumber, int columnNumber) : rows(rowsNumber), columns(columnNumber) {
    static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>, "Matrix of this type cannot be created");
    matrix = new T*[rowsNumber];
    for (int i = 0; i<rowsNumber; i++)
        matrix[i] =  new T[columnNumber]{0};
}
template<typename T>
void Matrix<T>::printMatrix() {
    for(int x=0; x<rows; x++){
        for(int y=0; y<columns; y++){
            cout<<matrix[x][y]<<" ";
        }
        cout<<endl;
    }
    cout<<"\n"<<endl;
}
template<typename T>
Matrix<T>::Matrix(int f_rows, int f_columns, const string& fileName) {
    rows = f_rows;
    columns = f_columns;
    ifstream file;
    file.open(fileName);
    if(file.fail()) {
        cout << "Could not open the file" << endl;
        matrix = creatAMatrix(0,0);
    }

    else {
        matrix = creatAMatrix(rows, columns);
        for(int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; j++) {
                file >> matrix[i][j];
            }
        }
        file.close();
    }
}

template<typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &cMatrix) {
    if (this!=&cMatrix){
        delete[] matrix;
        matrix = new Matrix<T>(cMatrix.rows, cMatrix.columns);
        for(int i =0; i <rows; i++){
            for(int x=0; x<columns; x++){
                matrix[i][x] = cMatrix[i][x];
            }
        }
    }
    return *this;
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> &cMatrix) : rows(cMatrix.rows), columns(cMatrix.columns) {
    static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>, "Matrix of this type cannot be created");
    matrix = creatAMatrix(this->rows, this->columns);
//    for(int i =0; i <rows; i++)
//        for(int x=0; x<columns; x++)
//            matrix[i][x] = cMatrix[i][x];
}

template<typename T>
Matrix<T> &Matrix<T>::operator+=(const Matrix<T> &cMatrix) {
    if(*this == cMatrix)
        for (int i = 0; i < rows; i++)
            for (int x =0; x < columns; x++)
                matrix[i][x] = this->matrix[i][x] + cMatrix.matrix[i][x];
    else
        cout << "Matrices of different order cannot be added to each other"<<endl;
    return *this;
}

template<typename T>
Matrix<T> &Matrix<T>::operator-=(const Matrix<T> &cMatrix) {
    if(*this == cMatrix)
        for (int i = 0; i < rows; i++)
            for (int x =0; x < columns; x++)
                matrix[i][x] = this->matrix[i][x] - cMatrix.matrix[i][x];
    else
        cout << "Matrices of different order cannot be subtracted from each other"<<endl;
    return *this;
}

template<typename T>
bool Matrix<T>::operator==(const Matrix<T> &other) {
    return this->rows == other.rows && this->columns == other.columns;
}

template<typename T>
Matrix<T>::~Matrix() {
    for (int i = 0; i < rows; i++)
    {
        delete[] matrix[i];
    }
    delete matrix;
}

template<typename T>
Matrix<T> &Matrix<T>::operator*=(T number) {
    for (int i = 0; i < rows; i++)
        for (int x =0; x < columns; x++)
            matrix[i][x] = this->matrix[i][x] * number;

    return *this;
}


template<typename T>
Matrix<T> &Matrix<T>::operator*=(const Matrix<T> &cMatrix) {
    if (!(this->columns == cMatrix.rows)){
        cout<< "The 2 matrices are in an order where you cannot find their multiplication the original function is: "<<endl;
        return *this;

    }
    int newRows = rows;
    int newColumns = cMatrix.columns;
    auto* cMatrix1 = new Matrix<T>(newRows, newColumns);
    for (int i=0; i<rows; i++)
        for (int x = 0; x < cMatrix.columns; x++)
            for (int l = 0; l < columns; l++)
                cMatrix1->matrix[i][x] += matrix[i][l] * cMatrix.matrix[l][x];
    matrix = creatAMatrix(newRows, newColumns);
    matrix = cMatrix1->matrix;
    return *this;
}

template<typename T>
T Matrix<T>::dotProduct(int rowIndex, int columnIndex) {
    T dotProduct = 0;
    // as in arrays we start from index 0 therefore we need to subtract 1.
    T* row = getRow(rowIndex  );
    T* column = getColumn(columnIndex );
    for(int i =0; i < rows; i++){
            dotProduct += row[i] * column[i];

    }
    return dotProduct;
}

template<typename T>
T *Matrix<T>::getColumn(int index) {
    if (index > rows || index < 0)
        cout <<"the requested column does not exist"<<endl;
    T *column = new T[rows];
    for(int i =0; i<rows; i++){
        column[i] = matrix[i][index];
    }
    return column;
}

template<typename T>
T *Matrix<T>::getRow(int index) {
    if (index < 0 || index > columns)
        cout<<"the requested row does not exist"<<endl;
    T *row = new T[columns];
    for (int i =0; i<columns; i++){
        row[i]=matrix[index][i];
    }
    return row;
}
template<typename T>
T ** Matrix<T>::creatAMatrix(int rows1, int columns1)   {

    rows = rows1;
    columns = columns1;
    matrix = new T*[rows];
    for (int i = 0; i<rows; i++)
        matrix[i] =  new T[columns]{0};
    return matrix;
}

template<typename T>
Matrix<T> &Matrix<T>::operator*=(const Vector<T> &vector) {
    if (columns != vector.size){
        cout<< "the matrix's columns is different from the vector size.  the original function is: "<<endl;
        return *this;
    }
    auto* matrix1 = new Matrix<T>(rows, 1);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            matrix1->matrix[i][0] += (matrix[i][j] * vector.vector[j]);
    matrix = creatAMatrix(rows,1);
    matrix = matrix1->matrix;
    return *this;
}
template<typename T>
Matrix<T> &Matrix<T>::transpose() {
    auto* transpose = new Matrix<T>(columns, rows);
    for (int i = 0; i < rows; i++){
        for (int x =0; x < columns; x++ ){
            transpose->matrix[x][i] = matrix[i][x];
        }
    }
    matrix = creatAMatrix(columns,rows);
    matrix = transpose->matrix;
    return *this;
}

template<typename T>
Matrix<T>::Matrix(size_t size, T value) : rows(size), columns(size){
    static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>, "Matrix of this type cannot be created");
    matrix = creatAMatrix(size, size);
   for (int i = 0; i<size; i++){
       for (int x =0; x<size; x++){
           matrix[i][x] = value;
       }
   }
}

template<typename T>
T Matrix<T>::det(T** matrix, int size) {
    if (columns != rows) {
        cout << "we cannot calculate the det of a non square matrix" << endl;
        return 0;
    }
    rows = size;
    columns = size;
    T deter = 0;
    if (size == 1) {
        deter+= matrix[0][0];
    }
    if (size == 2 ){
        deter+= ((matrix[0][0]*matrix[1][1]) - (matrix[0][1]*matrix[1][0]));
    }else
        for (int i = 0; i < size ; i++){
            int sign = 1;
            if (i % 2 == 1) sign = -1;
            deter += sign * matrix[0][i] * det(removeColumnAndRow(matrix,0,i, size - 1), size - 1);
    }
    return deter;
}

template<typename T>
Matrix<T>::Matrix(T **matrix, int rows, int columns) :matrix(matrix), rows(rows), columns(columns){
    static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>, "Matrix of this type cannot be created");
}

template<typename T>
T **Matrix<T>::removeColumnAndRow(T** matrix, int Rowindex,int ColumnIndex, int size) {
    T** result = new T * [size];
    for (int i = 0; i < size; i++){
        result[i] = new T[size];
    }

    for (int i = 0, ii = 0; i <size; i++, ii++){
        if (i == Rowindex)
            ii++;
        for (int x = 0, xx = 0; x < size; x++, xx++){
            if (x == ColumnIndex)
                xx++;
            result[i][x] = matrix[ii][xx];
        }
    }
    return result;
}

template<typename T>
bool Matrix<T>::setElement(int rowIndex, int columnIndex, T value) {
    if (rowIndex > rows || rowIndex < 0 || columnIndex > columns || columnIndex < 0 )
        return false;
    else
        matrix[rowIndex][columnIndex] = value;
    return true;
}

template<typename T>
T Matrix<T>::getElem(int rowIndex, int columnIndex) {
    if (rowIndex > rows || rowIndex < 0 || columnIndex > columns || columnIndex < 0 )
        return 0;
    return matrix[rowIndex][columnIndex];
}

template<typename T>
int Matrix<T>::getColumnSize() {
    return rows;
}


#endif //MATRICES_MATRIX_H
