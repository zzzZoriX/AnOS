#ifndef KEYBOARD32
#define KEYBOARD32

#include "../utils.h"
#include "../low-level.h"

#define INTERRUPT_GATE          0x8e
#define KB_STATUS_PORT          0x64
#define KB_DATA_PORT            0x60
#define KERNEL_CODE_SEG_OFFSET  0x08

#define PIC1_COMMAND_PORT       0x20
#define PIC2_COMMAND_PORT       0xa0
#define PIC1_DATA_PORT          0x21
#define PIC2_DATA_PORT          0xa1

#define IDT_SIZE                256

typedef struct {
    uword   lower_bits,
            selector;
    ubyte   zero,
            gate;
    uword   hightest_bits;
} __attribute__((packed)) IDT_element;

extern IDT_element IDT[IDT_SIZE];

void kio32_idt_init(void);
void kio32_kb_init(void);

#endif // KEYBOARD32