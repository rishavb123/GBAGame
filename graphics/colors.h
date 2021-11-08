#ifndef COLORS_H
#define COLORS_H

#define COLOR(r, g, b) ((r) | (g) << 5 | (b) << 10)
#define WHITE COLOR(31, 31, 31)
#define RED COLOR(31, 0, 0)
#define GREEN COLOR(0, 31, 0)
#define BLUE COLOR(0, 0, 31)
#define MAGENTA COLOR(31, 0, 31)
#define CYAN COLOR(0, 31, 31)
#define YELLOW COLOR(31, 31, 0)
#define BLACK COLOR(0, 0, 0)
#define GRAY COLOR(5, 5, 5)

#endif