#include "../../kio/kio32/kio32-buf.h"

buffer32_t kio32_buffer;

void kio32_buffer_init(void){
    kio32_buffer.count = 0;
    kio32_buffer.head =  0;
    kio32_buffer.tail =  0;
}

bool_t kio32_buffer_has_data(void){
    return kio32_buffer.count > 0;
}

void kio32_buffer_put_char(const ubyte c){
    if(kio32_buffer.count >= KIO32_MAX_BUFFER_SIZE)
        return;

    kio32_buffer.data[kio32_buffer.head] = c;
    kio32_buffer.head = (kio32_buffer.head + 1) % KIO32_MAX_BUFFER_SIZE;
    ++kio32_buffer.count;
}

ubyte kio32_buffer_get_char(void){
    if(kio32_buffer.count == 0)
        return 0;

    ubyte charcode = kio32_buffer.data[kio32_buffer.tail];
    kio32_buffer.tail = (kio32_buffer.tail + 1) % KIO32_MAX_BUFFER_SIZE;
    --kio32_buffer.count;

    return charcode;
}