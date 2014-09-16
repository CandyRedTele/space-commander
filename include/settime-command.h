#ifndef SETTIME_COMMAND_H
#define SETTIME_COMMAND_H
#define SETTIME_CMD_SIZE 9
#define SETTIME_RTN_SIZE 10

#include "icommand.h"
#include <time.h>
#include <iostream>
#include <cstdio>

using namespace std;

struct InfoBytesSetTime
{
    char time_status;
    time_t time_set;

};
class SetTimeCommand : public ICommand {
public:
    SetTimeCommand(time_t time);  
    time_t GetSeconds() { return seconds; };
    void* Execute();
    void* ParseResult(const char * result);        
private:
    time_t seconds;
};
#endif
