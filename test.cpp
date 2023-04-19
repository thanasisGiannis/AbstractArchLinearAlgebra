#include "LinearAlgebra.h"

#include <iostream>
#include <memory>
#include <string_view>
#include <source_location>

#define coutred "\033[0;31m"
#define coutgreen "\033[1;32m"
#define coutyellow "\033[1;33m"
#define coutreset "\033[0m"
#define coutcyan "\033[0;36m"

#define FUNC_NAME(a) std::string() + a;
#define CHECK(a,...) \
std::cout << coutyellow << "Start Test: " << coutcyan << #a << coutreset << std::endl;\
if(false == a(__VA_OPT__(,) __VA_ARGS__)) { \
    std::cout << coutred << "FAILED TEST: " << coutcyan << #a << coutreset <<std::endl; exit(-1);\
};\
std::cout << coutgreen << "Success Test: " << coutcyan << #a << coutreset << std::endl;


using mpjdVector = std::shared_ptr<mpjd::LinearAlgebra<int>::Vector>;


bool Vector_capacity_test() {

    mpjd::LinearAlgebra<int> la;
    mpjdVector
    vec      = la.newVector(mpjd::LinearAlgebra<int>::target_arch::CPU);
    
    bool testValidity = true;
    try {
        vec->reserve(0);
        testValidity &=  (vec->capacity() == 0);
        vec->reserve(5);
        testValidity &=  (vec->capacity() == 5);
    } catch (...) {
        testValidity = false;
    }
    return testValidity;
}


bool Vector_size_test() {

    mpjd::LinearAlgebra<int> la;
    mpjdVector
    vec      = la.newVector(mpjd::LinearAlgebra<int>::target_arch::CPU);

    bool testValidity = true;
    try {
        testValidity &=  (vec->size() == 0);
        vec->push_back(3);
        testValidity &=  (vec->size() == 1);

        // return vec to original state
        vec->clear();
        testValidity &=  (vec->size() == 0);
    } catch (...) {
        testValidity = false;
    }
    return testValidity;
}

bool Vector_iterator_test() {

    mpjd::LinearAlgebra<int> la;
    mpjdVector
    vec      = la.newVector(mpjd::LinearAlgebra<int>::target_arch::CPU);

    bool testValidity = true;
    try {
        std::vector<int> nums({0,1,2,3,4,5,6,7,8,9});
        for(auto i : nums) vec->push_back(i);

        auto num  = nums.begin();
        for( auto vVal = vec->begin(); vVal!= vec->end(); vVal++,num++){
            if(*num != *vVal) {
                testValidity &= false;
            }
        }

        auto num_r  = nums.rbegin();
        for( auto vVal = vec->rbegin(); vVal!= vec->rend(); vVal++, num_r++){
            if(*(num_r) != *(vVal)) {
                testValidity &= false;
            }
        }
        
        mpjd::LinearAlgebra<int>::Vector::Iterator it2 = vec->begin();
        ++it2;
        mpjd::LinearAlgebra<int>::Vector::Iterator it3;
        it3 = it2;

        testValidity &= (*it3 == *it2);

        ++it3;
        testValidity &= (*it3 != *it2);


    } catch (...) {
        testValidity = false;
    }
    return testValidity;

}

bool Vector_resize_test() {
    
    mpjd::LinearAlgebra<int> la;
    mpjdVector
    vec      = la.newVector(mpjd::LinearAlgebra<int>::target_arch::CPU);

    bool testValidity = true;
    try {

        vec->resize(10);
        if(10 != vec->size()){
            testValidity &= false;
        }

        vec->resize(9);
        if(9 != vec->size()){
            testValidity &= false;
        }

        vec->clear();
        if(0 != vec->size()){
            testValidity &= false;
        }

        vec->resize(15);
        if(15 != vec->size()){
            testValidity &= false;
        }
    } catch (...) {
        testValidity = false;
    }
    return testValidity;

}

bool Vector_init_with_zero_vals() {

    mpjd::LinearAlgebra<int> la;
    mpjdVector
    vec      = la.newVector(mpjd::LinearAlgebra<int>::target_arch::CPU);

    bool testValidity = true;
    try {
        std::vector<int> nums({1,2,3,4,5,6,7,8,9,10});
        for(auto i : nums) vec->push_back(i);

        vec->init(0);

        auto num_r  = nums.begin();
        for( auto vVal = vec->begin(); vVal!= vec->end(); vVal++, num_r++){
            if((*num_r) == (*vVal)) {
                testValidity &= false;
            }
        }
    } catch (...) {
        testValidity = false;
    }
    return testValidity;
}


int main(){

    CHECK(Vector_capacity_test);
    CHECK(Vector_size_test);
    CHECK(Vector_iterator_test);
    CHECK(Vector_init_with_zero_vals);
    CHECK(Vector_resize_test);

    /*

    std::cout << "SHARED_COUNT: " << myVectorCPU.use_count() << std::endl;

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
    

    std::shared_ptr<mpjd::LinearAlgebra::Vector<int>>
    myVectorCPU2 = myVectorCPU; 

    std::cout << myVectorCPU2 << " " << myVectorCPU << std::endl;
    myVectorCPU->clear();
    std::cout << "Capacity = " << myVectorCPU->capacity() << std::endl;
    std::cout << "Arch = " << myVectorCPU->getArch() << std::endl;

    std::cout << "Size = " << myVectorCPU->size() << std::endl;
*/
    return 0;
}