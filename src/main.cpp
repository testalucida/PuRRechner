#include <FL/Fl.H>

#include "Application.h"

int main() {
    Application app;
    app.init();
    app.getWindow().show();
    return Fl::run();
}
