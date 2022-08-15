#include "interface.h"

namespace photos {

using namespace ci;
using namespace ci::app;

void PhotoApp::setup() {
    ci::app::setWindowSize(kWindowSize, 800);
    auto img = loadImage(loadAsset( "cover.jpg" ));
    // reference: https://mottosso.gitbooks.io/cinder/content/book/cinder/Surface.html
    Surface bitmap(img);
    bitmap_ = bitmap;
    last_bitmap_ = bitmap;
    original_bitmap_ = bitmap;
    mTex_ = gl::Texture2d::create(bitmap);
    // All modes
    painter_ = photos::Painter();
    editor_ = photos::Editor();
    creator_ = photos::Creator();
}

void PhotoApp::draw() {
    // Button return to main menu
    ci::gl::clear("grey");
    ci::gl::color(ci::Color("black"));
    ci::gl::drawSolidRect(ci::Rectf(vec2(RETURN_BUTTON_X_START, RETURN_BUTTON_Y_START),
                                    vec2(RETURN_BUTTON_X_END, RETURN_BUTTON_Y_END)));
    ci::gl::drawStringCentered("Back to Main", vec2((RETURN_BUTTON_X_START + RETURN_BUTTON_X_END) / 2,
                                                    (RETURN_BUTTON_Y_START + RETURN_BUTTON_Y_END) / 2),
                               ci::Color("white"));
    ci::gl::color(ci::Color("white"));
    gl::draw(mTex_);
    if (mode_ == 0) {
        // Main menu
        DisplayMain();
    } else if (mode_ == 1) {
        // Editor mode
        editor_.Display(button_position1_, button_position2_, button_position3_, button_position4_, return_flag_);
    } else if (mode_ == 2) {
        // Paint mode
        painter_.Display(SIZE_ADJUSTMENT_Y, COLOR_ADJUSTMENT_Y);
    } else {
        // Creator mode
        creator_.Display();
    }
}

void PhotoApp::DisplayMain() {
    ci::gl::color(ci::Color("white"));
    gl::draw(mTex_);
    ci::gl::color(ci::Color("black"));
    // Buttons in main
    ci::gl::drawSolidRect(ci::Rectf(vec2(MENU_START_X, MENU_START_Y - MENU_HEIGHT * 1.5),
                                    vec2(MENU_END_X, MENU_START_Y- MENU_HEIGHT)));
    ci::gl::drawSolidRect(ci::Rectf(vec2(MENU_START_X, MENU_START_Y),
                                    vec2(MENU_END_X, MENU_START_Y + MENU_HEIGHT)));
    ci::gl::drawSolidRect(ci::Rectf(vec2(MENU_START_X, MENU_START_Y + MENU_HEIGHT * 2),
                                    vec2(MENU_END_X, MENU_START_Y + MENU_HEIGHT * 3)));
    ci::gl::drawSolidRect(ci::Rectf(vec2(MENU_START_X, MENU_START_Y + MENU_HEIGHT * 4),
                                    vec2(MENU_END_X, MENU_START_Y + MENU_HEIGHT * 5)));
    // Words on buttons
    ci::Font font = ci::Font("Arial Black", 40);
    ci::Font font_small = ci::Font("Arial Black", 30);
    ci::Color color = ci::Color("lightpink");
    ci::gl::drawStringCentered("Mode:", vec2(MENU_MID_X, 120),
                               ci::Color("white"), font_small );
    ci::gl::drawStringCentered("New Photo", vec2(MENU_MID_X, MENU_START_Y - MENU_HEIGHT * 2.5 / 2 - 10),
                               color, font_small );
    ci::gl::drawStringCentered("Editor", vec2(MENU_MID_X, MENU_START_Y + MENU_HEIGHT / 2 - 10),
                               color, font);
    ci::gl::drawStringCentered("Painter", vec2(MENU_MID_X, MENU_START_Y + MENU_HEIGHT * 5 / 2 - 10),
                               color, font);
    ci::gl::drawStringCentered("Creative", vec2(MENU_MID_X, MENU_START_Y + MENU_HEIGHT * 9 / 2 - 10),
                               color, font);
}

void PhotoApp::SelectBrush(int x, int y) {
    if (y >= COLOR_ADJUSTMENT_Y - COLOR_THRESHOLD && y <= COLOR_ADJUSTMENT_Y + COLOR_THRESHOLD
        && x >= COLOR_START && x <= COLOR_END) {
        // Find position to adjust color
        color_ = (int)((x - COLOR_START) / COLOR_WIDTH + 1);
    } else if (y >= SIZE_ADJUSTMENT_Y - COLOR_THRESHOLD && y <= SIZE_ADJUSTMENT_Y + COLOR_THRESHOLD
               && x >= COLOR_START && x <= COLOR_END) {
        // Find position to adjust size
        size_ = (int) ((x - COLOR_START) / COLOR_WIDTH) * 2.5 + 5;
    }
}

void PhotoApp::SelectMain(int x, int y) {
    if (x >= MENU_START_X && x <= MENU_END_X) {
        // New photo create
        if (y >= MENU_START_Y - MENU_HEIGHT * 1.5 && y <= MENU_START_Y - MENU_HEIGHT) {
            // Read Next Image
            auto img = loadImage(loadAsset( all_images_[current_image_]));
            if (current_image_ < 2) {
                current_image_ += 1;
            } else {
                current_image_ = 0;
            }
            // Open new graph to surface
            Surface bitmap(img);
            bitmap_ = bitmap;
            original_bitmap_ = bitmap_;
            mTex_ = gl::Texture2d::create(bitmap);
            // Buttons should return to their normal positions
            return_flag_ = true;
        } else if (y >= MENU_START_Y && y <= MENU_START_Y + MENU_HEIGHT) {
            mode_ = 1;
        } else if (y >= MENU_START_Y + MENU_HEIGHT * 2 && y <= MENU_START_Y + MENU_HEIGHT  * 3) {
            mode_ = 2;
        } else if (y >= MENU_START_Y + MENU_HEIGHT * 4  && y <= MENU_START_Y + MENU_HEIGHT * 5) {
            mode_ = 3;
        }
    }
}

bool PhotoApp::SelectCreatorMode(int x, int y) {
    if (x >= MENU_START_X && x <= MENU_END_X) {
        if (y >= MENU_START_Y && y <= MENU_START_Y + MENU_HEIGHT) {
            reverse_flag_ = true;
            mosaic_flag_ = false;
            random_flag_ = false;
        } else if (y >= MENU_START_Y + MENU_HEIGHT * 2 && y <= MENU_START_Y + MENU_HEIGHT  * 3) {
            reverse_flag_ = false;
            mosaic_flag_ = true;
            random_flag_ = false;
        } else if (y >= MENU_START_Y + MENU_HEIGHT * 4  && y <= MENU_START_Y + MENU_HEIGHT * 5) {
            reverse_flag_ = false;
            mosaic_flag_ = false;
            random_flag_ = true;
        }
        return true;
    }
    // If within the range, return false to indicate that there is no other modfiction needs
    return false;
}

void PhotoApp::update() {
    gl::draw(mTex_);
}

void PhotoApp::keyDown(ci::app::KeyEvent event) {
    if (event.getCode() == KeyEvent::KEY_LEFT){
        // Clear current photo
        last_bitmap_ = bitmap_;
        bitmap_ = original_bitmap_;
        mTex_ = gl::Texture2d::create(bitmap_);
        return_flag_ = true;
    } else if (event.getChar() == 'w'){
        // Change photo
        auto img = loadImage(loadAsset( "white.jpg" ));
        Surface bitmap(img);
        bitmap_ = bitmap;
        mTex_ = gl::Texture2d::create(bitmap);
    } else if (event.getChar() == 'z' && event.isControlDown()){
        // Control-z photo
        bitmap_ = last_bitmap_;
        mTex_ = gl::Texture2d::create(last_bitmap_);
    } else if (event.getChar() == 's' && event.isControlDown()){
        // Save photo
        writeImage( "new_image.png", bitmap_);
    }
}

void PhotoApp::mouseDown(ci::app::MouseEvent event) {
    return_flag_ = false;
    int x = event.getPos()[0];
    int y = event.getPos()[1];
    // Check 'Return' button
    if (x >= RETURN_BUTTON_X_START && x <= RETURN_BUTTON_X_END
            && y >= RETURN_BUTTON_Y_START && y <= RETURN_BUTTON_Y_END) {
        mode_ = 0;
        reverse_flag_ = false;
        mosaic_flag_ = false;
        random_flag_ = false;
        return;
    }
    if (mode_ == 0) {
        // Call main menu selection
        SelectMain(x, y);
    } else if (mode_ == 1) {
        // Call editor mode selection
        if (x > bitmap_.getWidth()) {
            last_bitmap_ = bitmap_;
            editor_.ChangeSelection(x, y, bitmap_, button_position1_, button_position2_,
                                    button_position3_, button_position4_);
            mTex_ = gl::Texture2d::create(bitmap_);
        }
    } else if (mode_ == 2) {
        // Call brush mode selection
        SelectBrush(x, y);
    } else {
        // Call creator mode selection
        if (!SelectCreatorMode(x, y)) {
            last_bitmap_ = bitmap_;
            creator_.CreateEffects(x, y, bitmap_, reverse_flag_,
                                   mosaic_flag_, random_flag_);
            mTex_ = gl::Texture2d::create(bitmap_);
        }
    }
}

void PhotoApp::mouseDrag(ci::app::MouseEvent event) {
    vec2 position = event.getPos();
    last_bitmap_ = bitmap_;
    if (mode_ == 2) {
        // Case for painting
        painter_.DrawLine(bitmap_, position, size_, color_);
        mTex_ = gl::Texture2d::create(bitmap_);
    } else if (mode_ == 3 && mosaic_flag_) {
        // Case for mosaic
        creator_.CreateEffects(event.getPos().x, event.getPos().y, bitmap_,
                               reverse_flag_, mosaic_flag_, random_flag_);
        mTex_ = gl::Texture2d::create(bitmap_);
    }
}
}  // namespace photos
