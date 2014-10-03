#include "update-command.h"
#include <stdio.h>
#include "base64.h"
#include <cstring>
#include "commands.h"
#include "subsystems.h"
#include "SpaceString.h"
#include "SpaceDecl.h"
#include "shakespeare.h"

extern const char* s_cs1_subsystems[];

void* UpdateCommand::Execute() {
    FILE* fp_update_file = NULL;
    char* result = NULL;
    int retry = 10000;

    while(retry > 0 && fp_update_file == NULL){
        fp_update_file = fopen(this->GetPath(), "ab+");
        retry =- 1;
    }

    printf("Uploading file %s\n", this->GetPath());

    if(fp_update_file != NULL) {
        retry = 10000;
        size_t bytes_left = this->GetDataLength();
        size_t bytes_written = 0;
        while(retry > 0 && bytes_left > 0){
            bytes_left -= bytes_written;
            bytes_written += fwrite(this->file_data + bytes_written, sizeof(char), bytes_left, fp_update_file);
            retry =- 1;
        }

        fclose(fp_update_file); 

        result = (char* )malloc(sizeof(char) * (50 + CMD_HEAD_SIZE) );
        memset(result + CMD_HEAD_SIZE, '\0', sizeof(char) * 50);
        sprintf(result, "%lld", (long long)bytes_written);
        result[0] = UPDATE_CMD;
        result[1] = CS1_SUCCESS;
    }

    return result;         
}
void* UpdateCommand::ParseResult(const char *result)
{
    static struct InfoBytesUpdate info_bytes;
    info_bytes.update_status = result[1];
    info_bytes.bytes_written = result + CMD_HEAD_SIZE; 

    FILE* logfile;

    char buffer[80];
    logfile=Shakespeare::open_log("/home/logs",s_cs1_subsystems[COMMANDER]);
    if(info_bytes.update_status == CS1_SUCCESS)
        sprintf(buffer,"Update success. File %s deleted",info_bytes.bytes_written);
    else
        sprintf(buffer,"Update failure. File %s not deleted",info_bytes.bytes_written);

    if (logfile != NULL){
        Shakespeare::log(logfile,Shakespeare::NOTICE,s_cs1_subsystems[COMMANDER], buffer);
    }


    return (void*)&info_bytes;


}
