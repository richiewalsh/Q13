/*
part of the MTU COMP71004 module
author: Krishna Panduru
the program here performs a serial passthrough operation between USB and serial (p9, p10). 
correct upto 5 errors for proper functionality. 
the 6th error is a runtime error generating the following error. correct that as well.
++ MbedOS Error Info ++ 
Error Status: 0x80010130 Code: 304 Module: 1 
Error Message: pinmap not found for peripheral 
Location: 0x4353 Error Value: 0xFFFFFFFF
*/
#include "mbed.h"
#include <string.h>

//#define MAX_BUFFER_SIZE 64

DigitalOut myled(LED1);
BufferedSerial pc(USBRX, USBTX);
BufferedSerial dev(PB_9, PB_10);
string h = "Hello!! \r\n";
//char *buff = new char[MAX_BUFFER_SIZE];

void dev_recv(){
    while(dev.readable()){
        pc.write(dev.read());   
    }    
}

void pc_recv(){
    while(pc.readable()){
        dev.write(pc.read(/*buff, sizeof(buff)*/));    
    }    
}

int main() {
    
    pc.set_baud(9600);
    dev.set_baud(115200);
    pc.attach(&pc_recv);
    dev.attach(&dev_recv);
    pc.write(h);

    while(1) {
        myled = 1;
        wait_us(1000000);
        myled = 0;
        wait_us(1000000);
    }
}