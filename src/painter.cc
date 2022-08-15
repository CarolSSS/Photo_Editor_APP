#include "painter.h"

namespace photos {

using glm::vec2;

void Painter::Display(int size_y, int color_y) {
    // Draw brush options
    ci::gl::drawString("Brush Size", vec2(1100, size_y - 50));
    ci::gl::color(ci::Color("white"));
    ci::gl::drawSolidCircle(vec2(START_POSITION, size_y), 5);
    ci::gl::drawSolidCircle(vec2(START_POSITION + THRESHOLD, size_y), 7.5);
    ci::gl::drawSolidCircle(vec2(START_POSITION + THRESHOLD * 2, size_y), 10);
    ci::gl::drawSolidCircle(vec2(START_POSITION + THRESHOLD * 3, size_y), 12.5);
    ci::gl::drawSolidCircle(vec2(START_POSITION + THRESHOLD * 4, size_y), 15);
    ci::gl::drawSolidCircle(vec2(START_POSITION + THRESHOLD * 5, size_y), 17.5);
    ci::gl::drawSolidCircle(vec2(START_POSITION + THRESHOLD * 6, size_y), 20);
    // Draw color options
    ci::gl::drawString("Brush Color", vec2(START_POSITION, color_y - 50));
    ci::gl::color(ci::Color("purple"));
    ci::gl::drawSolidCircle(vec2(START_POSITION, color_y), 20);
    ci::gl::color(ci::Color("yellow"));
    ci::gl::drawSolidCircle(vec2(START_POSITION + THRESHOLD, color_y), 20);
    ci::gl::color(ci::Color("lightblue"));
    ci::gl::drawSolidCircle(vec2(START_POSITION + THRESHOLD * 2, color_y), 20);
    ci::gl::color(ci::Color("red"));
    ci::gl::drawSolidCircle(vec2(START_POSITION + THRESHOLD * 3, color_y), 20);
    ci::gl::color(ci::Color("blue"));
    ci::gl::drawSolidCircle(vec2(START_POSITION + THRESHOLD * 4, color_y), 20);
    ci::gl::color(ci::Color("green"));
    ci::gl::drawSolidCircle(vec2(START_POSITION + THRESHOLD * 5, color_y), 20);
    ci::gl::color(ci::Color("black"));
    ci::gl::drawSolidCircle(vec2(START_POSITION + THRESHOLD * 6, color_y), 20);
}

ci::Surface Painter::DrawLine(ci::Surface &bitmap, glm::vec2 position, int size, int colour) {
    int x = position.x;
    int y = position.y;
    // Iterate current point with given size and color.
    ci::Area area(x, y, x + size, y + size);
    ci::Surface::Iter iter = bitmap.getIter(area);
    while (iter.line()) {
        while (iter.pixel()) {
            switch (colour) {
                case 1:
                    // Purple
                    iter.r() = 250;
                    iter.b() = 250;
                    iter.g() = 0;
                    break;
                case 2:
                    // Yellow
                    iter.b() = 0;
                    iter.r() = 250;
                    iter.g() = 250;
                    break;
                case 3:
                    // Green
                    iter.r() = 0;
                    iter.b() = 250;
                    iter.g() = 250;
                    break;
                case 4:
                    // Red
                    iter.r() = 250;
                    iter.b() = 0;
                    iter.g() = 0;
                    break;
                case 5:
                    // Blue
                    iter.r() = 0;
                    iter.b() = 250;
                    iter.g() = 0;
                    break;
                case 6:
                    // Green
                    iter.r() = 0;
                    iter.b() = 0;
                    iter.g() = 250;
                    break;
                case 7:
                    // Black
                    iter.r() = 1;
                    iter.b() = 1;
                    iter.g() = 1;
                    break;
            }
        }
    }
    return bitmap;
}
} // namespace photos