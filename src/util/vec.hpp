#pragma once

namespace neptune::utils {
    /*
     * @brief 2D integer vector.
     */
    class Vector2i
    {
    private:
        int x,y = 0;
    public:
        Vector2i(int x, int y)
        {
            this->x = x;
            this->y = y;
        }

        int getX() { return x; }
        int getY() { return y; }

        void setX(int x) { this->x = x; }
        void setY(int y) { this->y = y; }
    };
}