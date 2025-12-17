#ifndef LLEVEL
#define LLEVEL

#include "utils.h"

extern void     load_idt(unsigned long* idt_ptr);
extern void     write_port(uword port, ubyte data);
extern ubyte    read_port(uword port);
extern void     sakio32_kbh(void);

#endif // LLEVEL