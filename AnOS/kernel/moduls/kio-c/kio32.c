#include "../kio/kio32.h"

vga_info   _vga_info;

void kio32_init_vga(void){
//  init vga info
    _vga_info.VGA =                 (volatile sbyte*)0xb8000;
    _vga_info.vga_rows_count =      25;
    _vga_info.vga_columns_count =   80;
    _vga_info.vga_symbol_size =     2;
    _vga_info.vga_row_size =        _vga_info.vga_columns_count * _vga_info.vga_symbol_size;
    _vga_info.vga_column_size =     _vga_info.vga_row_size * _vga_info.vga_symbol_size;
    _vga_info.vga_screen_size =     _vga_info.vga_row_size * _vga_info.vga_columns_count;

//  init cursor info
    _vga_info.vga_pos =             0;
    _vga_info.cursor_pos =          0;
    _vga_info.current_line_size =   0;
}

void kio32_clear_screen(void){
    for(sdword i = 0; i < _vga_info.vga_screen_size; ++i)
        kio32_print_symbol(' ', (symbol_attribute){.bg = BLACK, .fg = BLACK});

    _vga_info.cursor_pos = 0;
    _vga_info.current_line_size = 0;
    _vga_info.vga_pos = 0;
}

void kio32_print_symbol(const char c, const symbol_attribute attr){
    _vga_info.VGA[_vga_info.vga_pos++] = c;
    _vga_info.VGA[_vga_info.vga_pos++] = MAKE_VGA_ATTRIBUTE_FROM_STRUCT(attr);

    ++_vga_info.cursor_pos;
    ++_vga_info.current_line_size;
}

void kio32_print(const sbyte* str, const symbol_attribute attrfas){
    for(sdword i = 0; str[i] != '\0'; ++i)
        kio32_print_symbol(str[i], attrfas);
}