import os, sys, PyPDF2

if len(sys.argv) != 3:
    print('Please enter a dir to walk through and a password for encryption.')
    sys.exit(0)

if not os.path.isdir(sys.argv[1]):
    print('Invalid dir path.')
    sys.exit(0)

for dirPath, _, filenames in os.walk(sys.argv[1]):
    print(f'Path: {dirPath}\tisFile: {os.path.isfile(dirPath)}')
    for filename in filenames:
        if filename.endswith('.pdf'):
            print(f'Encrypting {filename}...')
            pdfFb = open(os.path.join(dirPath, filename), 'rb')
            pdfReader = PyPDF2.PdfReader(pdfFb)

            pdfWriter = PyPDF2.PdfWriter()
            for page in pdfReader.pages:
                pdfWriter.add_page(page)
            pdfWriter.encrypt(sys.argv[2])

            pdfOutputFb = open(os.path.join(dirPath, filename).replace('.pdf', '_encrypted.pdf'), 'wb')
            pdfWriter.write(pdfOutputFb)

            pdfFb.close()
            pdfOutputFb.close()

print('Done.')
