#pragma once

#include <iostream>
namespace mpjd{
    template <class fp>
    class Operations {
        public:
            virtual fp dot(const int dim, const fp *x, const int incx,
                    const fp *y, const int incy);

            virtual void gemm(const char transa, const char  transb,
                    const  int m, const int n, const int k, 
                    const fp alpha, const fp* a, const int lda,
                    const fp* b, const int ldb,
                    const fp beta, fp* c, const int ldc); 

            virtual void axpy(const int dim, const fp alpha, 
                    const fp *x, const int incx, fp *y, const int incy);
                
            virtual fp nrm2(const int dim, const fp *x, const int incx);

            virtual void scal(const int dim, const fp alpha, 
                fp *x, const int incx);

            virtual void geam(const char transa, const char transb,
                    int m, int n,
                    const fp alpha, const fp *A, int lda,
                    const fp beta, const fp *B, int ldb,
                    fp *C, int ldc);
            
            virtual void trsm(const char Layout, const char side,
                    const char uplo, const char transa,
                    const char diag, 
                    const int dim, const int nrhs,
                    const fp alpha, 
                    const fp *A, const int ldA, 
                    fp *B , const int ldB);
    };
}
