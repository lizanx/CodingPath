import PyPDF2

pdfFileObj = open('aboutMD.pdf', 'rb')
pdfReader = PyPDF2.PdfReader(pdfFileObj)
print(f'Pages: {len(pdfReader.pages)}, Encrypted: {pdfReader.is_encrypted}')
# print(type(pdfReader.pages[0]))
# print(pdfReader.pages[0].extract_text())
watermarkFileObj = open('watermark.pdf', 'rb')
wmReader = PyPDF2.PdfReader(watermarkFileObj)

pdfOutputFile = open('aboutMD_output.pdf', 'wb')
pdfWriter = PyPDF2.PdfWriter()
for i in range(len(pdfReader.pages)):
    if i < 3:
        pdfReader.pages[i].merge_page(wmReader.pages[0])
        pdfWriter.add_page(pdfReader.pages[i])
    else:
        pdfWriter.add_page(pdfReader.pages[i])
pdfWriter.encrypt('mypassword')
pdfWriter.write(pdfOutputFile)

pdfOutputFile.close()
watermarkFileObj.close()
pdfFileObj.close()
print('Done.')
