import time, pyautogui

try:
    while True:
        pyautogui.moveRel(1, 0)
        time.sleep(10)
        pyautogui.moveRel(-1, 0)
        time.sleep(10)
except KeyboardInterrupt:
    print('Done')
