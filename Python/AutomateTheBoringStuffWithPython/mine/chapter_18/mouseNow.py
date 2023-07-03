import pyautogui

print('Press CTRL+C to exit.')

try:
    while True:
        x, y = pyautogui.position()
        pixelColor = pyautogui.screenshot().getpixel((x, y))
        posStr = f'X:{str(x).rjust(4)}, Y:{str(y).rjust(4)}, RGB: ' \
            f'({str(pixelColor[0]).rjust(3)}, {str(pixelColor[0]).rjust(3)}, {str(pixelColor[0]).rjust(3)})'
        print(posStr, end='')
        print('\b' * len(posStr), end='', flush=True)
except KeyboardInterrupt:
    print('\nDone.')
