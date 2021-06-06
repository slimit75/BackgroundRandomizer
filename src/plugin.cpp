// Includes
#include <string>
#include <fstream>
#include <filesystem>
#include <cmath>
#include "XPLMDisplay.h"
#include "XPLMUtilities.h"
#include "XPLMPlugin.h"

#if IBM
    #include <windows.h>
#endif
#if LIN
    #include <GL/gl.h>
#elif __GNUC__
    #include <OpenGL/gl.h>
#else
    #include <GL/gl.h>
#endif

// Error if compiling with wrong SDK
#ifndef XPLM300
    #error This is made to be compiled against the XPLM300 SDK
#endif

// Namespaces
using namespace std;
using namespace std::filesystem;
using std::filesystem::current_path;

PLUGIN_API int XPluginStart(char* plugin_name, char* plugin_signature, char* plugin_description) {
    XPLMDebugString("<BackgroundRandomizer> Starting v2.0\n");
    try {
        strcpy(plugin_name, "BackgroundRandomizer");
        strcpy(plugin_signature, "simsolutions.BackgroundRandomizer");
        strcpy(plugin_description, "BackgroundRandomizer changes the background image of X-Plane's menus.");
    }
    catch (exception& e) {
        XPLMDebugString("<BackgroundRandomizer> ERROR: ");
        XPLMDebugString(e.what());
        XPLMDebugString("\n");
    }
    return 1;
}

PLUGIN_API void	XPluginStop(void) { }
PLUGIN_API void XPluginDisable(void) { }

PLUGIN_API int  XPluginEnable(void) { 
    try {
        path backgroundsFolder = current_path() += "/Resources/plugins/BackgroundRandomizer/Images";
        path backgrounds[100];

        int i = 0;

        for (const auto& entry : directory_iterator(backgroundsFolder)) {
            backgrounds[i] = entry.path();
            i = i + 1;
        }

        srand((unsigned)time(NULL));

        int selectedBackground = rand() % i + 1;

        path backgroundPath = backgrounds[selectedBackground];
        path destPath = current_path() += "/Resources/bitmaps/interface11/image_background_screenshot_for_stack.png";

        remove(destPath);
        copy(backgroundPath, destPath, copy_options::update_existing);
        XPLMDebugString("<BackgroundRandomizer> Background successfully set.\n");
    }
    catch (exception& e) {
        XPLMDebugString("<BackgroundRandomizer> ERROR: ");
        XPLMDebugString(e.what());
        XPLMDebugString("\n");
    }
    return 1; 
}
PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFrom, int inMsg, void* inParam) { }
