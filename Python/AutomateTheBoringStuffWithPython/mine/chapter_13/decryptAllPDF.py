import os, sys, PyPDF2

if len(sys.argv) != 3:
    print('Please enter a dir to walk through and a password for decryption.')
    sys.exit(0)

if not os.path.isdir(sys.argv[1]):
    print('Invalid dir path.')
    sys.exit(0)

for dirPath, _, filenames in os.walk(sys.argv[1]):
    print(f'Path: {dirPath}\tisFile: {os.path.isfile(dirPath)}')
    for filename in filenames:
        if filename.endswith('.pdf'):
            pdfFb = open(os.path.join(dirPath, filename), 'rb')
            pdfReader = PyPDF2.PdfReader(pdfFb)
            if pdfReader.is_encrypted:
                if pdfReader.decrypt(sys.argv[2]) != 0:
                    print(f'Decrypting {filename}...')
                    pdfWriter = PyPDF2.PdfWriter()
                    for page in pdfReader.pages:
                        pdfWriter.add_page(page)

                    pdfOutputFb = open(os.path.join(dirPath, filename).replace('.pdf', '_decrypted.pdf'), 'wb')
                    pdfWriter.write(pdfOutputFb)
                    pdfOutputFb.close()
                else:
                    print(f'Incorrect password[{sys.argv[2]} for {filename}]!')

            pdfFb.close()

print('Done.')
