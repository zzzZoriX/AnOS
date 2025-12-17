#ifndef KIO32
#define KIO32

#include "../utils.h"
#include "kio-color.h"

typedef struct {
//  vga cursor info
    sdword  vga_pos,    // position in vga(1 step = 2 byte)
            cursor_pos; // noramal position(vga_pos / 2)
    uword   current_line_size;

//  vga info
    sdword  vga_columns_count,  // by default - 80
            vga_rows_count,     // by default - 25
            vga_symbol_size,    // 2 bytes
            vga_row_size,       // by default - 160 bytes
            vga_column_size,    // by default - 50 bytes
            vga_screen_size;    // by default - 4000 bytes

    volatile sbyte*  VGA;
} __attribute__((packed)) vga_info;

extern vga_info    _vga_info;


void kio32_init_vga(void);

void kio32_clear_screen(void);

void kio32_print_symbol(const char c, const symbol_attribute attr);

/**
 * @param attrfas   used for all symbols in the string
 */
void kio32_print(const sbyte* str, const symbol_attribute attrfas);

void kio32_newline(void);

#endif // KIO32