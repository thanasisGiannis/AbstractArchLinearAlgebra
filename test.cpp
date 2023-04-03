#include "LinearAlgebra.h"

#include <iostream>
#include <memory>


int main(){

    mpjd::LinearAlgebra la;

    mpjd::LinearAlgebra::Vector<int>& 
    myVectorCPU      = la.newVector<int>(mpjd::LinearAlgebra::target_arch::CPU);

    std::cout << "Capacity = " << myVectorCPU.capacity() << std::endl;
    std::cout << "Size = " << myVectorCPU.size() << std::endl;
    myVectorCPU.reserve(100);
    myVectorCPU.push_back(0);
    myVectorCPU.push_back(1);
    myVectorCPU.push_back(2);
    std::cout << "Capacity = " << myVectorCPU.capacity() << std::endl;
    std::cout << "Size = " << myVectorCPU.size() << std::endl;
    mpjd::LinearAlgebra::Vector<int>::Iterator it = myVectorCPU.begin();

    std::cout << "V[1] = " << (myVectorCPU)[1] << std::endl;
    std::cout << "*(++it) = " << *(++it) << std::endl;
    
    myVectorCPU.clear();
    std::cout << "Capacity = " << myVectorCPU.capacity() << std::endl;
    std::cout << "Size = " << myVectorCPU.size() << std::endl;

    return 0;
}