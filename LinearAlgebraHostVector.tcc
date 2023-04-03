#include <functional>

template<class fp> 
class mpjd::LinearAlgebra::Host_Vector
: public mpjd::LinearAlgebra::Vector<fp> 
{
    public:
        virtual mpjd::LinearAlgebra::Vector<fp>::Iterator begin() override; 
        virtual mpjd::LinearAlgebra::Vector<fp>::Iterator end() override; 
               
        int size() override; 
        Host_Vector();
        ~Host_Vector();
        fp& operator[](int idx);
        void push_back(fp var);

        void reserve(int numVars); 
        int  capacity();
        void clear();
        
    private:
        class Iterator : public mpjd::LinearAlgebra::Vector<fp>::IteratorImplementationBase {
            public:
                Iterator(Host_Vector* v = nullptr, unsigned int idx = 0);
                Iterator* clone();
                fp& operator*();
                //Iterator& operator=(mpjd::LinearAlgebra::Vector<fp>::IteratorImplementationBase& otherIterImpl);
                Iterator& operator++();
                Iterator& operator--();
                bool operator==(mpjd::LinearAlgebra::Vector<fp>::IteratorImplementationBase& otherIterImpl);
                bool operator!=(mpjd::LinearAlgebra::Vector<fp>::IteratorImplementationBase& otherIterImpl);
            private:
                unsigned int _idx;
                unsigned int _max_idx();
                Host_Vector<fp>* _v;
        };

        std::vector<fp> _vector;
        const target_arch _vec_arch = target_arch::CPU;
};

template<class fp>
unsigned int mpjd::LinearAlgebra::Host_Vector<fp>::Iterator::_max_idx()
{
  
  return _v->size();
}
template<class fp>
mpjd::LinearAlgebra::Host_Vector<fp>::Iterator::Iterator(Host_Vector* v, unsigned int idx)
: _v(v), 
  _idx(idx) {

}
template<class fp>
fp& mpjd::LinearAlgebra::Host_Vector<fp>::Iterator::operator*() {
    if(_idx <= _max_idx()) {
        fp& num = this->_v->_vector[_idx];
        return num;
    } else {
        std::cout << "Error DEREFENCE nullptr" << std::endl;
        exit(-1);
    }
}

template<class fp>
bool mpjd::LinearAlgebra::Host_Vector<fp>::Iterator::
operator==(mpjd::LinearAlgebra::Vector<fp>::IteratorImplementationBase& otherIterImpl) {
    auto it = dynamic_cast<Iterator*>(&otherIterImpl);
    return (((*this)._v == (*it)._v) && ((*this)._idx == (*it)._idx));
}

template<class fp>
bool mpjd::LinearAlgebra::Host_Vector<fp>::Iterator::
operator!=(mpjd::LinearAlgebra::Vector<fp>::IteratorImplementationBase& otherIterImpl) {
    auto it = dynamic_cast<Iterator*>(&otherIterImpl);
    return !(((*this)._v == (*it)._v) && ((*this)._idx == (*it)._idx));
}

template<class fp>
mpjd::LinearAlgebra::Host_Vector<fp>::Iterator& 
mpjd::LinearAlgebra::Host_Vector<fp>::Iterator::operator++() {
    ++_idx; 
    if(_idx > _max_idx()+1) _idx = _max_idx()+1;
    return *this;
}

template<class fp>
mpjd::LinearAlgebra::Host_Vector<fp>::Iterator* 
mpjd::LinearAlgebra::Host_Vector<fp>::Iterator::clone() {
    mpjd::LinearAlgebra::Host_Vector<fp>::Iterator* newit = new Iterator(this->_v,this->_idx);
    return newit; 
}

template<class fp>
mpjd::LinearAlgebra::Host_Vector<fp>::Iterator& 
mpjd::LinearAlgebra::Host_Vector<fp>::Iterator::operator--() {
    --_idx; 
    if(_idx < 0) _idx = 0;
    return *this;
}

template<class fp>
mpjd::LinearAlgebra::Vector<fp>::Iterator
mpjd::LinearAlgebra::Host_Vector<fp>::begin() {
    mpjd::LinearAlgebra::Host_Vector<fp>::Iterator 
    *it = new mpjd::LinearAlgebra::Host_Vector<fp>::Iterator(this,0);
    return  (typename mpjd::LinearAlgebra::Vector<fp>::Iterator(*it));
} 

template<class fp>
mpjd::LinearAlgebra::Vector<fp>::Iterator
mpjd::LinearAlgebra::Host_Vector<fp>::end() {
    mpjd::LinearAlgebra::Host_Vector<fp>::Iterator 
    *it = new mpjd::LinearAlgebra::Host_Vector<fp>::Iterator(this,_vector.size()+1);
    return  (typename mpjd::LinearAlgebra::Vector<fp>::Iterator(*it));
} 


template<class fp>
mpjd::LinearAlgebra::Host_Vector<fp>::Host_Vector() {
}

template<class fp>
mpjd::LinearAlgebra::Host_Vector<fp>::~Host_Vector() {
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
