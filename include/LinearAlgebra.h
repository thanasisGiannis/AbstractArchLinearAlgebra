#pragma once 

#include <vector>
#include <memory>
#include <iostream>

namespace mpjd {

    template<class fp>
    class LinearAlgebra 
    {
        public:
            enum target_arch {
                CPU,
                GPU
            };
            
            LinearAlgebra(target_arch arch = target_arch::CPU);

            ~LinearAlgebra();

            //template<class fp>
            class Vector;

            //template<class fp>
            //class BlockVector; // TODO

            //template<class fp>
            //class DenseMatrix; // TODO

            
            std::unique_ptr<Vector> 
                newVector(target_arch arch);

            //template<class fp>
            //std::unique_ptr<Vector<fp>> newBlockVector(target_arch arch); // TODO

            //template<class fp>
            //std::unique_ptr<Vector<fp>> newDenseMatrix(target_arch arch); // TODO

            //template<class fp>
            //class Operations;
        private:
            class Host_Vector;

            class Device_Vector;

            target_arch _arch;

    };
}

#include "LinearAlgebra.tcc"
#include "LinearAlgebraAbstractVector.tcc"
#include "LinearAlgebraHostVector.tcc"
//#include "LinearAlgebraDeviceVector.tcc"