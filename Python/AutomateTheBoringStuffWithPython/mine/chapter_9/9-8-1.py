import os, shutil, sys

def cpyTypedFileTo(srcDir: str, dstDir: str, extension: str):
    if not os.path.exists(srcDir) or not os.path.exists(dstDir):
        print('Invalid dir input.')
        return
    
    dstPath = os.path.abspath(dstDir)
    for dirName, _, files in os.walk(srcDir):
        for file in files:
            if file.endswith(extension):
                shutil.copy(os.path.join(dirName, file), os.path.join(dstPath, file))

if __name__ == '__main__':
    if len(sys.argv) != 4:
        print('Please enter source dir, destination dir and extension.')
        sys.exit(0)
    
    print(f'Copying files ending with {sys.argv[3]} in {sys.argv[1]} to {sys.argv[2]}')
    cpyTypedFileTo(sys.argv[1], sys.argv[2], sys.argv[3])
