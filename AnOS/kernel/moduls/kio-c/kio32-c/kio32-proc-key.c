#include "../../kio/kio32/kio32-proc-key.h"

void kio32_process_key(const sbyte k){
    if(k == '\n'){
//      TODO: add command processing
    }
    else if(k == '\b'){
//      TODO: add backspace processing
    }
    else if(k >= ' '){
        kio32_print_symbol(k, (symbol_attribute){.bg = BLACK, .fg = WHITE});
    }
}