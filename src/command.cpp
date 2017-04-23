#include "command.h"

#include <memory>

#include <unistd.h>
#include <cstring>
#include <iostream>

namespace
{
    void argv_deleter(char** argv)
    {
        if(!argv)
            return;

        for(size_t i = 0 ; argv[i] != nullptr; ++i)
            ::free(argv[i]);

        delete[] argv;
    }

    std::shared_ptr<char*> to_argv(const std::string& cmd ,const std::vector<std::string>& vec)
    {
        char **argv = new char*[vec.size() + 2];
        argv[0] = ::strdup(cmd.c_str());
        for(size_t i = 0 ; i < vec.size(); ++i)
            argv[i+1] = ::strdup(vec[i].c_str());

        argv[vec.size()+1] = nullptr;

        return std::shared_ptr<char*>(argv, argv_deleter);
    }
}

command::command(const std::string cmd, const std::vector<std::string> &arguments, const environ_map &envs)
: m_cmd(cmd), m_arguments(arguments), m_envs(envs)
{}

void command::exec()
{
    int res = ::execve(m_cmd.c_str(), to_argv(m_cmd , m_arguments).get(), m_envs.raw());
    std::cout << "res: " << res << " errno: " << errno << " str: " << strerror(errno) << std::endl;
}

