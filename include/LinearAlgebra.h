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
                newVector(target_arch arch);

/*
            void gemm(const char transa, const char  transb,
            const  int m, const int n, const int k, 
            const double alpha, const double* a, const int lda,
            const double* b, const int ldb,
            const double beta, double* c, const int ldc); 
*/
            fp dot(const int dim, const fp *x, const int incx,
                const fp *y, const int incy) ;
/*
            void axpy(const int dim, const double alpha, 
                const double *x, const int incx, double *y, const int incy);
            double nrm2(const int dim, const double *x, const int incx);
            void scal(const int dim, const double alpha, 
                double *x, const int incx);

            void geam(const char transa, const char transb,
                    int m, int n,
                    const double alpha, const double *A, int lda,
                    const double beta, const double *B, int ldb,
                    double *C, int ldc);
            
            void trsm(const char Layout, const char side,
                                    const char uplo, const char transa,
                                    const char diag, 
                                    const int dim, const int nrhs,
                                    const double alpha, 
                                    const double *A, const int ldA, 
                                    double *B , const int ldB);
*/                                    
        private:
            class Host_Vector;

            class Device_Vector;

            target_arch _arch;

    };
}

#include "LinearAlgebra.tcc"
#include "LinearAlgebraAbstractVector.tcc"
#include "LinearAlgebraHostVector.tcc"
//#include "LinearAlgebraDeviceVector.tcc"
#include "LinearAlgebraOperationsDouble.tcc"