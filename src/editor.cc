#include "editor.h"

namespace photos {

using glm::vec2;
using namespace ci;

void Editor::Display(vec2& button_position1, vec2& button_position2, vec2& button_position3,
                     vec2& button_position4, bool clear) {
    // Default button and adjustment range
    ci::gl::color(ci::Color("lightpink"));
    ci::gl::drawString("Saturation ", vec2(START_X, START_Y));
    ci::gl::drawSolidRect(ci::Rectf(vec2(START_X, INTERVAL_Y),
                                    vec2(END_X, INTERVAL_Y + THRESHOLD_WIDE)));
    ci::gl::drawString("Darkness ", vec2(START_X, START_Y + INTERVAL_Y));
    ci::gl::drawSolidRect(ci::Rectf(vec2(START_X, INTERVAL_Y * 2),
                                    vec2(END_X, INTERVAL_Y * 2 + THRESHOLD_WIDE)));
    ci::gl::drawString("Redness ", vec2(START_X, START_Y + INTERVAL_Y * 2));
    ci::gl::drawSolidRect(ci::Rectf(vec2(START_X, INTERVAL_Y * 3),
                                    vec2(END_X, INTERVAL_Y * 3 + THRESHOLD_WIDE)));
    ci::gl::drawString("Blueness ", vec2(START_X, START_Y + INTERVAL_Y * 3));
    ci::gl::drawSolidRect(ci::Rectf(vec2(START_X, INTERVAL_Y * 4),
                                    vec2(END_X, INTERVAL_Y * 4 + THRESHOLD_WIDE)));
    // If control-z is pressed, return to default
    if (clear) {
        button_position1 = DEFAULT_POSITION1;
        button_position2 = DEFAULT_POSITION2;
        button_position3 = DEFAULT_POSITION3;
        button_position4 = DEFAULT_POSITION4;
    }
    // Draw buttons
    ci::gl::drawSolidCircle(button_position1, BUTTON_RADIUS);
    ci::gl::drawSolidCircle(button_position2, BUTTON_RADIUS);
    ci::gl::drawSolidCircle(button_position3, BUTTON_RADIUS);
    ci::gl::drawSolidCircle(button_position4, BUTTON_RADIUS);
}

ci::Surface& Editor::ChangeSaturation(double degree, ci::Surface& bitmap) {
    // Change the difference between largest and smallest
    Area area(0, 0, bitmap.getWidth(), bitmap.getHeight());
    Surface::Iter iter = bitmap.getIter(area);
    while (iter.line()) {
        while (iter.pixel()) {
            // Needs to iterate through all cases
            if (iter.r() <= iter.g()) {
                if (iter.g() <= iter.b()) {
                    // If exceeds limit, keep original
                    if ((iter.b() + degree) >= COLOR_MAX || (iter.r() - degree) <= 0) {
                        continue;
                    }
                    iter.b() += degree;
                    iter.r() -= degree;
                } else {
                    if (iter.r() <= iter.b()) {
                        if ((iter.g() + degree) >= COLOR_MAX || (iter.r() - degree) <= COLOR_MIN) {
                            continue;
                        }
                        iter.g() += degree;
                        iter.r() -= degree;
                    } else {
                        if ((iter.g() + degree) >= COLOR_MAX || (iter.b() - degree) <= COLOR_MIN) {
                            continue;
                        }
                        iter.g() += degree;
                        iter.b() -= degree;
                    }
                }
            } else {
                if (iter.r() <= iter.b()) {
                    if ((iter.b() + degree) >= COLOR_MAX || (iter.g() - degree) <= COLOR_MIN) {
                        continue;
                    }
                    iter.b() += degree;
                    iter.g() -= degree;
                } else {
                    if (iter.b() <= iter.g()) {
                        if ((iter.r() + degree) >= COLOR_MAX || (iter.b() - degree) <= COLOR_MIN) {
                            continue;
                        }
                        iter.r() += degree;
                        iter.b() -= degree;
                    } else {
                        if ((iter.r() + degree) >= COLOR_MAX || (iter.g() - degree) <= COLOR_MIN) {
                            continue;
                        }
                        iter.r() += degree;
                        iter.g() -= degree;
                    }
                }
            }
        }
    }
    return bitmap;
}

ci::Surface& Editor::ChangeRedness(double degree, ci::Surface& bitmap) {
    Area area(0, 0, bitmap.getWidth(), bitmap.getHeight());
    Surface::Iter iter = bitmap.getIter(area);
    while (iter.line()) {
        while (iter.pixel()) {
            // Increasing redness by degree
            if ((iter.r() + degree) >= COLOR_MAX) {
                iter.r() = COLOR_MAX;
            } else if ((iter.r() + degree) <= COLOR_MIN) {
                iter.r() = COLOR_MIN;
            } else {
                iter.r() += degree;
            }
        }
    }
    return bitmap;
}

ci::Surface& Editor::ChangeBlueness(double degree, ci::Surface& bitmap) {
    Area area(0, 0, bitmap.getWidth(), bitmap.getHeight());
    Surface::Iter iter = bitmap.getIter(area);
    while (iter.line()) {
        while (iter.pixel()) {
            // Increasing blueness by degree
            if ((iter.b() + degree) >= COLOR_MAX) {
                iter.b() = COLOR_MAX;
            } else if ((iter.b() + degree) <= COLOR_MIN) {
                iter.b() = COLOR_MIN;
            } else {
                iter.b() += degree;
            }
        }
    }
    return bitmap;
}

ci::Surface& Editor::ChangeDarkness(double degree, ci::Surface& bitmap) {
    Area area(0, 0, bitmap.getWidth(), bitmap.getHeight());
    Surface::Iter iter = bitmap.getIter(area);
    // Multiply degree to the original rgb
    while (iter.line()) {
        while (iter.pixel()) {
            // If in left direction, it means increasing lightness. use * instead of /
            if (degree <= 0) {
                iter.r() *= (-degree);
                iter.g() *= (-degree);
                iter.b() *= (-degree);
            } else {
                iter.r() /= degree;
                iter.g() /= degree;
                iter.b() /= degree;
            }
            if (iter.r() <= COLOR_MIN) {
                iter.r() = COLOR_MIN;
            }
            if (iter.g() <= COLOR_MIN) {
                iter.g() = COLOR_MIN;
            }
            if (iter.b() <= COLOR_MIN) {
                iter.b() = COLOR_MIN;
            }
            if (iter.r() >= COLOR_MAX) {
                iter.r() = COLOR_MAX;
            }
            if (iter.g() >= COLOR_MAX) {
                iter.g() = COLOR_MAX;
            }
            if (iter.b() >= COLOR_MAX) {
                iter.b() = COLOR_MAX;
            }
        }
    }
    return bitmap;
}

void Editor::ChangeSelection(int x, int y, ci::Surface& bitmap, vec2& button_position1, vec2& button_position2,
                             vec2& button_position3, vec2& button_position4) {
    if (y <= START_BUTTON + WIDE_HALF) {
        // Change saturation
        double degree = (x - button_position1.x) / DEGREE_THRESHOLD_LARGE;
        ChangeSaturation(degree, bitmap);
        button_position1 = vec2(x, START_BUTTON + MID_THRESHOLD);
    } else if (y >= START_BUTTON * 2 - WIDE_HALF && y <= START_BUTTON * 2 + WIDE_HALF) {
        // change darkness
        double degree = (x - button_position2.x) / DEGREE_THRESHOLD_LARGE;
        ChangeDarkness(degree, bitmap);
        button_position2 = vec2(x, START_BUTTON * 2 + MID_THRESHOLD);
    } else if (y >= START_BUTTON * 3 - WIDE_HALF && y <= START_BUTTON * 3 + WIDE_HALF) {
        // Change redness
        double degree = (x - button_position3.x) / DEGREE_THRESHOLD_MIN;
        ChangeRedness(degree, bitmap);
        button_position3 = vec2(x, START_BUTTON * 3 + MID_THRESHOLD);
    } else if  (y >= START_BUTTON * 4 - WIDE_HALF && y <= START_BUTTON * 4 + WIDE_HALF) {
        // Change blueness
        double degree = (x - button_position4.x) / DEGREE_THRESHOLD_MIN;
        ChangeBlueness(degree, bitmap);
        button_position4 = vec2(x, START_BUTTON * 4 + MID_THRESHOLD);
    }
}
}  // namespace photos
