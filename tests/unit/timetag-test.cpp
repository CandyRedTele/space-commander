/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*
* AUTHORS : Space Concordia 2014, Shawn
*
* TITLE : timetag-test.cpp 
*
* DESCRIPTION : Tests the TimetagCommand class
*
*----------------------------------------------------------------------------*/
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "CppUTest/TestHarness.h"
#include "CppUTest/MemoryLeakDetectorMallocMacros.h"
#include "SpaceString.h"
#include "command-factory.h"
#include "timetag-command.h"
#include "icommand.h"
#include "fileIO.h"
#include "commands.h"
#include "subsystems.h"
#include "dirUtl.h"

#include "Date.h"

#include "SpaceDecl.h"
#define DATETIMEFORMAT "%Y%m%d%H%M"

static char command_buf[TIMETAG_CMD_SIZE] = {'\0'};

TEST_GROUP(TimetagTestGroup)
{
    void setup()
    {
        memset(command_buf, 0, TIMETAG_CMD_SIZE);
    }
    void teardown()
    {
    
    }
};

TEST(TimetagTestGroup, AddJob)
{  
  int test_result=-1;

  char task[72] = "echo \"$(grep \"^${USER}:\" /etc/passwd | cut -d: -f5)\" \\>\\> /tmp/test.log";
  command_buf[0] = TIMETAG_CMD; 
  memcpy(command_buf+1,task,72); 

  TimetagCommand *command = (TimetagCommand*)CommandFactory::CreateCommand(command_buf);

  Date date(2014, 9, 16, 3, 4, 4);
  time_t rawtime = date.GetTimeT();

  int result = command->AddJob(rawtime,task);
  if (result > 0) {
     test_result=0; 
  }
  CHECK_EQUAL(0, test_result);
}

TEST(TimetagTestGroup, CancelJob)
{
  int add_result=-1;

  char task[48] = "grep -HinT --color=auto something /tmp/test.log";
  command_buf[0] = TIMETAG_CMD; 
  memcpy(command_buf+1,task,48); 

  TimetagCommand *command = (TimetagCommand*)CommandFactory::CreateCommand(command_buf);

  Date date(2014, 9, 15, 10, 10, 10);
  time_t rawtime = date.GetTimeT();

  int result = command->AddJob(rawtime,task);
  if (result > 0) {
     add_result=0; 
  }
  CHECK_EQUAL(0, add_result);

  int cancel_result = command->CancelJob(result); 
  CHECK_EQUAL(0, cancel_result);
}

/* 
TEST(TimetagTestGroup, EscapeCharacters)
{
  char to_escape[3] = {'<','>'}; // TODO NOT COMPHREHENSIVE
  char * test_string = "This is a << >> test string";
  char * result = escape_characters (test_string, 28, to_escape, 2);
  char * expected = "This is a \\<\\< \\>\\> test string";
  printf("Result: '%s'\r\n",result);
  printf("Expect: '%s'\r\n",expected);

  size_t limit = 31; 
  size_t z=0;
  for (z=0; z<limit; z++) { 
    CHECK_EQUAL(
        expected[z], result[z]
    );
  }
}
*/
