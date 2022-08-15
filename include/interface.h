#include "painter.h"
#include "creator.h"
#include "editor.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"

namespace photos {

/**
 * An app for process photos.
 */
class PhotoApp : public ci::app::App {
 public:
    void setup() override;
    void draw() override;
    void update() override;
    void mouseDown(ci::app::MouseEvent event) override;
    void mouseDrag(ci::app::MouseEvent event) override;
    void keyDown(ci::app::KeyEvent event) override;
    const int kWindowSize = 1500;
    const int kMargin = 100;
 private:
    // The current mode of our app: 0 for main menu, 1 for photo editor, 2 for painter, 3 for creative
    int mode_ = 0;

    // Image list and index
    std::string all_images_[3] = {"image1.jpeg", "image2.png", "image3.jpg"};
    int current_image_ = 0;

    // Variables for current image
    ci::Surface bitmap_;
    ci::Surface last_bitmap_;
    ci::Surface original_bitmap_;
    ci::gl::Texture2dRef mTex_;
    bool return_flag_ = false;

    // Button position in editor mode
    vec2 button_position1_ = vec2(1100,100);
    vec2 button_position2_ = vec2(1100,200);
    vec2 button_position3_ = vec2(1100,300);
    vec2 button_position4_ = vec2(1100,400);

    // Color and size in painter mode
    int color_ = 1;
    int size_ = 10;
    int SIZE_ADJUSTMENT_Y = 600;
    int COLOR_ADJUSTMENT_Y = 700;
    int COLOR_START = 1080;
    int COLOR_END = 1420;
    int COLOR_THRESHOLD = 20;
    int COLOR_WIDTH = 50;

    // Position of mode selection in main menu
    int MENU_START_X = 1100;
    int MENU_MID_X = 1200;
    int MENU_END_X = 1300;
    int MENU_START_Y = 200;
    int MENU_HEIGHT = 100;

    // Position of return to main button
    int RETURN_BUTTON_X_START = 1400;
    int RETURN_BUTTON_X_END = 1500;
    int RETURN_BUTTON_Y_START = 760;
    int RETURN_BUTTON_Y_END = 800;

    // Flags for random mode
    bool reverse_flag_ = false;
    bool mosaic_flag_ = false;
    bool random_flag_ = false;

    // Editor classes
    Painter painter_;
    Editor editor_;
    Creator creator_;

    // Display main menu
    void DisplayMain();

    // Implement the selection functions in main menu
    void SelectMain(int x, int y);

    // Implement the selections in paint mode
    void SelectBrush(int x, int y);

    // Implement the selection of creative mode
    bool SelectCreatorMode(int x, int y);
};
}  // namespace idealgas
