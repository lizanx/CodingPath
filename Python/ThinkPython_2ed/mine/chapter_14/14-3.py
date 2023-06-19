import os
import hashlib

def get_mp3_paths(dirname):
    mp3s = []
    for node in os.listdir(dirname):
        if os.path.isfile(node):
            if node[-4:] == '.mp3':
                mp3s.append(os.path.join(dirname, node))
        elif os.path.isdir(node):
            mp3s.extend(get_mp3_paths(node))
    return mp3s

def compare_md5(file_1, file_2):
    try:
        f1 = open(file_1)
    except:
        print('Failed to open', file_1)
        return False
    else:
        content_1 = file_1.read()
        f1.close()
    try:
        f2 = open(file_2)
    except:
        print('Failed to open', file_2)
        return False
    else:
        content_2 = file_2.read()
        f2.close()
    
    md5_f1 = hashlib.md5(content_1).hexdigest()
    md5_f2 = hashlib.md5(content_2).hexdigest()
    if md5_f1 == md5_f2:
        return True
    return False

