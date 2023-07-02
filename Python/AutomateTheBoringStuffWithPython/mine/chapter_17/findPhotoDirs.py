import os, sys
from PIL import Image

if len(sys.argv) != 2:
    print('Please enter a root directory to search.')
    sys.exit()

rootDir = sys.argv[1]
if not os.path.isdir(rootDir):
    print('Please enter a valid root directory.')
    sys.exit()

for foldername, subfolders, filenames in os.walk(rootDir):
    numPhotoFiles = 0
    numNonPhotoFiles = 0
    for filename in filenames:
        # Check if file extension isn't .png or .jpg.
        if not (filename.lower().endswith('.png') or \
                filename.lower().endswith('.jpg') or \
                filename.lower().endswith('.jpeg')):
            numNonPhotoFiles += 1
            continue

        imgObj = Image.open(os.path.join(foldername, filename))
        width, height = imgObj.size
        if width > 500 and height > 500:
            numPhotoFiles += 1
        else:
            numNonPhotoFiles += 1

    # If more than half of files were photos,
    # print the absolute path of the folder.
    if numPhotoFiles > numNonPhotoFiles:
        print(f'Photo directory "{foldername}" found.')

print('Done.')
