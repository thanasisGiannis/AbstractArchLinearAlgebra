#include "LinearAlgebra.h"

#include <iostream>
#include <memory>


int main(){

    mpjd::LinearAlgebra la;
    //std::unique_ptr<mpjd::LinearAlgebra::Vector<int>> myVector  = la.newVector<int>();
    mpjd::LinearAlgebra::Vector<int>* myVector  = new mpjd::LinearAlgebra::Vector<int>();

    std::cout << "Size = " << myVector->size() << std::endl;
    return 0;
}