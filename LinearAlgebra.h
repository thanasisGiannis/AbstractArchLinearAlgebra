#pragma once 

#include <vector>
#include <memory>
#include <iostream>

namespace mpjd {

    class LinearAlgebra 
    {
        public:
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
            std::unique_ptr<Vector<fp>> newVector(){
                std::unique_ptr<Device_Vector<fp>> 
                    p(std::unique_ptr<Device_Vector<fp>>(
                        new Device_Vector<fp>())
                    );
                    
                return std::move(p);
            }

        private:
            template<class fp> 
            class Device_Vector
            : public Vector<fp> 
            {
                public:
                    int size() override { return _vector.size();} 
                    Device_Vector() {std::cout << "Device_Vector()" << std::endl;}
                    ~Device_Vector() {std::cout << "~Device_Vector()" << std::endl;}
                private:
                    std::vector<fp> _vector;
            };

    };
}