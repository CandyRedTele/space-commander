#ifndef UPDATE_COMMAND_H
#define UPDATE_COMMAND_H


#include <string>
#include "icommand.h"

using namespace std;

class UpdateCommand : public ICommand {
public:
    UpdateCommand(string* path) {
        this->path = path;
    };
    
    ~UpdateCommand(){ 
        if (path != NULL) {
            delete path;
            path = NULL;
        }
    };

    void Execute() {};
    string* GetPath() { return path; };
private:
    string* path;
};
#endif