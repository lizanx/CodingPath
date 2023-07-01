import sys, os, PyPDF2

if len(sys.argv) != 3:
    print('Please enter a dir to walk through and a file containing possible passwords for hacking.')
    sys.exit(0)

if not os.path.isdir(sys.argv[1]):
    print('Invalid dir path.')
    sys.exit(0)

searchPath = sys.argv[1]
pwdFilePath = sys.argv[2]

pwdFile = open(pwdFilePath)
pwdList = []
for word in pwdFile:
    pwdList.append(word.strip().lower())
pwdFile.close()

for dirPath, _, filenames in os.walk(searchPath):
    for filename in filenames:
        if filename.endswith('.pdf'):
            with open(os.path.join(dirPath, filename), 'rb') as fb:
                pdfReader = PyPDF2.PdfReader(fb)
                if pdfReader.is_encrypted:
                    print(f'Hacking encrypted file {filename}...')
                    for pwd in pwdList:
                        # print(f'Trying password "{pwd}"...')
                        if pdfReader.decrypt(pwd) !=  0:
                            print(f'Password for file[{os.path.join(dirPath, filename)}] is "{pwd}"')
                            break

print('Done.')
