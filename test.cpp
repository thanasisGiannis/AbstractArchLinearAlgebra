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
    
    std::unique_ptr<mpjd::LinearAlgebra::Vector<int>> 
    myVectorGPU      = la.newVector<int>(mpjd::LinearAlgebra::target_arch::GPU);
    
    std::cout << "Size = " << myVectorDefault->size() << std::endl;
    std::cout << "Size = " << myVectorGPU->size() << std::endl;
    std::cout << "Size = " << myVectorCPU->size() << std::endl;
    return 0;
}