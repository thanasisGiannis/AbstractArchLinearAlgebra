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
                Iterator(IteratorImplementation *iterImpl = NULL)
                : _iterImpl(iterImpl) { 
                    //std::cout << "New Iterator " << this << std::endl;
                }
                ~Iterator() {
                    //std::cout << "Del Iterator " << this << std::endl; 
                    if(NULL != _iterImpl) delete _iterImpl;
                }

                fp& operator*() {return (*(*_iterImpl));}
                Iterator& operator++() {++(*_iterImpl); return *this;};
                Iterator& operator--() {--(*_iterImpl); return *this;};
                
                Iterator& operator=(const Iterator& otherIterImpl) {
                    if(NULL != this->_iterImpl) {
                        delete this->_iterImpl;
                    }
                    this->_iterImpl = (otherIterImpl._iterImpl)->clone();
                    return *this;
                }
                
                Iterator operator++(int) {
                    IteratorImplementation* _iterImpl2 = _iterImpl->clone();
                    Iterator it(_iterImpl2);
                    ++(*_iterImpl); 
                    return it;
                }

                Iterator operator--(int) {
                    IteratorImplementation* _iterImpl2 = _iterImpl->clone();
                    Iterator it(_iterImpl2);
                    --(*_iterImpl); 
                    return it;
                }

                bool operator==(const Iterator& otherIterImpl) { return *((this->_iterImpl))==(*(otherIterImpl._iterImpl));}
                bool operator!=(const Iterator& otherIterImpl) { return *((this->_iterImpl))!=(*(otherIterImpl._iterImpl));}
                
            private:
                IteratorImplementation* _iterImpl;
        };
        
        virtual int size() = 0;
        virtual ~Vector() = default;
        
        virtual const fp* data() = 0;
        virtual fp& operator[](int idx) = 0;
        virtual void reserve(int numVars) = 0; 
        virtual int  capacity() = 0;
        virtual void clear() = 0;
        virtual void push_back(fp var) = 0; 
        virtual const target_arch getArch() = 0;

        virtual mpjd::LinearAlgebra::Vector<fp>::Iterator begin() = 0; 
        virtual mpjd::LinearAlgebra::Vector<fp>::Iterator end() = 0; 
        
        //virtual mpjd::LinearAlgebra::Vector<fp>::Iterator rbegin() = 0; 
        //virtual mpjd::LinearAlgebra::Vector<fp>::Iterator rend() = 0; 
        
        //virtual Vector& operator=(Vector& otherV)=0;

    protected:
        class IteratorImplementation {
            public:
                virtual ~IteratorImplementation()=default;
                virtual fp& operator*()=0;
                virtual IteratorImplementation& operator++()=0;
                virtual IteratorImplementation& operator--()=0;
                virtual bool operator==(IteratorImplementation& otherIterImpl)=0;
                virtual bool operator!=(IteratorImplementation& otherIterImpl)=0;
                virtual IteratorImplementation* clone()=0;
        };
        
        Vector() {}
};