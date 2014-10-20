#include <cstdlib>
#include <iostream>

#include "BoostTcpServer.hpp"
#include "ServerManager.hpp"

int main(void)
{
    try
    {
        ServerManager server(new BoostTcpServer());
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    system("PAUSE>NUL");
    return (0);
}
