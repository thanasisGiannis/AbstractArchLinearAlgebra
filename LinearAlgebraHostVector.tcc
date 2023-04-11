#include <functional>
#include <memory>

template<class fp> 
class mpjd::LinearAlgebra::Host_Vector
: public mpjd::LinearAlgebra::Vector<fp> 
{
    public:
        mpjd::LinearAlgebra::Vector<fp>::Iterator begin() override; 
        mpjd::LinearAlgebra::Vector<fp>::Iterator end() override; 

        mpjd::LinearAlgebra::Vector<fp>::Iterator rbegin()override; 
        mpjd::LinearAlgebra::Vector<fp>::Iterator rend() override; 
               
        Host_Vector();
        ~Host_Vector();
        const fp* data() override {return _vector.data();};

        int size() override; 
        void resize(int dim);
        fp& operator[](int idx);
        void push_back(fp var);

        void reserve(int numVars); 
        int  capacity();
        void clear();
        const target_arch getArch() { return _vec_arch;}
        void init(int val);

    private: 
        class IteratorImplementationConcrete : public mpjd::LinearAlgebra::Vector<fp>::IteratorImplementation {
            public:
                enum type_iterator {
                    forward,
                    reverse
                };
                IteratorImplementationConcrete(Host_Vector* v = nullptr, int idx = 0, type_iterator type_iter = forward);
                ~IteratorImplementationConcrete(); 
                
                IteratorImplementationConcrete* clone();
                fp& operator*();
                IteratorImplementationConcrete& operator++();
                bool operator==(mpjd::LinearAlgebra::Vector<fp>::IteratorImplementation& otherIterImpl);
                bool operator!=(mpjd::LinearAlgebra::Vector<fp>::IteratorImplementation& otherIterImpl);
            private:
                const type_iterator _type_iter;
                int _idx;
                int _max_idx();
                Host_Vector<fp>* _v;
        };

        std::vector<fp> _vector;
        const target_arch _vec_arch = target_arch::CPU;
};

template<class fp>
int mpjd::LinearAlgebra::Host_Vector<fp>::IteratorImplementationConcrete::_max_idx()
{ 
  return _v->size()-1;
}
template<class fp>
mpjd::LinearAlgebra::Host_Vector<fp>::IteratorImplementationConcrete::IteratorImplementationConcrete(Host_Vector* v, int idx, type_iterator type_iter)
: _v(v), 
  _idx(idx),
  _type_iter(type_iter) {
    //std::cout << "new IteratorConcrete "<< this << std::endl;
}
template<class fp>
mpjd::LinearAlgebra::Host_Vector<fp>::IteratorImplementationConcrete::~IteratorImplementationConcrete(){
    //std::cout << "Del IteratorConcrete "<< this << std::endl;
}

template<class fp>
fp& mpjd::LinearAlgebra::Host_Vector<fp>::IteratorImplementationConcrete::operator*() {
    if(0 <= _idx && _idx <= _max_idx()) {
        fp& num = this->_v->_vector[_idx];
        return num;
    } else {
        std::cout << "Error DEREFENCE nullptr" << std::endl;
        exit(-1);
    }
}

template<class fp>
bool mpjd::LinearAlgebra::Host_Vector<fp>::IteratorImplementationConcrete::
operator==(mpjd::LinearAlgebra::Vector<fp>::IteratorImplementation& otherIterImpl) {
    auto* it = (IteratorImplementationConcrete*)(&otherIterImpl);
    return (((*this)._v == (*it)._v) && ((*this)._idx == (*it)._idx)  && ((*this)._type_iter == (*it)._type_iter));
}

template<class fp>
bool mpjd::LinearAlgebra::Host_Vector<fp>::IteratorImplementationConcrete::
operator!=(mpjd::LinearAlgebra::Vector<fp>::IteratorImplementation& otherIterImpl) {
    auto* it = (IteratorImplementationConcrete*)(&otherIterImpl);
    return (((*this)._v != (*it)._v) || ((*this)._idx != (*it)._idx) ||((*this)._type_iter != (*it)._type_iter));
}

