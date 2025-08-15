#ifndef UIPADDING_H
#define UIPADDING_H

#include <stdint.h>

struct UIPadding {
    int16_t top = 0, right = 0, bottom = 0, left = 0;

    UIPadding(int16_t all = 0) : top(all), right(all), bottom(all), left(all) {}
    UIPadding(int16_t t, int16_t r, int16_t b, int16_t l) : top(t), right(r), bottom(b), left(l) {}
};

#endif // UIPADDING_H