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

            //template<class fp>
            //class BlockVector; // TODO

            //template<class fp>
            //class DenseMatrix; // TODO

            template<class fp>
            std::unique_ptr<Vector<fp>> newVector(target_arch arch);

            //template<class fp>
            //std::unique_ptr<Vector<fp>> newBlockVector(target_arch arch); // TODO

            //template<class fp>
            //std::unique_ptr<Vector<fp>> newDenseMatrix(target_arch arch); // TODO

            //template<class fp>
            //class Operations;
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