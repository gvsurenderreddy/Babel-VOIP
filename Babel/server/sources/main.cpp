#include <cstdlib>
#include <iostream>

#include "BabelServer.hpp"
#include "HandleCmd.hpp"

int	testCmd(void){
	TcpClient socket;
	HandleCmd cmd(socket);
	std::vector<std::string> *t;
	socket.receive(2000);

	t = cmd.unPackCmd();
	if (t != NULL){
		std::cout << "taille tableau " << t->size() << std::endl;
		//std::cout << cmd.getInstruction() << std::endl;
		std::cout << (*t)[0] << std::endl;
		std::cout << (*t)[1] << std::endl;
		std::cout << (*t)[2] << std::endl;
		std::cout << (*t)[3] << std::endl;
		std::cout << cmd.getInstruction() << std::endl;
	}
	system("pause");
	return (0);
}

int main(void)
{
	return (testCmd());
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
