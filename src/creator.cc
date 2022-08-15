#include "creator.h"

namespace photos {

using glm::vec2;
using namespace ci;

void Creator::Display() {
    // Buttons
    ci::gl::color(ci::Color("black"));
    ci::gl::drawSolidRect(ci::Rectf(vec2(MENU_START_X, MENU_START_Y),
                                    vec2(MENU_END_X, MENU_START_Y + MENU_HEIGHT)));
    ci::gl::drawSolidRect(ci::Rectf(vec2(MENU_START_X, MENU_START_Y + MENU_HEIGHT * 2),
                                    vec2(MENU_END_X, MENU_START_Y + MENU_HEIGHT * 3)));
    ci::gl::drawSolidRect(ci::Rectf(vec2(MENU_START_X, MENU_START_Y + MENU_HEIGHT * 4),
                                    vec2(MENU_END_X, MENU_START_Y + MENU_HEIGHT * 5)));
    // Words
    ci::Font font = ci::Font("Arial Black", 40);
    ci::Color color = ci::Color("lightpink");
    ci::gl::drawStringCentered("Reverse", vec2(MENU_MID_X, MENU_START_Y + MENU_HEIGHT / 2 - 10),
                               color, font);
    ci::gl::drawStringCentered("Mosaic", vec2(MENU_MID_X, MENU_START_Y + MENU_HEIGHT * 5 / 2 - 10),
                               color, font);
    ci::gl::drawStringCentered("Random", vec2(MENU_MID_X, MENU_START_Y + MENU_HEIGHT * 9 / 2 - 10),
                               color, font);
}

void Creator::GenerateMosaic(Area area, ci::Surface& bitmap) {
    Surface::Iter iter = bitmap.getIter(area);
    // Find sum of rgb of all the pixel in the selected area
    int r_total = 0;
    int g_total = 0;
    int b_total = 0;
    while (iter.line()) {
        while (iter.pixel()) {
            r_total += iter.r();
            g_total += iter.g();
            b_total += iter.b();
        }
    }
    // Calculate mean
    double new_r = r_total / (MOSAIC_THRESHOLD * MOSAIC_THRESHOLD * 4);
    double new_g = g_total / (MOSAIC_THRESHOLD * MOSAIC_THRESHOLD * 4);
    double new_b = b_total / (MOSAIC_THRESHOLD * MOSAIC_THRESHOLD * 4);
    // Reiterate to change pixel rgb values to the mean
    Surface::Iter iter_change = bitmap.getIter(area);
    while (iter_change.line()) {
        while (iter_change.pixel()) {
            iter_change.r() = new_r;
            iter_change.g() = new_g;
            iter_change.b() = new_b;
        }
    }
}

void Creator::GenerateRandom(Area area, ci::Surface& bitmap, int random_number) {
    Surface::Iter iter = bitmap.getIter(area);
    while (iter.line()) {
        while (iter.pixel()) {
            // Modify one of the three r/g/b
            if (random_number % 3 == 0) {
                iter.r() += iter.r() + random_number % 30;
            } else if (random_number % 3 == 1) {
                iter.g() += iter.g() + random_number % 30;
            } else {
                iter.b() += iter.b() + random_number % 30;
            }
        }
    }
}

void Creator::CreateEffects(int x, int y, ci::Surface& bitmap,
                            bool reverse_flag, bool mosaic_flag, bool random_flag) {
    if (reverse_flag) {
        Area area(0, 0, x, y);
        Surface::Iter iter = bitmap.getIter(area);
        while (iter.line()) {
            while (iter.pixel()) {
                // Create reverse effect by calculating 100 - pixel
                iter.r() = 100 - iter.r();
                iter.g() = 100 - iter.g();
                iter.b() = 100 - iter.b();
            }
        }
    } else if (mosaic_flag) {
        Area area(x - MOSAIC_THRESHOLD, y - MOSAIC_THRESHOLD,
                  x + MOSAIC_THRESHOLD, y + MOSAIC_THRESHOLD);
        GenerateMosaic(area, bitmap);
    } else if (random_flag) {
        // reference: https://www.tutorialspoint.com/c_standard_library/c_function_rand.htm
        // Using random to generate effects
        time_t t;
        srand((unsigned) time(&t));
        int random_number = rand();
        Area area(rand() % MENU_START_Y, rand() % MENU_START_Y,random_number % MENU_MID_X + MENU_START_Y,
                  random_number % MENU_MID_X + MENU_START_Y);
        GenerateRandom(area, bitmap, random_number);
    }
}
}  // namespace photos
