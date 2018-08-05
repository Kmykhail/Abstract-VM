#include "AbstractVM.hpp"

int main(int ac, char **av)
{
    AbstractVM vm;
    try {
        vm.readCommand(ac, *(av + 1));
    }
    catch(std::exception & e){
        std::cout << e.what();
    }
    return 0;
}