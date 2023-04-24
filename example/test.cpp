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

bool Vector_dot() {

    mpjd::LinearAlgebra<double> la;
    std::shared_ptr<mpjd::LinearAlgebra<double>::Vector>
    x      = la.newVector(mpjd::LinearAlgebra<double>::target_arch::CPU);

    std::shared_ptr<mpjd::LinearAlgebra<double>::Vector>
    y      = la.newVector(mpjd::LinearAlgebra<double>::target_arch::CPU);

    bool testValidity = true;
    try {
        std::vector<double> nums({1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0});
        for(auto i : nums){
            x->push_back(i);
            y->push_back(i);
        } 

        auto a = la.dot(x->size(),x->data(),1,y->data(),1);
        if(std::abs(10.0-a) > 1e-08){
            testValidity = false;
        }
    } catch (...) {
        testValidity = false;
    }
    return testValidity;
}

bool Vector_axpy() {

    mpjd::LinearAlgebra<double> la;
    std::shared_ptr<mpjd::LinearAlgebra<double>::Vector>
    x      = la.newVector(mpjd::LinearAlgebra<double>::target_arch::CPU);

    std::shared_ptr<mpjd::LinearAlgebra<double>::Vector>
    y      = la.newVector(mpjd::LinearAlgebra<double>::target_arch::CPU);

    bool testValidity = true;
    try {
        std::vector<double> nums({1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0});
        for(auto i : nums){
            x->push_back(i);
            y->push_back(i);
        } 

        la.axpy(x->size(),1.0,x->data(),1,y->data(),1);

        for(auto i=0; i<x->size(); i++){
            if(std::abs(static_cast<double>(2.0)-(*y)[i]) > 1e-08){
                testValidity = false;
            }
        }
    } catch (...) {
        testValidity = false;
    }
    return testValidity;
}

bool Vector_nrm2() {

    mpjd::LinearAlgebra<double> la;
    std::shared_ptr<mpjd::LinearAlgebra<double>::Vector>
    x      = la.newVector(mpjd::LinearAlgebra<double>::target_arch::CPU);

    bool testValidity = true;
    try {
        std::vector<double> nums({0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0});
        for(auto i : nums){
            x->push_back(i);
        } 

        auto nrmx = la.nrm2(x->size(),x->data(),1);

        if(std::abs(static_cast<double>(0.0)-nrmx) > 1e-08){
            testValidity = false;
        }
    } catch (...) {
        testValidity = false;
    }
    return testValidity;
}

bool Vector_scal() {

    mpjd::LinearAlgebra<double> la;
    std::shared_ptr<mpjd::LinearAlgebra<double>::Vector>
    x      = la.newVector(mpjd::LinearAlgebra<double>::target_arch::CPU);

    bool testValidity = true;
    try {
        std::vector<double> nums({1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0});
        for(auto i : nums){
            x->push_back(i);
        } 

        la.scal(x->size(),2.0,x->data(),1);

        for(auto i=0; i<x->size(); i++){
            if(std::abs(static_cast<double>(2.0)-(*x)[i]) > 1e-08){
                testValidity = false;
            }
        }
    } catch (...) {
        testValidity = false;
    }
    return testValidity;
}


bool Vector_geam() {

    mpjd::LinearAlgebra<double> la;
    std::shared_ptr<mpjd::LinearAlgebra<double>::Vector>
    A      = la.newVector(mpjd::LinearAlgebra<double>::target_arch::CPU);
    int ldA;

    std::shared_ptr<mpjd::LinearAlgebra<double>::Vector>
    B      = la.newVector(mpjd::LinearAlgebra<double>::target_arch::CPU);
    int ldB;
    
    std::shared_ptr<mpjd::LinearAlgebra<double>::Vector>
    C      = la.newVector(mpjd::LinearAlgebra<double>::target_arch::CPU);
    int ldC;
    

    int rows,cols;

    bool testValidity = true;
    try {
        std::vector<double> nums({1.0, 1.0, 1.0,
                                  1.0, 1.0, 1.0,
                                  1.0, 1.0, 1.0}); // this is the transposed
        rows = 3;
        cols = 3;

        ldA = rows;
        ldB = ldA;
        ldC = ldA;

        double one = 1.0;

        for(auto i : nums){
            A->push_back(i);
            B->push_back(i);
            C->push_back(0.0);
        } 

        la.geam('N', 'N', rows, cols,
            one, A->data(), ldA,
            one, B->data(), ldB,
            C->data(), ldC);

        for(auto i=0; i<C->size(); i++){
            if(std::abs(static_cast<double>(2.0)-(*C)[i]) > 1e-08){
                testValidity = false;
            }
        }
    } catch (...) {
        testValidity = false;
    }
    return testValidity;
}


