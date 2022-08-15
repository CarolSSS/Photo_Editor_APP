#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/Surface.h"

using glm::vec2;

namespace photos {

/**
 * This class is used to create creative effects to the graph.
 */
class Creator {
 public:
    /**
     * This function is used to setup the display in interface.
     */
    void Display();
    /**
     * This function is used for creators to create creative effects.
     * @param x x position
     * @param y y position
     * @param bitmap Surface of graph
     * @param reverse_flag flag to generate reverse effects
     * @param mosaic_flag flag to generate mosaic effects
     * @param random_flag flag to generate random effects
     */
    void CreateEffects(int x, int y, ci::Surface& bitmap,
                       bool reverse_flag, bool mosaic_flag, bool random_flag);
    /**
     * This function is used to create random effects on the given graph.
     * @param area The area to edit
     * @param bitmap Surface of graph
     * @param random_number random number by time to create effects
     */
    void GenerateRandom(ci::Area area, ci::Surface& bitmap, int random_number);
    /**
     * This function is used to create mosaic effects on the given graph.
     * @param area The area to edit
     * @param bitmap Surface of graph
     */
    void GenerateMosaic(ci::Area area, ci::Surface& bitmap);

 private:
    // Position for the mode buttons
    int MENU_START_X = 1100;
    int MENU_MID_X = 1200;
    int MENU_END_X = 1300;
    int MENU_START_Y = 200;
    int MENU_HEIGHT = 100;
    // Size of Mosaic
    int MOSAIC_THRESHOLD = 20;
};
}  // namespace idealgas
