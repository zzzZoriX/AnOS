#ifndef KIO32BUF
#define KIO32BUF

#include "../../utils.h"

#define KIO32_MAX_BUFFER_SIZE   256

typedef struct {
    sbyte   data[KIO32_MAX_BUFFER_SIZE];
    udword  head,   // to write
            tail,   // to read
            count;  // current elements count
} buffer32_t;

extern buffer32_t kio32_buffer;


void    kio32_buffer_init(void);
bool_t  kio32_buffer_has_data(void);
void    kio32_buffer_put_char(const sbyte c);
sbyte   kio32_buffer_get_char(void);

#endif // KIO32BUF