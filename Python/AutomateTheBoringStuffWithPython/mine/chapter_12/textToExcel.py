import sys, openpyxl

wb = openpyxl.Workbook()
ws = wb.active

fillColumn = 1
for filename in sys.argv[1:]:
    with open(filename) as fb:
        lines = fb.readlines()
        for fillRow in range(1, len(lines) + 1):
            ws.cell(fillRow, fillColumn).value = lines[fillRow - 1]
    fillColumn += 1

wb.save('tte.xlsx')
wb.close()
print('Done.')