// Includes
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>
#include "XPLMDisplay.h"
#include "XPLMUtilities.h"
#include "XPLMPlugin.h"

// Error if compiling with wrong SDK
#ifndef XPLM300
    #error This is made to be compiled against the XPLM300 SDK
#endif

// Namespaces
using namespace std;
using namespace std::filesystem;
using std::filesystem::current_path;

// Callbacks.
PLUGIN_API int XPluginStart(char* plugin_name, char* plugin_signature, char* plugin_description) {
    strcpy(plugin_name, "BackgroundRandomizer");
    strcpy(plugin_signature, "simsolutions.BackgroundRandomizer");
    strcpy(plugin_description, "BackgroundRandomizer changes the background image of X-Plane's menus. Each background is randomly chosen at the previous startup.");
    return 1;
}
PLUGIN_API void	XPluginStop(void) { }
PLUGIN_API void XPluginDisable(void) { }
PLUGIN_API int  XPluginEnable(void) { 
    try {
        XPLMDebugString("<BackgroundRandomizer> Starting...\n");

        // Define variables
        path backgroundsFolder = current_path() += "/Resources/plugins/BackgroundRandomizer/Images";
        vector<path> backgroundList;

        // Get list of backgrounds
        for (const auto& entry : directory_iterator(backgroundsFolder)) {
            backgroundList.push_back(entry.path());
        }

        // Get random number that corresponds to a background.
        srand(time(NULL));
        int randNumber = rand() % backgroundList.size();

        // Figure out our destination path & background path.
        path backgroundPath = backgroundList.at(randNumber);
        path destPath = current_path() += "/Resources/bitmaps/interface11/image_background_screenshot_for_stack.png";

        // Copy over the new background.
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
