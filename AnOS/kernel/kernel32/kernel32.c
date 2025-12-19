#include "../moduls/kio/kio32/kio32.h"
#include "../moduls/kio/kio32/kio32-buf.h"
#include "../moduls/kio/kio32/kio32-proc-key.h"

void kernel32_main(void){
    kio32_init_vga();
    kio32_idt_init();
    kio32_kb_init();
    kio32_buffer_init();
    
    const sbyte welcome_message[] = "Welcome to AnOS!\0";
    const sbyte version[] =         "  ver. 0.0.1\0";
    
    kio32_clear_screen();
    kio32_print(welcome_message, (symbol_attribute){.bg = BLACK, .fg = WHITE});
    kio32_newline();
    kio32_print(version, (symbol_attribute){.bg = BLACK, .fg = WHITE});
    kio32_newline();
    
    kio32_idt_init();
    kio32_kb_init();


    while(true){
        if(kio32_buffer_has_data())
            kio32_process_key(kio32_buffer_get_char());
    }
}