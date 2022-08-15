#include "cinder/gl/gl.h"

using glm::vec2;

namespace photos {

/**
 * This class is used to present filtered graph.
 */
class Editor {
 public:
    // This function is used to set the display in interface with given position of buttons.
    void Display(vec2& button_position1, vec2& button_position2, vec2& button_position3,
                 vec2& button_position4, bool clear);

    /**
     * This function is used to change the surface with the new button positions.
     * @param x mouse x position
     * @param y mouse y position
     * @param bitmap Surface of graph
     * @param button_position1 position of first button
     * @param button_position2 position of second button
     * @param button_position3 position of third button
     * @param button_position4 position of fourth button
     */
    void ChangeSelection(int x, int y, ci::Surface& bitmap, vec2& button_position1, vec2& button_position2,
                         vec2& button_position3, vec2& button_position4);

    /**
     * This function is used to change the saturation with the degree given.
     * @param degree a value represents the extend to change
     * @param bitmap Surface of graph
     * @return New resulting surface
     */
    ci::Surface& ChangeSaturation(double degree, ci::Surface& bitmap);

    /**
     * This function is used to change the darkness with the degree given.
     * @param degree a value represents the extend to change
     * @param bitmap Surface of graph
     * @return New resulting surface
     */
    ci::Surface& ChangeDarkness(double degree, ci::Surface& bitmap);

    /**
     * This function is used to change the saturation with the degree given.
     * @param degree a value represents the extend to change
     * @param bitmap Surface of graph
     * @return New resulting surface
     */
    ci::Surface& ChangeRedness(double degree, ci::Surface& bitmap);

    /**
     * This function is used to change the bluness with the degree given.
     * @param degree a value represents the extend to change
     * @param bitmap Surface of graph
     * @return New resulting surface
     */
    ci::Surface& ChangeBlueness(double degree, ci::Surface& bitmap);

 private:
    // Default button positions
    vec2 DEFAULT_POSITION1 = vec2(1100,100);
    vec2 DEFAULT_POSITION2 = vec2(1100,200);
    vec2 DEFAULT_POSITION3 = vec2(1100,300);
    vec2 DEFAULT_POSITION4 = vec2(1100,400);
    int BUTTON_RADIUS = 10;
    // Adjustment range settings
    int START_X = 1100;
    int END_X = 1300;
    int START_Y = 70;
    int INTERVAL_Y = 100;
    int THRESHOLD_WIDE = 5;
    int START_BUTTON = 100;
    int WIDE_HALF = 50;
    double MID_THRESHOLD = 2.5;
    // Color range max and min in cinder system
    int COLOR_MAX = 255;
    int COLOR_MIN = 0;
    // Degree threshold for filters
    int DEGREE_THRESHOLD_LARGE = 20;
    int DEGREE_THRESHOLD_MIN = 2;
};
}  // namespace idealgas
