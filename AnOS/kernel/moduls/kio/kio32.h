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
    sdword  vga_columns_count,
            vga_rows_count,
            vga_symbol_size,
            vga_row_size,
            vga_column_size,
            vga_screen_size;

    volatile sbyte*  VGA;
} vga_info;

extern vga_info    _vga_info;


void kio32_init_vga(void);

void kio32_clear_screen(void);

void kio32_print_symbol(const char c, const symbol_attribute attr);

/**
 * @param attrfas   used for all symbols in the string
 */
void kio32_print(const sbyte* str, const symbol_attribute attrfas);

#endif // KIO32