#include <functional>
#include <memory>

template<class fp> 
class mpjd::LinearAlgebra<fp>::Host_Vector
: public mpjd::LinearAlgebra<fp>::Vector 
{
    public:
        mpjd::LinearAlgebra<fp>::Vector::Iterator begin() override; 
        mpjd::LinearAlgebra<fp>::Vector::Iterator end() override; 

        mpjd::LinearAlgebra<fp>::Vector::Iterator rbegin()override; 
        mpjd::LinearAlgebra<fp>::Vector::Iterator rend() override; 
               
        Host_Vector();
        ~Host_Vector();
        fp* data() override {return _vector.data();};

        int size() override; 
        void resize(int dim) override;
        fp& operator[](int idx) override;
        void push_back(fp var) override;

        void reserve(int numVars) override; 
        int  capacity() override;
        void clear() override;
        const target_arch getArch() override { return _vec_arch;}
        void init(int val) override;

    private: 
        class IteratorImplementationConcrete 
        : public mpjd::LinearAlgebra<fp>::Vector::IteratorImplementation {
            public:
                enum type_iterator {
                    forward,
                    reverse
                };
                IteratorImplementationConcrete(Host_Vector* v = nullptr, 
                    int idx = 0,
                    type_iterator type_iter = forward);
                    
                ~IteratorImplementationConcrete(); 
                
                IteratorImplementationConcrete* clone();
                fp& operator*();
                IteratorImplementationConcrete& operator++();
                bool operator==(mpjd::LinearAlgebra<fp>::Vector
                                    ::IteratorImplementation& otherIterImpl);
                bool operator!=(mpjd::LinearAlgebra<fp>::Vector
                                    ::IteratorImplementation& otherIterImpl);
            private:
                const type_iterator _type_iter;
                int _idx;
                int _max_idx();
                Host_Vector* _v;
        };

        std::vector<fp> _vector;
        const target_arch _vec_arch = target_arch::CPU;
};

template<class fp>
int mpjd::LinearAlgebra<fp>::Host_Vector::IteratorImplementationConcrete::
_max_idx()
{ 
  return _v->size()-1;
}
template<class fp>
mpjd::LinearAlgebra<fp>::Host_Vector::IteratorImplementationConcrete::
IteratorImplementationConcrete(Host_Vector* v, int idx, type_iterator type_iter)
: _v(v), 
  _idx(idx),
  _type_iter(type_iter) {
    //std::cout << "new IteratorConcrete "<< this << std::endl;
}
template<class fp>
mpjd::LinearAlgebra<fp>::Host_Vector::IteratorImplementationConcrete::
~IteratorImplementationConcrete(){
    //std::cout << "Del IteratorConcrete "<< this << std::endl;
}

template<class fp>
fp& mpjd::LinearAlgebra<fp>::Host_Vector::IteratorImplementationConcrete::
operator*() {
    if(0 <= _idx && _idx <= _max_idx()) {
        fp& num = this->_v->_vector[_idx];
        return num;
    } else {
        std::cout << "Error DEREFENCE nullptr" << std::endl;
        exit(-1);
    }
}

template<class fp>
bool mpjd::LinearAlgebra<fp>::Host_Vector::IteratorImplementationConcrete::
operator==(mpjd::LinearAlgebra<fp>::Vector::
                                IteratorImplementation& otherIterImpl) {
    auto* it = (IteratorImplementationConcrete*)(&otherIterImpl);
    return (    ((*this)._v         == (*it)._v) 
             && ((*this)._idx       == (*it)._idx)  
             && ((*this)._type_iter == (*it)._type_iter)
           );
}

template<class fp>
bool mpjd::LinearAlgebra<fp>::Host_Vector::
                                IteratorImplementationConcrete::
operator!=(mpjd::LinearAlgebra<fp>::Vector::
                                IteratorImplementation& otherIterImpl) {
    auto* it = (IteratorImplementationConcrete*)(&otherIterImpl);
    return (    ((*this)._v         != (*it)._v) 
             || ((*this)._idx       != (*it)._idx) 
             || ((*this)._type_iter != (*it)._type_iter)
           );
}

template<class fp>
mpjd::LinearAlgebra<fp>::Host_Vector::IteratorImplementationConcrete& 
mpjd::LinearAlgebra<fp>::Host_Vector::IteratorImplementationConcrete::
operator++() {
    if(type_iterator::forward == this->_type_iter){
        ++_idx; 
    } else {
        --_idx;
    } 
    if(_idx > _max_idx()) _idx = _max_idx()+1;
    if(_idx < 0) _idx = -1;
    return *this;
}

