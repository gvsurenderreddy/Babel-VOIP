#include <iostream>

#include "BabelServer.hpp"

int main(void)
{
    int ret;
    try
    {
        BabelServer babel;
        babel.startServer();
        ret = 0;
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        ret = -1;
    }
    // do { std::cout << std::endl << "Press the Enter key to exit."; } while (std::cin.get() != '\n');
    return (ret);
}
