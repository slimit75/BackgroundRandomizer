#![allow(unused_must_use)]
extern crate xplm;

use xplm::plugin::{Plugin, PluginInfo, management};
use xplm::{xplane_plugin, feature};
use std::fs;
use std::path::PathBuf;
use rand::Rng;

struct BackgroundRandomizerPlugin;

fn get_files(dir: PathBuf) -> Vec<fs::DirEntry> {
    let files = fs::read_dir(dir).unwrap();
    let mut images_array = Vec::new();

    for file in files {
        let unwrapped_file = file.unwrap();

        if fs::metadata(unwrapped_file.path()).unwrap().is_dir() {
            let temp_array = get_files(unwrapped_file.path());
            for item in temp_array {
                images_array.push(item);
            }
        }
        else {
            println!("[BackgroundRandomizer DEBUG] File found: {}", unwrapped_file.path().display());
            images_array.push(unwrapped_file);
        }
    }

    return images_array;
}

// Program partially based on this example: https://github.com/samcrow/rust-xplm/blob/master/examples/minimal.rs
impl Plugin for BackgroundRandomizerPlugin {
    type Error = std::convert::Infallible;

    fn start() -> Result<Self, Self::Error> {
        feature::find_feature("XPLM_USE_NATIVE_PATHS").expect("msg").set_enabled(true);
        xplm::debug("[BackgroundRandomizer] Finding new background...\n");

        // Fetch necessary directories
        let plugin_dir:PathBuf = management::this_plugin().path(); // Plugin directory
        println!("[BackgroundRandomizer DEBUG] Plugin path: {}", plugin_dir.display());

        let mut backgrounds_dir = PathBuf::from(plugin_dir.parent().unwrap().parent().unwrap()); // Images directory
        backgrounds_dir.push("images");

        let mut dest_path = PathBuf::from(plugin_dir.parent().unwrap().parent().unwrap().parent().unwrap().parent().unwrap()); // Destination path
        dest_path.push("bitmaps/interface11/image_background_screenshot_for_stack.png");

        // Generate the list of potential backgrounds
        let images = get_files(backgrounds_dir);

        // Select the new background
        let random_number = rand::thread_rng().gen_range(0..images.len());
        let background_path = &images[random_number];

        // Copy over the new background to the existing background
        // For now we are going to assume these DON'T error; if they do error, X-Plane still starts normally
        fs::remove_dir(&dest_path);
        fs::copy(background_path.path(), dest_path);
        println!("[BackgroundRandomizer DEBUG] New file: {} / TEST: {}", background_path.path().display(), &images[0].path().display());

        xplm::debug("[BackgroundRandomizer] Background successfully set.\n");

        Ok(BackgroundRandomizerPlugin)
    }

    fn info(&self) -> PluginInfo {
        PluginInfo {
            name: String::from("BackgroundRandomizer"),
            signature: String::from("org.slimit75.BackgroundRandomizer"),
            description: String::from("BackgroundRandomizer changes the background image of X-Plane's menus. Each background is randomly chosen at the previous startup."),
        }
    }
}

xplane_plugin!(BackgroundRandomizerPlugin);