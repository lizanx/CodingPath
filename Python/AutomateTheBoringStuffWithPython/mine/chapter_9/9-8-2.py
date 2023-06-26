import shutil, sys, os

def findLargeFile(dir: str, sizeThreshold: int = 2**20 * 100):
    if not os.path.exists(dir):
        print(f'Path "{dir}" does not exist!')
        return
    
    if os.path.isfile(dir):
        if (sz := os.path.getsize(dir)) >= sizeThreshold:
            print(f'Size of {dir}: {sz / (2**20)}MB')
        return
    
    for dirName, _, files in os.walk(dir):
        for file in files:
            path = os.path.join(dirName, file)
            if (sz := os.path.getsize(path)) >= sizeThreshold:
                print(f'Size of {path}: {round(sz / (2**20), 2)}MB')

if __name__ == '__main__':
    srcDir = input('Please enter the root dir to search:\n')
    sizeThreshold = int(input('Please enter the size threshold(in KB, by default 100MB):\n'))
    findLargeFile(srcDir, sizeThreshold)
