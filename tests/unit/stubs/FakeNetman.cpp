#include <Net2Com.h>

int main(){
    Net2Com* com_channel = new Net2Com(PIPE_ONE, PIPE_TWO, PIPE_THREE, PIPE_FOUR);
    
    unsigned char ONE = 1;
    unsigned char TWO_FIFTY_TWO = 252

    com_channel->WriteToInfoPipe(ONE);
    com_channel->WriteToDataPipe(TWO_FIFTY_TWO);

    // TODO send command ...




    delete com_channel;

}