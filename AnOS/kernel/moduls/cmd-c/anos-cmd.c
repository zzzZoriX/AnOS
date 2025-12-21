#include "../cmd/anos-cmd.h"

cmd current_command = (cmd){.cmd = "\0", .arg = "\0", .cmd_index = 0, .arg_index = 0};

// 0 - writing the command ; 1 - writing an arguments ; 2 - command writing stoped
static ubyte current_command_write_state = 0;

void cmd_put_char(const sbyte c){
    if(current_command_write_state == 2)
        return;
    else if(c == ';'){
        if(current_command_write_state == 0)
            current_command.cmd[current_command.cmd_index] = '\0';
        else if(current_command_write_state == 1)
            current_command.arg[current_command.arg_index] = '\0';

        current_command_write_state = 2;
        return;
    }
    else if(c == ' ' && current_command_write_state == 0){
        if (current_command.cmd_index == 0)
            return;

        current_command.cmd[current_command.cmd_index] = '\0';

        current_command_write_state = 1;
        return;
    }

    if(c < 0x20 && c != '\t')
        return;

    if(current_command_write_state == 0){
        if (current_command.cmd_index < MAX_CMD_LEN - 1)
            current_command.cmd[current_command.cmd_index++] = c;
    }
    else if(current_command_write_state == 1){
        if(current_command.arg_index < MAX_CMD_ARG_LEN - 1)
            current_command.arg[current_command.arg_index++] = c;
    }
}

void cmd_del_last_char(void){
    if(current_command_write_state == 2)
        return;
    
    if(current_command_write_state == 0)
        --current_command.cmd_index;
    else if(current_command_write_state == 1)
        --current_command.arg_index;
}

void cmd_load(cmd other){
    current_command.cmd_index = other.cmd_index;
    current_command.arg_index = other.arg_index;

    strcopy(current_command.cmd, other.cmd);
    strcopy(current_command.arg, other.arg);
}

void cmd_clear(void){
    current_command = (cmd){.cmd = "\0", .arg = "\0", .cmd_index = 0, .arg_index = 0};

    current_command_write_state = 0;
}

void cmd_print_current(void){
    if(current_command.cmd_index > 0)
        kio32_print(current_command.cmd, (symbol_attribute){.bg = BLACK, .fg = WHITE});
    if(current_command.arg_index > 0){
        kio32_print_symbol(' ', (symbol_attribute){.bg = BLACK, .fg = WHITE});
        kio32_print(current_command.arg, (symbol_attribute){.bg = BLACK, .fg = WHITE});
        kio32_print_symbol(';', (symbol_attribute){.bg = BLACK, .fg = WHITE});
    }
}

ubyte cmd_process(void){
    bool_t isavcmd = true;

    if(compare(current_command.cmd, CMD_HELP) == 0){
        kio32_print(
            "Available commands:",
            (symbol_attribute){.bg = BLACK, .fg = WHITE}
        );
        kio32_newline();

        kio32_print(
            "  help         - print available commands and helping info",
            (symbol_attribute){.bg = BLACK, .fg = WHITE}
        );
        kio32_newline();

        kio32_print(
            "  clear        - clear screen space",
            (symbol_attribute){.bg = BLACK, .fg = WHITE}
        );
        kio32_newline();

        kio32_print(
            "  echo \"msg\"     - repeat your message",
            (symbol_attribute){.bg = BLACK, .fg = WHITE}
        );
        kio32_newline();
    }
    else if(compare(current_command.cmd, CMD_CLEAR) == 0)
        kio32_clear_screen();
    else if(compare(current_command.cmd, CMD_ECHO) == 0){
        kio32_print(
            current_command.arg,
            (symbol_attribute){.bg = BLACK, .fg = WHITE}
        );
        kio32_newline();
    }

    else{
        kio32_print(
            "Unknown command: \"",
            (symbol_attribute){.bg = BLACK, .fg = WHITE}
        );
        kio32_print(
            current_command.cmd,
            (symbol_attribute){.bg = BLACK, .fg = WHITE}
        );
        kio32_print_symbol('"', (symbol_attribute){.bg = BLACK, .fg = WHITE});
        kio32_newline();

        kio32_print(
            "For available commands list type \"help\" command",
            (symbol_attribute){.bg = BLACK, .fg = WHITE}
        );
        kio32_newline();

        isavcmd = false;
    }

    return isavcmd;
}