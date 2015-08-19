#include <fstream>
#include <iostream>
class Logger
{

    public:
    Logger(const char * filename);
    ~Logger();
    void log(const char * msg);
    std::ofstream logfile;
};

