#ifndef ENVIRON_H
#define ENVIRON_H

#include <string>
#include <map>

struct _Env;


class raw_environ_holder
{
public:
    raw_environ_holder() = delete;
    raw_environ_holder(const raw_environ_holder&) = delete;
    raw_environ_holder(raw_environ_holder&&);

    raw_environ_holder& operator=(const raw_environ_holder&) = delete;
    raw_environ_holder& operator=(raw_environ_holder&&);

    ~raw_environ_holder();

    operator char**() { return ppenv;};

private:
    friend class environ_map;

    explicit raw_environ_holder(char** ppenv) : ppenv(ppenv){};

    void destroy();

    char** ppenv;
};


class environ_map : public std::map<std::string, std::string>
{
public:
    environ_map() = default;
    environ_map(const std::map<std::string, std::string>& map) : std::map<std::string, std::string>(map) {};
    environ_map(const environ_map&) = default;
    raw_environ_holder raw() const;

    static environ_map get_for_current_process();
};


#endif //CMD_EXEC_ENVIRON_H
