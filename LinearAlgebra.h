#pragma once 

#include <vector>
#include <memory>
#include <iostream>

namespace mpjd {

    class LinearAlgebra 
    {
        public:
            enum target_arch {
                CPU,
                GPU
            };
            
            LinearAlgebra(target_arch arch = mpjd::LinearAlgebra::target_arch::CPU);

            ~LinearAlgebra();

            template<class fp>
            class Vector 
            {
                public:
                    virtual int size() = 0;
                    virtual ~Vector() {}
                protected:
                    Vector() {}
            };

            template<class fp>
            std::unique_ptr<Vector<fp>> newVector();
            
            template<class fp>
            std::unique_ptr<Vector<fp>> newVector(const target_arch arch);
            
        private:
            template<class fp> 
            class Host_Vector;

            template<class fp> 
            class Device_Vector;

            target_arch _arch;

    };
}

#include "LinearAlgebra.tcc"
#include "LinearAlgebraHost.tcc"
#include "LinearAlgebraDevice.tcc"