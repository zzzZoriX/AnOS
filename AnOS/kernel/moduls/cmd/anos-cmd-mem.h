#ifndef ANOSCMDMEM
#define ANOSCMDMEM

#include "anos-cmd.h"
#include "../utils.h"

#define MAX_REM_CMD     15

extern cmd command_memory[MAX_REM_CMD];
extern sbyte    selected_command,
                rem_command_count;


void cmd_mem_remember(cmd command);
void cmd_mem_load_from_mem(cmd* command, sbyte incdecv);
void cmd_mem_scroll(void);
void cmd_mem_clear(void); // can be used like a initialize function

#endif // ANOSCMDMEM