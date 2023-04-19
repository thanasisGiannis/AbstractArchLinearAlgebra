#include <typeinfo>
#include <cstdlib>
#include <cstring>
#include <memory>

template<class fp>
class mpjd::LinearAlgebra::Vector 
{
    protected: 
        class IteratorImplementation;
    
    public:
        class Iterator {
            public: 
                Iterator(IteratorImplementation *iterImpl = NULL);
                ~Iterator();

                fp& operator*();
                Iterator& operator++();
                Iterator& operator=(const Iterator& otherIterImpl);
                Iterator operator++(int);
                Iterator operator--(int);
                bool operator==(const Iterator& otherIterImpl);// { return *((this->_iterImpl))==(*(otherIterImpl._iterImpl));}
                bool operator!=(const Iterator& otherIterImpl);// { return *((this->_iterImpl))!=(*(otherIterImpl._iterImpl));}
                
            private:
                IteratorImplementation* _iterImpl;
        };
        
        virtual int size() = 0;
        virtual ~Vector() = default;
        
        virtual const fp* data() = 0;
        virtual fp& operator[](int idx) = 0;
        virtual void reserve(int numVars) = 0; 
        virtual void resize(int dim) = 0; 
        virtual int  capacity() = 0;
        virtual void clear() = 0;
        virtual void push_back(fp var) = 0; 
        virtual const target_arch getArch() = 0;
        virtual void init(int val) = 0;
        
        virtual mpjd::LinearAlgebra::Vector<fp>::Iterator begin() = 0; 
        virtual mpjd::LinearAlgebra::Vector<fp>::Iterator end() = 0; 
        
        virtual mpjd::LinearAlgebra::Vector<fp>::Iterator rbegin() = 0; 
        virtual mpjd::LinearAlgebra::Vector<fp>::Iterator rend() = 0; 

    protected:
        class IteratorImplementation {
            public:
                virtual ~IteratorImplementation()=default;
                virtual fp& operator*()=0;
                virtual IteratorImplementation& operator++()=0;
                virtual bool operator==(IteratorImplementation& otherIterImpl)=0;
                virtual bool operator!=(IteratorImplementation& otherIterImpl)=0;
                virtual IteratorImplementation* clone()=0;
        };
        
        Vector() {}
};


template<class fp>
mpjd::LinearAlgebra::Vector<fp>::Iterator::
Iterator(IteratorImplementation *iterImpl)
: _iterImpl(iterImpl) {}

template<class fp>
mpjd::LinearAlgebra::Vector<fp>::Iterator::
~Iterator() {
    if(NULL != _iterImpl) delete _iterImpl;
}

template<class fp>
fp& mpjd::LinearAlgebra::Vector<fp>::Iterator::
operator*() {
    return (*(*_iterImpl));
}

template<class fp>
mpjd::LinearAlgebra::Vector<fp>::Iterator& 
mpjd::LinearAlgebra::Vector<fp>::Iterator::
operator++() {
    ++(*_iterImpl); 
    return *this;
}

template<class fp>
mpjd::LinearAlgebra::Vector<fp>::Iterator& 
mpjd::LinearAlgebra::Vector<fp>::Iterator::
operator=(const Iterator& otherIterImpl) {
    if(NULL != this->_iterImpl) {
        delete this->_iterImpl;
    }
    this->_iterImpl = (otherIterImpl._iterImpl)->clone();
    return *this;
}

template<class fp>
mpjd::LinearAlgebra::Vector<fp>::Iterator 
mpjd::LinearAlgebra::Vector<fp>::Iterator::
operator++(int) {
    IteratorImplementation* _iterImpl2 = _iterImpl->clone();
    Iterator it(_iterImpl2);
    ++(*_iterImpl); 
    return it;
}

template<class fp>
mpjd::LinearAlgebra::Vector<fp>::Iterator 
mpjd::LinearAlgebra::Vector<fp>::Iterator::
operator--(int) {
    IteratorImplementation* _iterImpl2 = _iterImpl->clone();
    Iterator it(_iterImpl2);
    --(*_iterImpl); 
    return it;
}

template<class fp>
bool mpjd::LinearAlgebra::Vector<fp>::Iterator::
operator==(const Iterator& otherIterImpl) { 
    return *((this->_iterImpl))==(*(otherIterImpl._iterImpl));
}

template<class fp>
bool mpjd::LinearAlgebra::Vector<fp>::Iterator::
operator!=(const Iterator& otherIterImpl) { 
    return *((this->_iterImpl))!=(*(otherIterImpl._iterImpl));
}
