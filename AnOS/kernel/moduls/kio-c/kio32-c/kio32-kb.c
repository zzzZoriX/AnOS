#include "../../kio/kio32/kio32-kb.h"
#include "../../kio/kio32/kio32.h"

IDT_element IDT[IDT_SIZE];


void kio32_idt_init(void){
    unsigned long   kb_addr32 = (unsigned long)akio32_kbh,
                    idt_addr32,
                    idt_ptr[2];

/*
    why 0x21?
    keyboard using IRQ1 it's input gate #1 of PIC1 controller, it offset equal 0x20
    now we just sum this two numbers and getting 0x21 - number of interrupt
*/
    IDT[0x21].lower_bits = kb_addr32 & 0xffff;
    IDT[0x21].hightest_bits = (kb_addr32 >> 16) & 0xffff;
    IDT[0x21].gate = INTERRUPT_GATE;
    IDT[0x21].zero = 0;
    IDT[0x21].selector = KERNEL_CODE_SEG_OFFSET;

    /* ICW1 */
    write_port(PIC1_COMMAND_PORT, 0x11);
    write_port(PIC2_COMMAND_PORT, 0x11);

    /* ICW2 */
    write_port(PIC1_DATA_PORT, 0x20);
    write_port(PIC2_DATA_PORT, 0x28);

    /* ICW3 */
    write_port(PIC1_DATA_PORT, 0x00);
    write_port(PIC2_DATA_PORT, 0x00);

    /* ICW4 */
    write_port(PIC1_DATA_PORT, 0x01);
    write_port(PIC2_DATA_PORT, 0x01);

    /* interrupts mask */
    write_port(PIC1_DATA_PORT, 0xff);
    write_port(PIC2_DATA_PORT, 0xff);

    idt_addr32 = (unsigned long)IDT;
    idt_ptr[0] = (sizeof(IDT_element) * IDT_SIZE) + ((idt_addr32 & 0xffff) << 16);
    idt_ptr[1] = idt_addr32 >> 16;

    load_idt(idt_ptr);
}

void kio32_kb_init(void){
    write_port(PIC1_DATA_PORT, 0xfd);
}

void kio32_kbh(void){
    ubyte   status;
    sbyte   keycode;

    write_port(PIC1_COMMAND_PORT, 0x20);

    status = read_port(KB_STATUS_PORT);
    
    if(status & 0x01){
        keycode = read_port(KB_DATA_PORT);
        if(keycode < 0 || keycode & 0x80){
            // write_port(PIC1_COMMAND_PORT, 0x20);s
            return;
        }
        else if(keycode == KIO32_UP_ARROW_KEYCODE)
            kio32_buffer_put_char(KIO32_UP_ARROW_MAGIC);

        else if(keycode == KIO32_DOWN_ARROW_KEYCODE)
            kio32_buffer_put_char(KIO32_DOWN_ARROW_MAGIC);

        else if(keycode == KIO32_LEFT_ARROW_KEYCODE)
            kio32_buffer_put_char(KIO32_LEFT_ARROW_MAGIC);

        else if(keycode == KIO32_RIGHT_ARROW_KEYCODE)
            kio32_buffer_put_char(KIO32_RIGHT_ARROW_MAGIC);
        
        else
            kio32_buffer_put_char(kb_map[keycode]);
    }
}