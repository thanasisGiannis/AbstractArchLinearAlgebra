#include "LinearAlgebra.h"

#include <iostream>
#include <memory>


int main(){

    mpjd::LinearAlgebra la;

    std::shared_ptr<mpjd::LinearAlgebra::Vector<int>>
    myVectorCPU      = la.newVector<int>(mpjd::LinearAlgebra::target_arch::CPU);


    std::cout << "Capacity = " << myVectorCPU->capacity() << std::endl;
    std::cout << "Size = " << myVectorCPU->size() << std::endl;
    myVectorCPU->reserve(100);
    myVectorCPU->push_back(0);
    myVectorCPU->push_back(1);
    myVectorCPU->push_back(2);
    std::cout << "Capacity = " << myVectorCPU->capacity() << std::endl;
    std::cout << "Size = " << myVectorCPU->size() << std::endl;
    mpjd::LinearAlgebra::Vector<int>::Iterator it = myVectorCPU->begin();

    std::cout << "V[1] = " << (*myVectorCPU)[1] << std::endl;
    std::cout << "1 *(++it) = " << *(++it) << std::endl;

    std::cout << "V[1] = " << (*myVectorCPU)[1] << std::endl;
    std::cout << "2 *(--it) = " << *(--it) << std::endl;

    std::cout << "V[1] = " << (*myVectorCPU)[1] << std::endl;
    std::cout << "3 *(it) = " << *(it) << std::endl;
    std::cout << "4 *(it++) = " << *(it++) << std::endl;
    std::cout << "5 *(it) = " << *(it) << std::endl;

    std::cout << "3 *(it) = " << *(it) << std::endl;
    std::cout << "4 *(it--) = " << *(it--) << std::endl;
    std::cout << "5 *(it) = " << *(it) << std::endl;


    mpjd::LinearAlgebra::Vector<int>::Iterator it_end = myVectorCPU->end();
    std::cout << "it == it " << (it == it) << std::endl;
    std::cout << "it == it_end " << (it == it_end) << std::endl;
    std::cout << "it != it " << (it != it) << std::endl;
    std::cout << "it != it_end " << (it != it_end) << std::endl;
    
    //std::cout << "*(it_end) = " << *(it_end) << std::endl;

    mpjd::LinearAlgebra::Vector<int>::Iterator it2;
    it2 = it;

    const int *vector_ptr = myVectorCPU->data();
    std::cout << "*vector_ptr = " << (*vector_ptr) << std::endl;
    
    myVectorCPU->clear();
    std::cout << "Capacity = " << myVectorCPU->capacity() << std::endl;
    std::cout << "Size = " << myVectorCPU->size() << std::endl;

    return 0;
}