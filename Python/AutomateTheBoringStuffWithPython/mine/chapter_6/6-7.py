def printTable(table: list):
    """Print a table column by column, each row should be of same size.
    :param table: a list of lists, rows x cols table.
    """
    if not table or any(len(row) != len(table[0]) for row in table):
        raise ValueError('The table is invalid for printing.')

    colWidth = max((max(len(item) for item in row)) for row in table)
    for col in range(len(table[0])):
        for row in range(len(table)):
            print(table[row][col].rjust(colWidth), end='')
        print()

tableData = [
    ['apples', 'oranges', 'cherries', 'banana'],
    ['Alice', 'Bob', 'Carol', 'David'],
    ['dogs', 'cats', 'moose', 'goose']
]
printTable(tableData)
