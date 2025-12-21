#ifndef KIO32KM
#define KIO32KM

static const char kb_map[128] = {
0, 27, 
'1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
'-', '=', '\b', '\t',
'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'',
'`', 0,
'\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
'*', 
0,      // alt
' ',    // space
0,      // caps lock
0,      // 59 - f1 >> ...
0, 0, 0, 0, 0, 0, 0, 0,
0,      // ... << f10
0,      // 69 - num lock
0,      // scroll lock
0,      // home key
0,      // up arrow
0,      // page up
'-',
0,      // left arrow
0,
0,      // right arrow
'+',
0,      // 79 - end key
0,      // down arrow
0,      // page down
0,      // insert key
0,      // delete key
0, 0, 0,
0,      // f11
0,      // f12
0,      // all others key undefined
};

#define KIO32_UP_ARROW_KEYCODE        0x48
#define KIO32_DOWN_ARROW_KEYCODE      0x50
#define KIO32_RIGHT_ARROW_KEYCODE     0x4d
#define KIO32_LEFT_ARROW_KEYCODE      0x4b

#define KIO32_UP_ARROW_MAGIC          130
#define KIO32_DOWN_ARROW_MAGIC        131
#define KIO32_RIGHT_ARROW_MAGIC       132
#define KIO32_LEFT_ARROW_MAGIC        133

#endif // KIO32KM