bool Vector_gemm() {

    mpjd::LinearAlgebra<double> la;
    std::shared_ptr<mpjd::LinearAlgebra<double>::Vector>
    A      = la.newVector(mpjd::LinearAlgebra<double>::target_arch::CPU);
    int ldA;

    std::shared_ptr<mpjd::LinearAlgebra<double>::Vector>
    B      = la.newVector(mpjd::LinearAlgebra<double>::target_arch::CPU);
    int ldB;
    
    std::shared_ptr<mpjd::LinearAlgebra<double>::Vector>
    C      = la.newVector(mpjd::LinearAlgebra<double>::target_arch::CPU);
    int ldC;
    

    int rows,cols;

    bool testValidity = true;
    try {
        std::vector<double> Anums({1.0, 1.0, 1.0,
                                   1.0, 1.0, 1.0,
                                   1.0, 1.0, 1.0}); // this is the transposed

        std::vector<double> Bnums({1.0, 1.0, 1.0,
                                   1.0, 1.0, 1.0,
                                   1.0, 1.0, 1.0}); // this is the transposed

        rows = 3;
        cols = 3;

        ldA = rows;
        ldB = ldA;
        ldC = ldA;

        double one  = 1.0;
        double zero = 0.0;

        for(auto i : Anums){
            A->push_back(i);
        } 

        for(auto i : Bnums){
            B->push_back(i);
            C->push_back(0.0);
        } 

        la.gemm('N', 'N',
            rows, cols, cols,
            one, A->data(), ldA,
            B->data(), ldB,
            zero, C->data(), ldC);

        for(auto i=0; i<C->size(); i++){
            if(std::abs(static_cast<double>(3.0)-(*C)[i]) > 1e-08){
                testValidity = false;
            }
        }
    } catch (...) {
        testValidity = false;
    }
    return testValidity;
}



bool Vector_trsm() {

    mpjd::LinearAlgebra<double> la;
    std::shared_ptr<mpjd::LinearAlgebra<double>::Vector>
    A      = la.newVector(mpjd::LinearAlgebra<double>::target_arch::CPU);
    int ldA;

    std::shared_ptr<mpjd::LinearAlgebra<double>::Vector>
    b      = la.newVector(mpjd::LinearAlgebra<double>::target_arch::CPU);
    
    std::shared_ptr<mpjd::LinearAlgebra<double>::Vector>
    x      = la.newVector(mpjd::LinearAlgebra<double>::target_arch::CPU);

    int rows,cols;

    bool testValidity = true;
    try {
        std::vector<double> Anums({1.0, 1.0, 1.0,
                                   0.0, 1.0, 1.0,
                                   0.0, 0.0, 1.0}); // this is the transposed

        std::vector<double> xnums({1.0, 
                                   1.0, 
                                   1.0});

        rows = 3;
        cols = 3;

        ldA = rows;
        
        double one  = 1.0;
        double zero = 0.0;

        for(auto i : Anums){
            A->push_back(i);
        } 

        for(auto i : xnums){
            x->push_back(i);
            b->push_back(0.0);
        } 

        la.gemm('N', 'N',
            rows, 1, cols,
            one, A->data(), ldA,
            x->data(), cols,
            zero, b->data(), cols);


            la.trsm('C', 'L','L', 'N',
                        'N', rows, 1,
                        one, A->data(), ldA, 
                        b->data() , rows);

        for(auto i=0; i<b->size(); i++){
            if(std::abs((*x)[i]-(*b)[i]) > 1e-08){
                testValidity = false;
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
    CHECK(Vector_dot);
    CHECK(Vector_axpy);
    CHECK(Vector_nrm2);
    CHECK(Vector_scal);
    CHECK(Vector_geam);
    CHECK(Vector_gemm);
    CHECK(Vector_trsm);

    return 0;
}