#include "LinearAlgebra.h"

#include <iostream>
#include <memory>


int main(){

    mpjd::LinearAlgebra la;
    //mpjd::LinearAlgebra la(mpjd::LinearAlgebra::target_arch::GPU);
    std::unique_ptr<mpjd::LinearAlgebra::Vector<int>> 
    myVectorDefault  = la.newVector<int>();
    
    std::unique_ptr<mpjd::LinearAlgebra::Vector<int>> 
    myVectorCPU      = la.newVector<int>(mpjd::LinearAlgebra::target_arch::CPU);

    std::cout << "Capacity = " << myVectorCPU->capacity() << std::endl;
    std::cout << "Size = " << myVectorCPU->size() << std::endl;
    myVectorCPU->reserve(100);
    myVectorCPU->push_back(0);
    myVectorCPU->push_back(1);
    myVectorCPU->push_back(2);
    std::cout << "Capacity = " << myVectorCPU->capacity() << std::endl;
    std::cout << "Size = " << myVectorCPU->size() << std::endl;
    
    std::cout << "V[1] = " << (*myVectorCPU)[1] << std::endl;
    
    myVectorCPU->clear();
    std::cout << "Capacity = " << myVectorCPU->capacity() << std::endl;
    std::cout << "Size = " << myVectorCPU->size() << std::endl;
    
    //mpjd::LinearAlgebra::Vector<int>& myVectorCPU2 = (*myVectorCPU);
    

    
    std::unique_ptr<mpjd::LinearAlgebra::Vector<int>> 
    myVectorGPU      = la.newVector<int>(mpjd::LinearAlgebra::target_arch::GPU);
    
    std::cout << "Size = " << myVectorDefault->size() << std::endl;
    std::cout << "Size = " << myVectorGPU->size() << std::endl;
    std::cout << "Size = " << myVectorCPU->size() << std::endl;
    return 0;
}