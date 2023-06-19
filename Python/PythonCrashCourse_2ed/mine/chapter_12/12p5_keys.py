import pygame
import sys

class Keys:
    """Monitor key presses."""
    def __init__(self):
        pygame.init()
        self.screen = pygame.display.set_mode(size=(50, 50))

    def run(self):
        while True:
            for event in pygame.event.get():
                if event.type == pygame.KEYDOWN:
                    print("Key Pressed:", event.key)
                elif event.type == pygame.QUIT:
                    sys.exit()
            pygame.display.flip()

if __name__ == '__main__':
    keys = Keys()
    keys.run()