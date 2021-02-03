//
// Created by Mufasa on 1/24/2021.
//

#ifndef MATRICES_VECTOR_H
#define MATRICES_VECTOR_H
#include <iostream>
using namespace std;
template <typename T>
class Vector {
private:

public:
    T* vector;
    int size;
    Vector(int size);
    Vector(T* array, int size);
    ~Vector();
    void printVector();
    bool setIndex(int index, T value);
    bool setRandom();
    T scalarProduct(const Vector<T> &other);
    int getSize(){
        return size;
    }
};
template<typename T>
Vector<T>::Vector(int size) :size(size) {
    static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>, "Matrix of this type cannot be created");
      vector = new T[size]{0};
}
template<typename T>
T Vector<T>::scalarProduct(const Vector<T> &other) {
    if (this->size != other.size){
        cout << "Vectors with different sizes"<<endl;
        return 0;
    }
    T scalarProduct = 0;
    for (int i =0; i<size; i++){
        scalarProduct += this->vector[i] * other.vector[i];
    }
    return scalarProduct;
}

template<typename T>
void Vector<T>::printVector() {
    for (int i = 0; i<size; i++){
        cout<<vector[i]<<" ";
    }
    cout<<"\n"<<endl;
}

template<typename T>
Vector<T>::~Vector() {
    delete [] vector;
}

template<typename T>
bool Vector<T>::setIndex(int index, T value) {
    if (index < 0 || index > size){
        cout<<"index does not exist"<<endl;
        return false;
    }
    vector[index] = value;
}
template<typename T>
bool Vector<T>::setRandom() {
    for (int i = 0; i < size; i++){
        vector[i] = (T)rand();
    }
    return true;
}

template<typename T>
Vector<T>::Vector(T *array, int size) {
    static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>, "Matrix of this type cannot be created");
    this->size = size;
    vector = array;

}


#endif //MATRICES_VECTOR_H
