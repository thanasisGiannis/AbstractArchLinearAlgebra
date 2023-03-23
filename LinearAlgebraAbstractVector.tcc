template<class fp>
class mpjd::LinearAlgebra::Vector 
{
    public:
        virtual int size() = 0;
        virtual ~Vector() {}
        
        
        virtual void reserve(int numVars) = 0; 
        virtual int  capacity() = 0;
        virtual void clear() = 0;

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