template<class fp>
mpjd::LinearAlgebra<fp>::Host_Vector::IteratorImplementationConcrete* 
mpjd::LinearAlgebra<fp>::Host_Vector::IteratorImplementationConcrete::
clone() {

    mpjd::LinearAlgebra<fp>::Host_Vector::IteratorImplementationConcrete* 
    newit = new IteratorImplementationConcrete(this->_v,
                                               this->_idx,
                                               this->_type_iter
                                              );

    return newit; 
}

template<class fp>
mpjd::LinearAlgebra<fp>::Vector::Iterator
mpjd::LinearAlgebra<fp>::Host_Vector::begin() {
    mpjd::LinearAlgebra<fp>::Host_Vector::IteratorImplementationConcrete 
    *it = new mpjd::LinearAlgebra<fp>::Host_Vector::
                IteratorImplementationConcrete(this,
                                                0,
                                                mpjd::LinearAlgebra<fp>
                                                ::Host_Vector
                                                ::IteratorImplementationConcrete
                                                ::type_iterator::forward
                                               );

    return  (typename mpjd::LinearAlgebra<fp>::Vector::Iterator(it));
} 


template<class fp>
mpjd::LinearAlgebra<fp>::Vector::Iterator
mpjd::LinearAlgebra<fp>::Host_Vector::end() {
    mpjd::LinearAlgebra<fp>::Host_Vector::IteratorImplementationConcrete 
    *it = new mpjd::LinearAlgebra<fp>::Host_Vector::
                IteratorImplementationConcrete(this,
                                               this->size(),
                                               mpjd::LinearAlgebra<fp>
                                               ::Host_Vector
                                               ::IteratorImplementationConcrete
                                               ::type_iterator::forward
                                              );

    return  (typename mpjd::LinearAlgebra<fp>::Vector::Iterator(it));
} 

template<class fp>
mpjd::LinearAlgebra<fp>::Vector::Iterator
mpjd::LinearAlgebra<fp>::Host_Vector::rbegin() {
    mpjd::LinearAlgebra<fp>::Host_Vector::IteratorImplementationConcrete 
    *it = new mpjd::LinearAlgebra<fp>::Host_Vector::
                IteratorImplementationConcrete(this,
                                               this->size()-1,
                                               mpjd::LinearAlgebra<fp>
                                               ::Host_Vector
                                               ::IteratorImplementationConcrete
                                               ::type_iterator::reverse);
                                               
    return  (typename mpjd::LinearAlgebra<fp>::Vector::Iterator(it));
} 

template<class fp>
mpjd::LinearAlgebra<fp>::Vector::Iterator
mpjd::LinearAlgebra<fp>::Host_Vector::rend() {
    mpjd::LinearAlgebra<fp>::Host_Vector::IteratorImplementationConcrete 
    *it = new mpjd::LinearAlgebra<fp>::Host_Vector::
                IteratorImplementationConcrete(this,
                                               -1,
                                               mpjd::LinearAlgebra<fp>
                                               ::Host_Vector
                                               ::IteratorImplementationConcrete
                                               ::type_iterator::reverse
                                              );
                                              
    return  (typename mpjd::LinearAlgebra<fp>::Vector::Iterator(it));
} 

template<class fp>
void mpjd::LinearAlgebra<fp>::Host_Vector::init(int val) {
    std::fill(this->_vector.begin(),this->_vector.end(), static_cast<fp>(0.0));
}

template<class fp>
mpjd::LinearAlgebra<fp>::Host_Vector::Host_Vector() {
    //std::cout << "New Host_Vector" << std::endl;
}

template<class fp>
mpjd::LinearAlgebra<fp>::Host_Vector::~Host_Vector() {
    //std::cout << "Del Host_Vector" << std::endl;
}

template<class fp>
fp&  mpjd::LinearAlgebra<fp>::Host_Vector::operator[](int idx) {
    return _vector[idx];
}


template<class fp>
void mpjd::LinearAlgebra<fp>::Host_Vector::push_back(fp var) {
    _vector.push_back(var);
}

template<class fp>
int mpjd::LinearAlgebra<fp>::Host_Vector::size() {
    return _vector.size();
} 


template<class fp>
void mpjd::LinearAlgebra<fp>::Host_Vector::resize(int dim) {
    _vector.resize(dim);
}

template<class fp>
void mpjd::LinearAlgebra<fp>::Host_Vector::reserve(int numVars) {
    _vector.reserve(numVars);
}

template<class fp>
int mpjd::LinearAlgebra<fp>::Host_Vector::capacity() {
    return _vector.capacity();
}

template<class fp>
void mpjd::LinearAlgebra<fp>::Host_Vector::clear() {
    _vector.clear();
}
