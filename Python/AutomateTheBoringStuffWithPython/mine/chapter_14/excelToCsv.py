import sys, os, csv, openpyxl

if len(sys.argv) != 2:
    print('Please enter a folder cotaining Excel files to transform.')
    sys.exit()

folderPath = sys.argv[1]

for excelFile in os.listdir(folderPath):
    if not excelFile.endswith('.xlsx'):
        continue

    wb = openpyxl.load_workbook(os.path.join(folderPath, excelFile))
    for sheetName in wb.sheetnames:
        sheet = wb[sheetName]

        with open(os.path.join(folderPath, f'{excelFile.removesuffix(".xlsx")}_{sheetName}.csv'), 'w') as outputCsvFb:
            print(f'Processing {outputCsvFb.name}...')
            csvWriter = csv.writer(outputCsvFb)
            for rowNum in range(1, sheet.max_row + 1):
                rowData = []
                for colNum in range(1, sheet.max_column + 1):
                    rowData.append(sheet.cell(rowNum, colNum).value)
                
                csvWriter.writerow(rowData)

print('Done.')
