#ifndef UIRECT_H
#define UIRECT_H

struct UIRect
{
    int x, y, w, h;

    UIRect(int x_ = 0, int y_ = 0, int w_ = 0, int h_ = 0)
        : x(x_), y(y_), w(w_), h(h_) {}

    bool contains(int px, int py) const {
        return px >= x && px < (x + w) && py >= y && py < (y + h);
    }
};

#endif // UIRECT_H