template<class fp>
mpjd::LinearAlgebra::Host_Vector<fp>::IteratorImplementationConcrete& 
mpjd::LinearAlgebra::Host_Vector<fp>::IteratorImplementationConcrete::operator++() {
    if(type_iterator::forward == this->_type_iter){
        ++_idx; 
    } else {
        --_idx;
    } 
    if(_idx > _max_idx()) _idx = _max_idx()+1;
    if(_idx < 0) _idx = -1;
    return *this;
}
/*
template<class fp>
mpjd::LinearAlgebra::Host_Vector<fp>::IteratorImplementationConcrete& 
mpjd::LinearAlgebra::Host_Vector<fp>::IteratorImplementationConcrete::operator--() {
    if(type_iterator::forward == this->_type_iter){
        --_idx; 
    } else {
        ++_idx;
    }
    if(_idx > _max_idx()) _idx = _max_idx()+1;
    if(_idx < 0) _idx = -1;
    return *this;
}
*/
template<class fp>
mpjd::LinearAlgebra::Host_Vector<fp>::IteratorImplementationConcrete* 
mpjd::LinearAlgebra::Host_Vector<fp>::IteratorImplementationConcrete::clone() {
    mpjd::LinearAlgebra::Host_Vector<fp>::IteratorImplementationConcrete* newit = new IteratorImplementationConcrete(this->_v,this->_idx,this->_type_iter);
    return newit; 
}

template<class fp>
mpjd::LinearAlgebra::Vector<fp>::Iterator
mpjd::LinearAlgebra::Host_Vector<fp>::begin() {
    mpjd::LinearAlgebra::Host_Vector<fp>::IteratorImplementationConcrete 
    *it = new mpjd::LinearAlgebra::Host_Vector<fp>::IteratorImplementationConcrete(this,0,mpjd::LinearAlgebra::Host_Vector<fp>::IteratorImplementationConcrete::type_iterator::forward);
    return  (typename mpjd::LinearAlgebra::Vector<fp>::Iterator(it));
} 


template<class fp>
mpjd::LinearAlgebra::Vector<fp>::Iterator
mpjd::LinearAlgebra::Host_Vector<fp>::end() {
    mpjd::LinearAlgebra::Host_Vector<fp>::IteratorImplementationConcrete 
    *it = new mpjd::LinearAlgebra::Host_Vector<fp>::IteratorImplementationConcrete(this,this->size(),mpjd::LinearAlgebra::Host_Vector<fp>::IteratorImplementationConcrete::type_iterator::forward);
    return  (typename mpjd::LinearAlgebra::Vector<fp>::Iterator(it));
} 

template<class fp>
mpjd::LinearAlgebra::Vector<fp>::Iterator
mpjd::LinearAlgebra::Host_Vector<fp>::rbegin() {
    mpjd::LinearAlgebra::Host_Vector<fp>::IteratorImplementationConcrete 
    *it = new mpjd::LinearAlgebra::Host_Vector<fp>::IteratorImplementationConcrete(this,this->size()-1,mpjd::LinearAlgebra::Host_Vector<fp>::IteratorImplementationConcrete::type_iterator::reverse);
    return  (typename mpjd::LinearAlgebra::Vector<fp>::Iterator(it));
} 

template<class fp>
mpjd::LinearAlgebra::Vector<fp>::Iterator
mpjd::LinearAlgebra::Host_Vector<fp>::rend() {
    mpjd::LinearAlgebra::Host_Vector<fp>::IteratorImplementationConcrete 
    *it = new mpjd::LinearAlgebra::Host_Vector<fp>::IteratorImplementationConcrete(this,-1,mpjd::LinearAlgebra::Host_Vector<fp>::IteratorImplementationConcrete::type_iterator::reverse);
    return  (typename mpjd::LinearAlgebra::Vector<fp>::Iterator(it));
} 

template<class fp>
void mpjd::LinearAlgebra::Host_Vector<fp>::init(int val) {
    std::fill(this->_vector.begin(),this->_vector.end(), static_cast<fp>(0.0));
}

template<class fp>
mpjd::LinearAlgebra::Host_Vector<fp>::Host_Vector() {
    //std::cout << "New Host_Vector" << std::endl;
}

template<class fp>
mpjd::LinearAlgebra::Host_Vector<fp>::~Host_Vector() {
    //std::cout << "Del Host_Vector" << std::endl;
}

template<class fp>
fp&  mpjd::LinearAlgebra::Host_Vector<fp>::operator[](int idx) {
    return _vector[idx];
}


template<class fp>
void mpjd::LinearAlgebra::Host_Vector<fp>::push_back(fp var) {
    _vector.push_back(var);
}

template<class fp>
int mpjd::LinearAlgebra::Host_Vector<fp>::size() {
    return _vector.size();
} 


template<class fp>
void mpjd::LinearAlgebra::Host_Vector<fp>::resize(int dim) {
    _vector.resize(dim);
}

template<class fp>
void mpjd::LinearAlgebra::Host_Vector<fp>::reserve(int numVars) {
    _vector.reserve(numVars);
}

template<class fp>
int mpjd::LinearAlgebra::Host_Vector<fp>::capacity() {
    return _vector.capacity();
}

template<class fp>
void mpjd::LinearAlgebra::Host_Vector<fp>::clear() {
    _vector.clear();
}
