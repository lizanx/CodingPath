import os, shutil

def cpyTypedFileTo(srcDir: str, dstDir: str, extension: str):
    if not os.path.exists(srcDir) or not os.path.exists(dstDir):
        print('Invalid dir input.')
        return
    
    srcPath = os.path.abspath(srcDir)
    dstPath = os.path.abspath(dstPath)
    for _, _, files in os.walk(srcPath):
        for file in files:
            if file.endswith(extension):
                shutil.copy(os.path.join(srcPath, file), os.path.join(dstPath, file))

