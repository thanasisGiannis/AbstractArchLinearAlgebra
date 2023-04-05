#include <typeinfo>
#include <cstdlib>
#include <cstring>

template<class fp>
class mpjd::LinearAlgebra::Vector 
{
    protected: 
        class IteratorImplementation;
    
    public:
        class Iterator {
            public: // TODO: insert pointer at the Iterator constructor
                Iterator(IteratorImplementation &iterImpl)
                : _iterImpl(iterImpl){}

                fp& operator*(){return (*_iterImpl);}
                Iterator& operator++(){++_iterImpl; return *this;};
                Iterator& operator--(){--_iterImpl; return *this;};

                Iterator operator++(int) {
                    IteratorImplementation* _iterImpl2 = _iterImpl.clone();
                    Iterator it(*_iterImpl2);
                    ++(_iterImpl); 
                    return it;
                }

                Iterator operator--(int) {
                    IteratorImplementation* _iterImpl2 = _iterImpl.clone();
                    Iterator it(*_iterImpl2);
                    --(_iterImpl); 
                    return it;
                }

                bool operator==(Iterator& otherIterImpl) { return (*this)._iterImpl==otherIterImpl._iterImpl;}
                bool operator!=(Iterator& otherIterImpl) { return (*this)._iterImpl!=otherIterImpl._iterImpl;}
            private:
                IteratorImplementation& _iterImpl;// TODO: change to pointer
        };
        
        virtual int size() = 0;
        virtual ~Vector() {}
        
        virtual fp& operator[](int idx) = 0;
        virtual void reserve(int numVars) = 0; 
        virtual int  capacity() = 0;
        virtual void clear() = 0;
        virtual void push_back(fp var) = 0; 
        virtual mpjd::LinearAlgebra::Vector<fp>::Iterator begin() = 0; 
        virtual mpjd::LinearAlgebra::Vector<fp>::Iterator end() = 0; 
        

    protected:
        class IteratorImplementation {
            public:
                virtual fp& operator*()=0;
                virtual IteratorImplementation& operator++()=0;
                virtual IteratorImplementation& operator--()=0;
                virtual bool operator==(IteratorImplementation& otherIterImpl)=0;
                virtual bool operator!=(IteratorImplementation& otherIterImpl)=0;
                virtual IteratorImplementation* clone()=0;
        };
        
        Vector() {}
};