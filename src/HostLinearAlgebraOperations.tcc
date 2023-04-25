#include "LinearAlgebraOperations.h"

#include <iostream>
#include <vector>

#include <mkl.h>
#include <mkl_trans.h>
#include <omp.h>

namespace mpjd {
    template <class fp> 
    class HostOperations : public mpjd::Operations<fp> {
        public:
            fp dot(const int dim, const fp *x, const int incx,
                    const fp *y, const int incy) override;

            void gemm(const char transa, const char  transb,
                    const  int m, const int n, const int k, 
                    const fp alpha, const fp* a, const int lda,
                    const fp* b, const int ldb,
                    const fp beta, fp* c, const int ldc) override; 

            void axpy(const int dim, const fp alpha, 
                    const fp *x, const int incx, fp *y, const int incy) override;
                
            fp nrm2(const int dim, const fp *x, const int incx) override;

            void scal(const int dim, const fp alpha, 
                fp *x, const int incx) override;

            void geam(const char transa, const char transb,
                    int m, int n,
                    const fp alpha, const fp *A, int lda,
                    const fp beta, const fp *B, int ldb,
                    fp *C, int ldc) override;
            
            void trsm(const char Layout, const char side,
                    const char uplo, const char transa,
                    const char diag, 
                    const int dim, const int nrhs,
                    const fp alpha, 
                    const fp *A, const int ldA, 
                    fp *B , const int ldB) override;                    

    };
}

template <>
void mpjd::HostOperations<double>::gemm(const char transa, const char  transb,
    const  int m, const int n, const int k, 
    const double alpha, const double* a, const int lda,
    const double* b, const int ldb,
    const double beta, double* c, const int ldc) {
    
	CBLAS_TRANSPOSE ta;										
	switch (transa) {
		case 'T':
			ta = CblasTrans;
			break;
		case 'N':
			ta = CblasNoTrans;
			break;
		default:
			exit(-1);
	}

	CBLAS_TRANSPOSE tb;										
	switch (transb) {
		case 'T':
			tb = CblasTrans;
			break;
		case 'N':
			tb = CblasNoTrans;
			break;
		default:
			exit(-1); // error
	}

	MKL_INT mm = static_cast<MKL_INT>(m);
	MKL_INT nn = static_cast<MKL_INT>(n);
	MKL_INT kk = static_cast<MKL_INT>(k);

	cblas_dgemm(CblasColMajor, ta, tb, mm, nn, kk, alpha, a, lda, 
	    b, ldb, beta, c, ldc);
}


template <>
double mpjd::HostOperations<double>::dot(const int dim, const double *x, const int incx, 
    const double *y, const int incy) {
    
	return cblas_ddot(dim, x, incx, y, incy);
}

template <>
void mpjd::HostOperations<double>::axpy(const int dim, const double alpha, 
    const double *x, int incx, double *y, const int incy) {
    
		cblas_daxpy(dim, alpha, x, incx, y, incy);
}

template <>
double mpjd::HostOperations<double>::nrm2(const int dim, const double *x, const int incx) {

	//return cblas_dnrm2(dim, x, incx);
	MKL_INT dim_  = static_cast<MKL_INT>(dim);
	MKL_INT incx_ = static_cast<MKL_INT>(incx);
	return cblas_dnrm2(dim_, x, incx_);
}

template <>
void mpjd::HostOperations<double>::scal(const int dim, const double alpha, 
    double *x, const int incx) {

	cblas_dscal(dim, alpha, x, incx);
}

template <>
void mpjd::HostOperations<double>::geam(const char transa, const char transb,
              int m, int n,
              const double alpha, const double *A, int lda,
              const double beta, const double *B, int ldb,
              double *C, int ldc) {
	
	MKL_INT mm = static_cast<MKL_INT>(m);
	MKL_INT nn = static_cast<MKL_INT>(n);
	
	mkl_domatadd('c', transa, transb, mm, nn, alpha, A, lda, beta, B, ldb, C, ldc);
              
}

template <>
void mpjd::HostOperations<double>::trsm(const char Layout, const char side,
                               const char uplo, const char transa,
                               const char diag, 
                               const int dim, const int nrhs,
                               const double alpha, 
                               const double *A, const int ldA, 
                               double *B , const int ldB ) {

  CBLAS_LAYOUT cblas_Layout;
  CBLAS_SIDE cblas_side;
  CBLAS_UPLO cblas_uplo;
  CBLAS_TRANSPOSE cblas_transa;
  CBLAS_DIAG cblas_diag;

	switch (Layout) {
		case 'C':
			cblas_Layout = CblasColMajor;
			break;
		case 'R':
			cblas_Layout = CblasRowMajor;
			break;
		default:
			exit(-1); // error
	}


	switch (side) {
		case 'L':
			cblas_side = CblasLeft;
			break;
		case 'R':
			cblas_side = CblasRight;
			break;
		default:
			exit(-1); // error
	}


	switch (uplo) {
		case 'U':
			cblas_uplo = CblasUpper;
			break;
		case 'L':
			cblas_uplo = CblasLower;
			break;
		default:
			exit(-1); // error
	}

	switch (transa) {
		case 'N':
			cblas_transa = CblasNoTrans;
			break;
		case 'T':
			cblas_transa = CblasTrans;
			break;
		default:
			exit(-1); // error
	}

	switch (diag) {
		case 'N':
			cblas_diag = CblasNonUnit;
			break;
		case 'U':
			cblas_diag = CblasUnit;
			break;
		default:
			exit(-1); // error
	}

  
  MKL_INT mkl_dim  = static_cast<MKL_INT>(dim);
  MKL_INT mkl_nrhs = static_cast<MKL_INT>(nrhs);
  MKL_INT mkl_ldA  = static_cast<MKL_INT>(ldA);
  MKL_INT mkl_ldB  = static_cast<MKL_INT>(ldB);
  
  cblas_dtrsm(cblas_Layout, cblas_side, cblas_uplo, cblas_transa, cblas_diag,
              mkl_dim, mkl_nrhs, alpha, A, mkl_ldA, B, mkl_ldB);  

} 
