#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <painter.h>

using photos::Painter;
using namespace ci;
using namespace ci::app;

TEST_CASE("Test Painter") {
    SECTION("Painter color test purple") {
        auto img = loadImage(loadAsset( "white.jpg" ));
        // reference: https://mottosso.gitbooks.io/cinder/content/book/cinder/Surface.html
        Surface bitmap(img);
        Painter painter;
        Surface new_map = painter.DrawLine(bitmap, glm::vec2(100.0, 100.0), 5, 2);
        ci::Area area(100.0, 100.0, 105.0, 105.0);
        ci::Surface::Iter iter = bitmap.getIter(area);
        bool flag = true;
        while (iter.line()) {
            while (iter.pixel()) {
                if (iter.r() != 250 || iter.b() != 250 || iter.g() != 0) {
                    flag = false;
                }
            }
        }
        REQUIRE(flag == true);
    }

    SECTION("Painter color test black") {
        auto img = loadImage(loadAsset( "white.jpg" ));
        // reference: https://mottosso.gitbooks.io/cinder/content/book/cinder/Surface.html
        Surface bitmap(img);
        Painter painter;
        Surface new_map = painter.DrawLine(bitmap, glm::vec2(10.0, 20.0), 10, 7);
        ci::Area area(10, 20, 20, 30.0);
        ci::Surface::Iter iter = bitmap.getIter(area);
        bool flag = true;
        while (iter.line()) {
            while (iter.pixel()) {
                if (iter.r() != 1 || iter.b() != 1 || iter.g() != 1) {
                    flag = false;
                }
            }
        }
        REQUIRE(flag == true);
    }
}

