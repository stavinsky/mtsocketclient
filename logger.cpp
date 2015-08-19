#include "logger.h"

Logger::Logger(const char * filename)
{
    logfile.open(filename, std::ios::app);

}
Logger::~Logger()
{
    logfile.close();
}

void Logger::log(const char *msg)
{
    logfile << msg << std::endl;
}
