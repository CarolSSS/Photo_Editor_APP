#include "interface.h"

using photos::PhotoApp;

void prepareSettings(PhotoApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(PhotoApp, ci::app::RendererGl, prepareSettings);
