# BackgroundRandomizer
BackgroundRandomizer is a simple plugin that changes the background of your X-Plane menu every time you open your simulator. It works by scanning a folder for the images you want to use, selecting a random image, and then updates the file used by X-Plane. *Next time the simulator is opened the randomly selected image is displayed, so the first time you launch X-Plane with this plugin you may not notice a difference.*

> [!CAUTION]
> ## Why doesn't BackgroundRandomizer support X-Plane 12.05 and later?
> In X-Plane 12.05 the location used for the menu's background changed to the `/Resources/bitmaps/backgrounds` folder, which already includes 1 image being the default background. You can put multiple images in this directory and X-Plane will randomly select one on startup, just as BackgroundRandomiser did. As a result, BackgroundRandomiser on X-Plane 12.05 (and later) would be pointless and a waste of time. Just put your backgrounds into the new folder and enjoy the same functionality as BackgroundRandomizer with one less plugin.

## Requirements
- X-Plane 11 through 12.04
- Windows, Mac or Linux

## Reverting back to the default image
To revert back to the default image, simply run the X-Plane installer or verify files on Steam. You will be prompted to overwrite changed files, so if you don't want to affect other addons, make sure to only overwrite `/Resources/bitmaps/interface11/image_background_screenshot_for_stack.png`!
