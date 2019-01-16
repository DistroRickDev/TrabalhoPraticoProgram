#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "admin_setup.h"
#define    BUFFERLENGTH 256

int  serialRead(){

    // Declare variables and structures
    HANDLE hSerial;
    DCB dcbSerialParams = {0};
    COMMTIMEOUTS timeouts = {0};
    int valid = 0, count = 0;


    // Open the highest available serial port number
    while (valid == 0) {
        char portaserie[15] = "\\\\.\\COM0";
        portaserie[strlen(portaserie) - 1] += count;
        printf("%s\n", portaserie);
        fprintf(stderr, "Opening serial port...");
        hSerial = CreateFile(
                portaserie, GENERIC_READ | GENERIC_WRITE, 0, NULL,
                OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hSerial == INVALID_HANDLE_VALUE) {
            fprintf(stderr, "Error\n");

        } else {
            fprintf(stderr, "OK\n");
            valid = 1;
        }

        count++;

    }

    // Set device parameters (38400 baud, 1 start bit,
    // 1 stop bit, no parity)
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (GetCommState(hSerial, &dcbSerialParams) == 0) {
        fprintf(stderr, "Error getting device state\n");
        CloseHandle(hSerial);
        return 1;
    }

    dcbSerialParams.BaudRate = CBR_115200;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    if (SetCommState(hSerial, &dcbSerialParams) == 0) {
        fprintf(stderr, "Error setting device parameters\n");
        CloseHandle(hSerial);
        return 1;
    }

    // Set COM port timeout settings
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    if (SetCommTimeouts(hSerial, &timeouts) == 0) {
        fprintf(stderr, "Error setting timeouts\n");
        CloseHandle(hSerial);
        return 1;
    }



    //read

    BOOL Read_Status;                      // Status of the various operations
    char *SerialBuffer[BUFFERLENGTH];      // Buffer Containing Rxed Data
    DWORD NoBytesRead;                    // Bytes read by ReadFile()
    int i = 0;
    if (Read_Status == FALSE) {
        printf("\n    Error! in Setting WaitCommEvent()");
    } else //If  WaitCommEvent()==True Read the RXed data using ReadFile();
    {
        printf("\n\n    Characters Received \n");
        do {
            //Read_Status = ReadFile(hComm, &TempChar, sizeof(TempChar), &NoBytesRead, NULL);
            if (!ReadFile(hSerial, SerialBuffer, BUFFERLENGTH - 1, &NoBytesRead, NULL)) {
                printf("wrong character");
            }
            //SerialBuffer[i] = TempChar;
            printf("%s", SerialBuffer);
            writeToken(SerialBuffer);
            i++;
        } while (i == 0);


    }


    // Close serial port
    fprintf(stderr, "Closing serial port...");
    if (CloseHandle(hSerial) == 0) {
        fprintf(stderr, "Error\n");
        return 1;
    }
    fprintf(stderr, "OK\n");
}
