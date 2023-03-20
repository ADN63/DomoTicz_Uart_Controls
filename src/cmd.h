#pragma once
#ifndef DomoTicz_cmd_h_
#define DomoTicz_cmd_h_
#define CMD_ string(payload_uart.cmd)

/**
 *  ** HOW TO DECLARE A COMMAND
 *
 * * simply create a P object
 * * like this => P(p_available_cmd_node) = "node";
 * * and define a macro => #define _CMD_NODE String(FPSTR(p_available_cmd_node)).c_str()
 * * And Add to TABLES_CMD
 */
P(p_available_cmd_node) = "node";

// #define _CMD_NODE String(FPSTR(p_available_cmd_node)).c_str()
#define _CMD_NODE Fstring(p_available_cmd_node)

String TABLES_CMD[] = {
    _CMD_NODE};
#endif