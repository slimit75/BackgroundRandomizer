// Includes
#include <XPLMDisplay.h>
#include <XPLMUtilities.h>
#include <XPLMPlugin.h>

#include <string>
#include <fstream>
#include <filesystem>
#include <vector>
#include <cstring>

// Variables
char xpPath[512];
std::string backgroundsFolder;
std::string destinationPath;
std::string relativeImagesDirectory = "/Resources/plugins/BackgroundRandomizer/images";
std::string relativeDestinationPath = "/Resources/bitmaps/interface11/image_background_screenshot_for_stack.png";
std::filesystem::path backgroundPath;
std::vector<std::filesystem::path> backgroundList;

// Callbacks.
PLUGIN_API int XPluginStart(char* plugin_name, char* plugin_signature, char* plugin_description) {
    strcpy(plugin_name, "BackgroundRandomizer");
    strcpy(plugin_signature, "slimit75.BackgroundRandomizer");
    strcpy(plugin_description, "BackgroundRandomizer changes the background image of X-Plane's menus. Each background is randomly chosen at the previous startup.");
    
    XPLMEnableFeature("XPLM_USE_NATIVE_PATHS", 1);
    XPLMGetSystemPath(xpPath);

    backgroundsFolder = xpPath + relativeImagesDirectory;
    destinationPath = xpPath + relativeDestinationPath;

    XPLMDebugString("[BackgroundRandomizer] Finding new background...\n");
    try {
        // Get list of available backgrounds
        for (const auto& entry : std::filesystem::directory_iterator(backgroundsFolder)) {
            backgroundList.push_back(entry.path());
        }

        // Figure out the new background
        srand(time(NULL));
        int randNumber = rand() % backgroundList.size();
        backgroundPath = backgroundList.at(randNumber); 

        // Copy over new background to the existing background
        std::filesystem::remove(destinationPath);
        std::filesystem::copy(backgroundPath, destinationPath, std::filesystem::copy_options::update_existing);
        XPLMDebugString("[BackgroundRandomizer] Background successfully set.\n");
    }
    catch (std::exception& e) {
        XPLMDebugString("[BackgroundRandomizer] Error: ");
        XPLMDebugString(e.what());
        XPLMDebugString("\n");
    }

    return 1;
}
PLUGIN_API void	XPluginStop(void) { }
PLUGIN_API void XPluginDisable(void) { }
PLUGIN_API int  XPluginEnable(void) { return 1; }
PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFrom, int inMsg, void* inParam) { }
