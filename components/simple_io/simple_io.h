

#ifndef __SIMPLE_IO_H__
#define __SIMPLE_IO_H__

#include "esp_err.h"

#define BLACK       0x000000
#define WHITE       0xFFFFFF
#define RED         0xFF0000
#define GREEN       0x00FF00
#define BLUE        0x0000FF
#define YELLOW      0xFFFF00
#define MAGENTA     0xFF00FF
#define CYAN        0x00FFFF
#define GRAY        0x808080
#define SILVER      0xC0C0C0
#define MAROON      0x800000
#define OLIVE       0x808000
#define DARKGREEN   0x006400
#define NAVY        0x000080
#define PURPLE      0x800080
#define TEAL        0x008080
#define INDIGO      0x4B0082
#define BROWN       0xA52A2A
#define CORAL       0xFF7F50
#define CRIMSON     0xDC143C
#define DARKBLUE    0x00008B
#define DARKGRAY    0xA9A9A9
#define DARKKHAKI   0xBDB76B
#define DARKMAGENTA 0x8B008B
#define DARKOLIVE   0x556B2F
#define DARKORANGE  0xFF8C00
#define DARKRED     0x8B0000
#define DARKSALMON  0xE9967A
#define DARKSEAGREEN 0x8FBC8F
#define DARKSLATEBLUE 0x483D8B
#define DARKTURQUOISE 0x00CED1
#define DEEPPINK     0xFF1493
#define FORESTGREEN  0x228B22
#define GOLD         0xFFD700
#define GOLDENROD    0xDAA520
#define HOTPINK      0xFF69B4
#define INDIANRED    0xCD5C5C
#define KHAKI        0xF0E68C
#define LIGHTBLUE    0xADD8E6
#define LIGHTCORAL   0xF08080
#define LIGHTGRAY    0xD3D3D3
#define LIGHTGREEN   0x90EE90
#define LIGHTPINK    0xFFB6C1
#define LIGHTSALMON  0xFFA07A
#define LIGHTSEAGREEN 0x20B2AA
#define LIGHTSKYBLUE 0x87CEFA
#define LIGHTSLATEGRAY 0x778899
#define LIMEGREEN    0x32CD32
#define MEDIUMAQUAMARINE 0x66CDAA
#define MEDIUMPURPLE 0x9370DB
#define MEDIUMSEAGREEN 0x3CB371
#define MEDIUMSLATEBLUE 0x7B68EE
#define MEDIUMSPRINGGREEN 0x00FA9A
#define MEDIUMTURQUOISE 0x48D1CC
#define MIDNIGHTBLUE 0x191970

typedef struct {
    uint32_t red_pin;
    uint32_t green_pin;
    uint32_t blue_pin;
}pins_t;

esp_err_t configure_RGB_LED(pins_t* led_pins);
void run_loop(pins_t* led_pins);
void set_pin_level(uint32_t pin, uint32_t level);

#endif // __SIMPLE_IO_H__

