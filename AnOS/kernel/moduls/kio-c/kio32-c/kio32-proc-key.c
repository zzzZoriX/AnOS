#include "../../kio/kio32/kio32-proc-key.h"

void kio32_process_key(const sbyte k){
    if(k == '\n'){
        kio32_newline();

        ubyte isavcmd = cmd_process();
        if(isavcmd)
            cmd_mem_remember(current_command);

        cmd_clear();
    }
    else if(k == '\b'){
        kio32_backspace();
    }
    else if(k >= ' '){
        cmd_put_char(k);
        kio32_print_symbol(k, (symbol_attribute){.bg = BLACK, .fg = WHITE});
    }
}