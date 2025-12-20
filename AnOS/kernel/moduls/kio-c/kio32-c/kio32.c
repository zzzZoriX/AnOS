#include "../../kio/kio32/kio32.h"

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
    _vga_info.current_line_number = 1;
}

void kio32_clear_screen(void){
    for(sdword i = 0; i < _vga_info.vga_screen_size;){
        _vga_info.VGA[i++] = ' ';
        _vga_info.VGA[i++] = MAKE_VGA_ATTRIBUTE_FROM_VALUES(BLACK, BLACK);
    }

    _vga_info.cursor_pos = 0;
    _vga_info.current_line_size = 0;
    _vga_info.vga_pos = 0;
}

void kio32_print_symbol(const char c, const symbol_attribute attr){
    _vga_info.VGA[_vga_info.vga_pos++] = c;
    _vga_info.VGA[_vga_info.vga_pos++] = MAKE_VGA_ATTRIBUTE_FROM_STRUCT(attr);

    ++_vga_info.cursor_pos;
    _vga_info.current_line_size += _vga_info.vga_symbol_size;
}

void kio32_print(const sbyte* str, const symbol_attribute attrfas){
    for(sdword i = 0; str[i] != '\0'; ++i)
        kio32_print_symbol(str[i], attrfas);
}

void kio32_newline(void){
    _vga_info.vga_pos += _vga_info.vga_row_size - _vga_info.current_line_size;
    
    _vga_info.cursor_pos = _vga_info.vga_pos / 2;
    _vga_info.current_line_size = 0;
    ++_vga_info.current_line_number;

    if(_vga_info.current_line_number > _vga_info.vga_rows_count)
        kio32_scroll_screen();
}

void kio32_scroll_screen(void){
//  move up all lines
    for(sdword i = _vga_info.vga_row_size; i < _vga_info.vga_screen_size; ++i)
        _vga_info.VGA[i - _vga_info.vga_row_size] = _vga_info.VGA[i];

//  clear last line
    sdword last_line_start = (_vga_info.vga_rows_count - 1) * _vga_info.vga_row_size;
    for(sdword i = last_line_start; i < _vga_info.vga_screen_size; i += _vga_info.vga_symbol_size){
        _vga_info.VGA[i] = ' ';
        _vga_info.VGA[i + 1] = MAKE_VGA_ATTRIBUTE_FROM_VALUES(BLACK, BLACK);
    }

    _vga_info.vga_pos = last_line_start;
    _vga_info.cursor_pos = _vga_info.vga_pos / 2;
    _vga_info.current_line_size = 0;
}

void kio32_backspace(void){
    if(_vga_info.vga_pos == 0 || _vga_info.vga_pos % _vga_info.vga_row_size == 0)
        return;

    _vga_info.vga_pos -= 2;
    --_vga_info.cursor_pos;
    --_vga_info.current_line_size;
    
    _vga_info.VGA[_vga_info.vga_pos] = ' ';
    _vga_info.VGA[_vga_info.vga_pos + 1] = MAKE_VGA_ATTRIBUTE_FROM_VALUES(BLACK, BLACK);
}