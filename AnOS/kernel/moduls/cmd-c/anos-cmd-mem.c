#include "../cmd/anos-cmd-mem.h"

cmd command_memory[MAX_REM_CMD];
sbyte    selected_command = 15,
         rem_command_count = 0;

void cmd_mem_remember(cmd command){
    command_memory[rem_command_count].arg_index = command.arg_index;
    command_memory[rem_command_count].cmd_index = command.cmd_index;

    strcopy(command_memory[rem_command_count].cmd, command.cmd);
    strcopy(command_memory[rem_command_count].arg, command.arg);

    ++rem_command_count;
}

void cmd_mem_load_from_mem(cmd* command, sbyte incdecv){
    if(selected_command >= rem_command_count)
        selected_command = 0;
    if(selected_command < 0)
        selected_command = rem_command_count - 1;

    *command = command_memory[selected_command];

    selected_command += incdecv;
}

void cmd_mem_scroll(void){
    for(sbyte i = 1; i < rem_command_count; ++i)
        command_memory[i - 1] = command_memory[i];

    --rem_command_count;
    command_memory[rem_command_count] = (cmd){.cmd = "\0", .arg = "\0", .cmd_index = 0, .arg_index = 0};
}

void cmd_mem_clear(void){ 
    for(sbyte i = 0; i < MAX_REM_CMD; ++i)
        command_memory[i] = (cmd){.cmd = "\0", .arg = "\0", .cmd_index = 0, .arg_index = 0};

    rem_command_count = 0;
}