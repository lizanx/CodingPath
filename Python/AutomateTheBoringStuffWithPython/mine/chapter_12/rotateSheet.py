import sys, openpyxl, os

if len(sys.argv) != 2:
    print('Please enter start line, number of blank rows and a file')
    sys.exit(0)

wb = openpyxl.load_workbook(sys.argv[1])
sheet = wb.active
sheetRows = len(tuple(sheet.rows))
sheetCols = len(tuple(sheet.columns))

newWb = openpyxl.Workbook()
newSheet = newWb.active
newSheet.title = sheet.title
for row in range(1, sheetRows + 1):
    for col in range(1, sheetCols + 1):
        newSheet.cell(col, row).value = sheet.cell(row, col).value

newWb.save(os.path.basename(sys.argv[1]).rstrip('.xlsx') + '_new.xlsx')
