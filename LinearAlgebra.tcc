
mpjd::LinearAlgebra::LinearAlgebra(target_arch arch)
    : _arch{arch}
    {}

mpjd::LinearAlgebra::~LinearAlgebra() {
    std::cout << "LinearAlgebra Architecture = "  
                << (_arch==target_arch::CPU?"CPU":"GPU")
                << std::endl;
}

template<class fp>
mpjd::LinearAlgebra::Vector<fp>&
mpjd::LinearAlgebra::newVector(const mpjd::LinearAlgebra::target_arch arch){
    
    Vector<fp> *p;
    switch(arch){
        case target_arch::CPU:
            p = new Host_Vector<fp>();
            break;
        case target_arch::GPU:
            p = new Device_Vector<fp>();
            break;
        default:
            p = NULL;
            std::cout << "Not a proper initialization"
                        << std::endl;
    }
    return *p;
}

std::ostream& operator<<(std::ostream& os,mpjd::LinearAlgebra::target_arch __arch){
    switch(__arch){
        case mpjd::LinearAlgebra::target_arch::CPU:
            os << "CPU";
            break;
        case mpjd::LinearAlgebra::target_arch::GPU:
            os << "GPU";
            break;
    }
    return os;
}