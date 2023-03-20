#pragma once
#ifndef _DomoTicz_Uart_Controls_Hpp_
#define _DomoTicz_Uart_Controls_Hpp_

#ifndef Arduino_h
#include <Arduino.h>
#endif

#ifndef _Domoticz_Common_H_
#include <DomoTiczCommon.h>
#endif
/**
 * IMPORTANT NOTE
    TRACE_F("Max CMD : %d\nMax ACTION : %d\nMax VALUE : %d\n", MAX_CMD_LENGHT  -  1, MAX_ACTION_LENGHT -1 , MAX_VALUE_INPUT - 1);
 * MAX_CMD 5
 * MAX_ACTION 5
 * MAX_VALUE READED 17
*/
#include "uart_def.h"

bool _parsedInput;
bool _newData;
char _receivedChars[MAX_UART_INPUT];
char _tempChars[MAX_UART_INPUT];

class NodeControls
{
private:
    static void serial_loop();
    static void parseInput();
    static void parseCmd();
    static void showReadme();

public:
    NodeControls();
    ~NodeControls();
    static void begin();
    static void loop();
};

inline void NodeControls::serial_loop()
{
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char rc;

    const char startMarker = '<';
    const char endMarker = '>';

    while (Serial.available() > 0 && _newData == false)
    {
        rc = Serial.read();

        if (recvInProgress == true)
        {
            if (rc != endMarker)
            {
                _receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= MAX_UART_INPUT)
                {
                    ndx = MAX_UART_INPUT;
                }
            }
            else
            {
                _receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                _newData = true;
            }
        }
        else if (rc == startMarker)
        {
            recvInProgress = true;
        }
    }
}

inline void NodeControls::parseInput()
{
    char cmd_buffer[MAX_CMD_LENGHT +1];
    char action_buffer[MAX_ACTION_LENGHT +1];
    char value_buffer[MAX_VALUE_INPUT +1];

    char *strtoIndx;

    strtoIndx = strtok(_tempChars, ",");

    if (strlen(strtoIndx) <= MAX_CMD_LENGHT)
    {
        strcpy(cmd_buffer, strtoIndx);
        strtoIndx = strtok(NULL, ",");
        if (strlen(strtoIndx) <= MAX_ACTION_LENGHT)
        {
            strcpy(action_buffer, strtoIndx);
            strtoIndx = strtok(NULL, ",");
            if (strlen(strtoIndx) <= MAX_VALUE_INPUT)
            {
                strcpy(value_buffer, strtoIndx);
                _parsedInput = true;
            }
            else
            {
                _parsedInput = false;
            }
        }
        else
        {
            _parsedInput = false;
        }
    }
    else
    {
        _parsedInput = false;
    }

    if (_parsedInput == true)
    {
        strcpy(payload_uart.cmd, cmd_buffer);
        strcpy(payload_uart.action, action_buffer);
        strcpy(payload_uart.value, value_buffer);
    }
    else
    {
        payload_uart = uart_def();
        _parsedInput = false;
    }
}
/**
 *
 */
inline void NodeControls::parseCmd()
{
    // if (!strcmp(CMD_, _CMD_NODE)) // an <node,?,?> is enter
    if (IsValidCmd(_CMD_NODE)) // an <node,?,?> is enter
    {
        // if (!strcmp(ACTION_, _ACTION_NODE_HELP)) // an <node,help,?> is enter
        if (IsValidAction(_ACTION_NODE_HELP))
        {
            NodeControls::showReadme();
        }
        else if (IsValidAction(_ACTION_NODE_NAME))
        {
            DomoTicz::ReceivCmdChangeName();
        }
        else if (IsValidAction(_ACTION_NODE_ID))
        {
            DomoTicz::ReceivCmdChangeId();
        }
        else if (IsValidAction(_ACTION_NODE_RESET))
        {
            DomoTicz::ReceivCmdReset();
        }
        else if (IsValidAction(_ACTION_NODE_RESTART))
        {
            DomoTicz::ReceivCmdRestart();
        }
        else
        {
            TRACE_F("%s\n", ERRORCMD);
        }
    }
    else
    {
        TRACE_F("%s\n", ERRORCMD);
    }
}

inline void NodeControls::showReadme()
{
    TRACE_F("%s\n", README_UART);
}

NodeControls::NodeControls()
{
    _newData = false;
    _parsedInput = false;
}

NodeControls::~NodeControls()
{
}

inline void NodeControls::begin()
{
    _newData = false;
    _parsedInput = false;
    /**
     * begin Serial
     */
    Serial.begin(UART_BAUDRATE);
    fdev_setup_stream(&uartout, uart_putchar, NULL, _FDEV_SETUP_WRITE);
    stdout = &uartout;
    /**
     * Ended TRACE is now available
     */
    TRACE_F("%s %s::%s\n", String(F("Node")).c_str(), _Saved_Ref.nodeName, _Saved_Ref.nodeId);
}
/***
 * @brief look at ParseCmd() for How to Add Command
 */
inline void NodeControls::loop()
{
    serial_loop();

    if (_newData == true)
    {
        _newData = false;
        if (strlen(_receivedChars) > MAX_UART_INPUT)
        {
            TRACE_F("%s :: %s\n", ERRORCMD, TOOBIG);
            return;
        }
        strcpy(_tempChars, _receivedChars);
        parseInput();
    }
    if (_parsedInput)
    {
        _parsedInput = false;
        parseCmd();
    }
}

#endif