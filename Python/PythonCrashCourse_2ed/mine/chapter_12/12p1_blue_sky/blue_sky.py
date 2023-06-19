import pygame
import sys

class BlueSky:
    """A pygame window with blue background."""
    def __init__(self):
        pygame.init()
        self.screen = pygame.display.set_mode(size=(800, 800))
        self.bg_color = (0, 0, 255)
        self.screen.fill(self.bg_color)
        pygame.display.set_caption("BlueSky")
    
    def show_sky(self):
        while True:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    sys.exit()
            self.screen.fill(self.bg_color)
            pygame.display.flip()

    def set_color(self, r=0, g=0, b=255):
        """Set new background color using RGB values."""
        self.bg_color = (r, g, b)
        self.screen.fill(self.bg_color)

if __name__ == '__main__':
    bluesky = BlueSky()
    bluesky.show_sky()