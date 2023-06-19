import os

if __name__ == '__main__':
    for root, dirs, files in os.walk('D:\\PythonFiles\\PythonLearning\\ThinkPython_2ed'):
        print('root:', root)
        print('dirs:', dirs)
        print('files:', files)