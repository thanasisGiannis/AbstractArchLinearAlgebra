/*
    TODO: a) change base class to be Vector instead of Host_Vector
          b) add vector functionality that base class needs
*/

template<class fp> 
class mpjd::LinearAlgebra::Device_Vector
: public mpjd::LinearAlgebra::Host_Vector<fp> 
{
    public:
        int size() override; 
        Device_Vector();
        ~Device_Vector();
    private:
        std::vector<fp> _vector; // this should be a gpu vector
        const target_arch _vec_arch = target_arch::GPU;
};
            
template<class fp>
mpjd::LinearAlgebra::Device_Vector<fp>::Device_Vector() {
    std::cout << "Device_Vector()" << std::endl;
}

template<class fp>
mpjd::LinearAlgebra::Device_Vector<fp>::~Device_Vector() {
    std::cout << "~Device_Vector() : " 
              << "Arch: " << _vec_arch
              << std::endl;
}

template<class fp>
int mpjd::LinearAlgebra::Device_Vector<fp>::size() {
    return _vector.size();
} 