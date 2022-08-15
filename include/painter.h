#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/Surface.h"

namespace photos {

class Painter {
    public:
        /**
         * This function is used to setup the display in interface with given position of size and color.
         * @param size_y size position of brush
         * @param color_y color position of brush
         */
        void Display(int size_y, int color_y);

        /**
         * This function is used to draw lines with given position and size and color
         * @param bitmap The surface of graph
         * @param position Center position to draw
         * @param size size of brush
         * @param color color of brush
         * @return The surface after modification
         */
        ci::Surface DrawLine(ci::Surface &bitmap, glm::vec2 position, int size, int color);
    private:
        // Position variables for display
        int START_POSITION = 1100;
        int THRESHOLD = 50;
};
}


