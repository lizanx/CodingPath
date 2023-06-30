import sys, openpyxl

if len(sys.argv) != 2:
    print('Please enter an Excel file.')
    sys.exit(0)

wb = openpyxl.load_workbook(sys.argv[1])
ws = wb.active

for col in range(1, len(tuple(ws.columns)) + 1):
    with open(f'out_{col}.txt', 'w') as fb:
        for row in range(1, len(tuple(ws.rows)) + 1):
            fb.write(str(ws.cell(row, col).value) + '\n')

wb.close()

print('Done.')