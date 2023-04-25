#pragma once 

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
            const fp beta, fp* c, const int ldc); 

            fp dot(const int dim, const fp *x, const int incx,
                const fp *y, const int incy) ;
            void axpy(const int dim, const fp alpha, 
                const fp *x, const int incx, fp *y, const int incy);
            fp nrm2(const int dim, const fp *x, const int incx);
            void scal(const int dim, const fp alpha, 
                fp *x, const int incx);

            void geam(const char transa, const char transb,
                    int m, int n,
                    const fp alpha, const fp *A, int lda,
                    const fp beta, const fp *B, int ldb,
                    fp *C, int ldc);
            
            void trsm(const char Layout, const char side,
                                    const char uplo, const char transa,
                                    const char diag, 
                                    const int dim, const int nrhs,
                                    const fp alpha, 
                                    const fp *A, const int ldA, 
                                    fp *B , const int ldB);
        private:
            class Host_Vector;

            class Device_Vector;

            target_arch _arch;

            // abstract class that should have the interface for blas operations
            // implementations of this should use polymorphism and eventually
            // use wrappers around the calling external BLAS functions
            // class Operations; this will be the true blas wrappers depenting on cpu or gpu processing unit
            // Operations *op; // object to be used to delegate to proper BLAS operations

    };
}

#include "LinearAlgebra.tcc"
#include "LinearAlgebraAbstractVector.tcc"
#include "LinearAlgebraHostVector.tcc"
//#include "LinearAlgebraDeviceVector.tcc"
#include "LinearAlgebraOperationsDouble.tcc"