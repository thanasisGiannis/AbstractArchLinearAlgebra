
template<class fp> 
class mpjd::LinearAlgebra::Host_Vector
: public mpjd::LinearAlgebra::Vector<fp> 
{
    public:
        int size() override; 
        Host_Vector();
        ~Host_Vector();
        void reserve(int numVars); 
        int  capacity();
        void clear();
    private:
        std::vector<fp> _vector;
        const target_arch _vec_arch = target_arch::CPU;
};

template<class fp>
mpjd::LinearAlgebra::Host_Vector<fp>::Host_Vector() {
    std::cout << "Host_Vector()" << std::endl;
}

template<class fp>
mpjd::LinearAlgebra::Host_Vector<fp>::~Host_Vector() {
    std::cout << "~Host_Vector() : " 
              << "Arch: " << _vec_arch
              << std::endl;
}

template<class fp>
int mpjd::LinearAlgebra::Host_Vector<fp>::size() {
    return _vector.size();
} 

template<class fp>
void mpjd::LinearAlgebra::Host_Vector<fp>::reserve(int numVars){
    _vector.reserve(numVars);
}

template<class fp>
int mpjd::LinearAlgebra::Host_Vector<fp>::capacity(){
    return _vector.capacity();
}

template<class fp>
void mpjd::LinearAlgebra::Host_Vector<fp>::clear(){
    _vector.clear();
}
