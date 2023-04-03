template<class fp>
class mpjd::LinearAlgebra::Vector 
{
    protected: 
        class IteratorImplementationBase;
    
    public:
        class Iterator {
            public:
                Iterator(IteratorImplementationBase &iterImpl)
                : _iterImpl(iterImpl){}

                fp& operator*(){return (*_iterImpl);}
                Iterator& operator++(){++_iterImpl; return *this;};
            private:
                IteratorImplementationBase& _iterImpl;
        };
        
        virtual int size() = 0;
        virtual ~Vector() {}
        
        virtual fp& operator[](int idx) = 0;
        virtual void reserve(int numVars) = 0; 
        virtual int  capacity() = 0;
        virtual void clear() = 0;
        virtual void push_back(fp var) = 0; 
        virtual mpjd::LinearAlgebra::Vector<fp>::Iterator begin() = 0; 
        
        /* TODO:
        virtual insert(int sP, int numVars, fp val) = 0; // this will need an iterator
        
        virtual operator=() = 0;
        virtual assign() = 0;

        virtual void pop_back() = 0;
        */
    protected:
        class IteratorImplementationBase {
            public:
                virtual fp& operator*()=0;
                virtual IteratorImplementationBase& operator++()=0;
        };
        
        Vector() {}
};