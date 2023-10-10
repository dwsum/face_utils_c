#include <iostream>
#include "AppUtils/App.h"

// main() is where program execution begins.
int main() {

    //Initial appHelper class
    App appHelper;

    //Start video capture service
    appHelper.Capture();
    return 0;
}