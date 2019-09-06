# Import required libarys
import random
import os
from shutil import copyfile

# Get full the path of the screenshots folder
photo = os.path.dirname(os.path.realpath(__file__))
baseDir = photo 
photo = photo + r'\Screenshots'

# Get a random image
onlyfiles = next(os.walk(photo))[2]
file = random.randint(0,len(onlyfiles)-1)
image = onlyfiles[file]

# Get the path of the actual file to replace
replace = os.path.abspath(os.path.join(baseDir, os.pardir))
xdir = replace
replace = replace + r'\Resources\bitmaps\interface11\image_background_screenshot_for_stack.png'

# Copy that image into the menu image
copyfile(os.path.join(photo, image), replace)

# Start X-Plane
os.startfile(xdir + r'\X-Plane.exe')