template<class fp>
class mpjd::LinearAlgebra::Vector 
{
    public:
        virtual int size() = 0;
        virtual ~Vector() {}
        
        virtual fp& operator[](int idx) = 0;
        virtual void reserve(int numVars) = 0; 
        virtual int  capacity() = 0;
        virtual void clear() = 0;
        virtual void push_back(fp var) = 0; 
        /*
        class iterator {
            public:
                virtual operator++() = 0;
                virtual begin() = 0;
        }
        */
        
        /* TODO:
        virtual insert(int sP, int numVars, fp val) = 0; // this will need an iterator
        
        virtual operator=() = 0;
        virtual assign() = 0;

        virtual push_back() = 0;
        virtual pop_back() = 0;
        */
    protected:
        Vector() {}
};