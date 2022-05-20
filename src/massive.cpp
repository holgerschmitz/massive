#include <iostream>
#include <mpi.h>
#include <hdf5.h>

int main()
{
    std::cout << "Hello World!" << std::endl;
#ifdef MASSIVE_1X_1V
    std::cout << "Is 1x1v!" << std::endl;
#endif    
#ifdef MASSIVE_2X_3V
    std::cout << "Is 2x3v!" << std::endl;
#endif    
    return 0;
}
