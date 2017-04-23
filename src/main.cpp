#include <iostream>
#include "command.h"
#include "environ_map.h"


int main()
{
    environ_map m = environ_map::get_for_current_process();
    for(const auto& p: m)
    {
        std::cout << p.first << "=" << p.second << std::endl;
    }

    m.raw();

    command cmd("/bin/ls", std::vector<std::string>());
    cmd.exec();
}

