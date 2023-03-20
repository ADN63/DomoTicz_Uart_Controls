#pragma once
#ifndef Uart_Def_h
#define Uart_Def_h

#define UART_BAUDRATE 115200

#define MAX_UART_INPUT 32
#define MAX_CMD_LENGHT 6
#define MAX_ACTION_LENGHT 7
#define MAX_VALUE_INPUT ((MAX_CMD_LENGHT + MAX_ACTION_LENGHT) + 6)
#define zpla (MAX_CMD_LENGHT + MAX_ACTION_LENGHT + MAX_VALUE_INPUT)
#if zpla > MAX_UART_INPUT
#error("Payload is overlaod")
#endif
// MAX_CMD_LENGHT
// #define MAX_PARSED_INPUT 6 // Include cmd && action
#define MAX_PAYLOAD (MAX_VALUE_INPUT + 1)
#define IsValidInput(x) strlen(x) < MAX_PARSED_INPUT
#define IsValidCmd(x) (!strcmp(CMD_, x))
#define IsValidAction(x) (!strcmp(ACTION_, x))

struct uart_def
{
    char cmd[MAX_CMD_LENGHT + 1];
    char action[MAX_ACTION_LENGHT + 1];
    char value[MAX_VALUE_INPUT + 1];
};
uart_def payload_uart;
P(p_startup_msg) = "NodeControl Loaded\nEnter <node,help> to show how it's work";
#define MSG_STARTUP_NODE_CONTROL Fstring(p_startup_msg)

P(p_readme_node_control) = "look at https://";
#define README_UART Fstring(p_readme_node_control)

P(p_payload_too_big) = "payload too big";
#define TOOBIG Fstring(p_payload_too_big)

P(p_error_cmd) = "error cmd";
#define ERRORCMD Fstring(p_error_cmd)

#include "cmd.h"
#include "action.h"
#define _VALUE string(payload_uart.value)

#endif