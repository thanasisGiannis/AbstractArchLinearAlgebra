template <>
double mpjd::LinearAlgebra<double>::dot(const int dim, const double *x, const int incx, 
const double *y, const int incy) {
    double acc = static_cast<double>(0.0);
    for(auto i=0; i<dim; i++){
        acc += x[i*incx]*y[i*incy];
    }
    return acc;
}