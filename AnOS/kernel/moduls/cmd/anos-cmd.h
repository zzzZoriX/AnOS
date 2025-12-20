#ifndef ANOSCMD
#define ANOSCMD

#define MAX_CMD_LEN     10
#define MAX_CMD_ARG_LEN 512

#include "../utils.h"
#include "../str-utils.h"
#include "anos-cmd-def.h"
#include "../kio/kio32/kio32.h"

typedef struct {
    sbyte   cmd[MAX_CMD_LEN],
            arg[MAX_CMD_ARG_LEN];
    sdword  cmd_index,
            arg_index;
} cmd;

extern cmd current_command;


void cmd_put_char(const sbyte c);
void cmd_load(cmd other); 
void cmd_clear(void);

ubyte cmd_process(void);

#endif // ANOSCMD