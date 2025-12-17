#ifndef KIOC
#define KIOC

typedef enum {
    BLACK =         0x0,
    BLUE =          0x1,
    GREEN =         0x2,
    CYAN =          0x3,
    RED =           0x4,
    MAGNETA =       0x5,
    BROWN =         0x6,
    LIGHTGRAY =     0x7,
    DARKGRAY =      0x8,
    LIGHTBLUE =     0x9,
    LIGHTGREEN =    0xa,
    LIGHTCYAN =     0xb,
    LIGHTRED =      0xc,
    PINK =          0xd,
    YELLOW =        0xe,
    WHITE =         0xf
} Color;

typedef struct {
    Color   bg, // background
            fg; // foreground
} __attribute__((packed)) symbol_attribute;

#define MAKE_VGA_ATTRIBUTE_FROM_STRUCT(sattr)   (((sattr).bg << 8) | (sattr).fg)
#define MAKE_VGA_ATTRIBUTE_FROM_VALUES(bg, fg)  ((bg) << 8 | (fg))

#endif // KIOC