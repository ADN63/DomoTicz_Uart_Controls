#pragma once
#ifndef DomoTicz_Action_H_
#define DomoTicz_Action_H_
#define ACTION_ string(payload_uart.action)

/**
 *  ** HOW TO DECLARE AN ACTION
 * processus is very similar to Command :)
 *
 * * simply create a P object
 * * like this => P(p_available_action_node_help) = "help";
 * * and define a macro => #define _CMD_NODE_HELP String(FPSTR(p_available_action_node_help)).c_str()
 * * And Add to TABLES_ACTIONS
 */
P(p_action_node_help) = "help";
#define _ACTION_NODE_HELP Fstring(p_action_node_help)

P(p_action_node_name) = "name";
#define _ACTION_NODE_NAME Fstring(p_action_node_name)

P(p_action_node_id) = "id";
#define _ACTION_NODE_ID Fstring(p_action_node_id)

P(p_action_node_reset) = "reset";
#define _ACTION_NODE_RESET Fstring(p_action_node_reset)

P(p_action_node_restart) = "restart";
#define _ACTION_NODE_RESTART Fstring(p_action_node_restart)

String TABLES_ACTIONS[] = {
    _ACTION_NODE_HELP,
    _ACTION_NODE_NAME,
    _ACTION_NODE_ID,
    _ACTION_NODE_RESET,
    _ACTION_NODE_RESTART};
#endif