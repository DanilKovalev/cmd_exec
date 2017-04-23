#pragma once

#include "environ_map.h"

#include <string>
#include <vector>

class command
{
public:
    command(const std::string cmd, const std::vector<std::string>& arguments, const environ_map& envs = environ_map());
    command(const command&) = default;
    command(command&&) = default;

    command& operator=(const command&) = default;
    command& operator=(command&&) = default;

    ~command() = default;

    void exec();

private:
    std::string m_cmd;
    std::vector<std::string> m_arguments;
    environ_map m_envs;
};


