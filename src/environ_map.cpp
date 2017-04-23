#include "environ_map.h"

raw_environ_holder::raw_environ_holder(raw_environ_holder&& rhs)
: ppenv(rhs.ppenv)
{
    rhs.ppenv = nullptr;
}

raw_environ_holder& raw_environ_holder::operator=(raw_environ_holder&& rhs)
{
    destroy();
    ppenv = rhs.ppenv;
    rhs.ppenv = nullptr;
    return *this;
}

raw_environ_holder::~raw_environ_holder()
{
    destroy();
}

void raw_environ_holder::destroy()
{
    if(!ppenv)
        return;

    for(size_t i = 0 ; ppenv[i] != nullptr; ++i)
        ::free(ppenv[i]);

    delete[] ppenv;
}

raw_environ_holder environ_map::raw() const
{
    char **envs = new char*[size() + 1];
    size_t i = 0;
    for (const auto& pair: *this)
    {
        if (::asprintf(&envs[i], "%s=%s", pair.first.c_str(), pair.second.c_str()) == -1)
            std::__throw_system_error(errno);

        i++;
    }

    envs[size()] = nullptr;

    return raw_environ_holder(envs);
}

extern char **environ;

environ_map environ_map::get_for_current_process()
{
    environ_map result;

    int i = 0;
    while(environ[i])
    {
        std::string str(environ[i++]);
        size_t indx = str.find('=');
        if(indx == std::string::npos)
            throw std::runtime_error("Failed to parse env");

        result[str.substr(0, indx)] = str.substr(indx +1);
    }

    return result;
}


