#include <cstdlib>
#include <iostream>

#include "BabelServer.hpp"

int main(void)
{
    try
    {
        BabelServer babel;
        babel.run();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    system("PAUSE>NUL");
    return (0);
}
