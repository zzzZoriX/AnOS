#include "../../kio/kio32/kio32-proc-key.h"

void kio32_process_key(const ubyte k){
    if(k == '\n'){
        kio32_newline();

        ubyte isavcmd = cmd_process();
        if(isavcmd)
            cmd_mem_remember(current_command);

        cmd_clear();
    }

    else if(k == KIO32_UP_ARROW_MAGIC){
        cmd load_tmp;

        cmd_mem_load_from_mem(&load_tmp, 1);
        cmd_load(load_tmp);

        kio32_clear_line();
        cmd_print_current();
    }
    else if(k == KIO32_DOWN_ARROW_MAGIC){
        cmd load_tmp;

        cmd_mem_load_from_mem(&load_tmp, -1);
        cmd_load(load_tmp);

        kio32_clear_line();
        cmd_print_current();
    }

    else if(k == '\b'){
        cmd_del_last_char();
        kio32_backspace();
    }
    else if(k >= ' '){
        cmd_put_char(k);
        kio32_print_symbol(k, (symbol_attribute){.bg = BLACK, .fg = WHITE});
    }
}