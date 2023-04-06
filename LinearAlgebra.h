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
            class Vector;

            template<class fp>
            std::unique_ptr<Vector<fp>> newVector(target_arch arch);

        private:
            template<class fp> 
            class Host_Vector;

            template<class fp> 
            class Device_Vector;

            target_arch _arch;

    };
}

#include "LinearAlgebra.tcc"
#include "LinearAlgebraAbstractVector.tcc"
#include "LinearAlgebraHostVector.tcc"
#include "LinearAlgebraDeviceVector.tcc"