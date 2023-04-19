
#include <memory>

template <class fp>
mpjd::LinearAlgebra<fp>::LinearAlgebra(target_arch arch)
    : _arch{arch}
    {}

template <class fp>
mpjd::LinearAlgebra<fp>::~LinearAlgebra() {
    /*
    std::cout << "LinearAlgebra Architecture = "  
                << (_arch==target_arch::CPU?"CPU":"GPU")
                << std::endl;
    */
}

template<class fp>
std::unique_ptr<typename mpjd::LinearAlgebra<fp>::Vector>
mpjd::LinearAlgebra<fp>::newVector(const mpjd::LinearAlgebra<fp>::target_arch arch){
    std::unique_ptr<Vector> p;
    switch(arch){
        case target_arch::CPU:
            p = std::unique_ptr<Host_Vector>(new Host_Vector());
            break;
        case target_arch::GPU:
            p = std::unique_ptr<Host_Vector>(new Host_Vector()); // should be Device_Vector
            break;
        default:
            p = NULL;
            std::cout << "Not a proper initialization"
                        << std::endl;
    }
    return std::move(p);
}

template <class fp>
std::ostream& operator<<(std::ostream& os, const typename mpjd::LinearAlgebra<fp>::target_arch __arch){
    switch(__arch){
        case mpjd::LinearAlgebra<fp>::target_arch::CPU:
            os << "CPU";
            break;
        case mpjd::LinearAlgebra<fp>::target_arch::GPU:
            os << "GPU";
            break;
    }
    return os;
}