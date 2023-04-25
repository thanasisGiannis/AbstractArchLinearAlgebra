#pragma once 

#include <LinearAlgebraOperations.h>

#include <vector>
#include <memory>
#include <iostream>

namespace mpjd {

    template<class fp>
    class LinearAlgebra 
    {
        public:
            enum target_arch {
                CPU,
                GPU
            };
            
            LinearAlgebra(target_arch arch = target_arch::CPU);

            ~LinearAlgebra();

            class Vector;
            
            std::unique_ptr<Vector> 
                newVector();

            void gemm(const char transa, const char  transb,
                    const  int m, const int n, const int k, 
                    const fp alpha, const fp* a, const int lda,
                    const fp* b, const int ldb,
                    const fp beta, fp* c, const int ldc) {
                
                    return _op->gemm(transa, transb, m, n, k, 
                             alpha, a, lda, b, ldb, beta, c, ldc);
                 }; 

            fp dot(const int dim, const fp *x, const int incx,
                    const fp *y, const int incy) {
                    
                    return _op->dot(dim, x, incx, y, incy);
                }

            void axpy(const int dim, const fp alpha, 
                    const fp *x, const int incx, fp *y, const int incy) {
                    
                    return _op->axpy(dim, alpha, x, incx, y, incy);
                 }; 
                
            fp nrm2(const int dim, const fp *x, const int incx) {
                    
                    return _op->nrm2(dim, x, incx);
                 }; 

            void scal(const int dim, const fp alpha, 
                fp *x, const int incx) {
                    
                    return _op->scal(dim, alpha, x, incx);
                 }; 

            void geam(const char transa, const char transb,
                    int m, int n,
                    const fp alpha, const fp *A, int lda,
                    const fp beta, const fp *B, int ldb,
                    fp *C, int ldc) {
                    
                    return _op->geam(transa, transb, m, n,
                        alpha, A, lda, beta, B, ldb, C, ldc);
                 }; 
            
            void trsm(const char Layout, const char side,
                                    const char uplo, const char transa,
                                    const char diag, 
                                    const int dim, const int nrhs,
                                    const fp alpha, 
                                    const fp *A, const int ldA, 
                                    fp *B , const int ldB) {
                    
                    return _op->trsm(Layout, side,
                                     uplo, transa, diag, dim, nrhs, alpha, A, ldA, B, ldB);
                 }; 
        private:
            class Host_Vector;

            class Device_Vector;

            target_arch _arch;

            std::unique_ptr<Operations<fp>> _op; // object to be used to delegate to proper BLAS operations

    };
}

#include "LinearAlgebra.tcc"
#include "LinearAlgebraAbstractVector.tcc"
#include "LinearAlgebraHostVector.tcc"
//#include "LinearAlgebraDeviceVector.tcc"
//#include "LinearAlgebraOperationsDouble.tcc"