import pygame
import sys

class Character:
    """Show a character image with matched background color."""
    def __init__(self, img):
        """Initialize the window and the image."""
        pygame.init()
        self.screen = pygame.display.set_mode(size=(800, 800))
        self.bg_color = (127, 185, 196)
        self.screen.fill(self.bg_color)
        pygame.display.set_caption("Game Character")
        self.image = pygame.image.load(img)
        self.screen_rect = self.screen.get_rect()
        self.char_rect = self.image.get_rect()
        self.char_rect.center = self.screen_rect.center
    
    def run(self):
        """Loop until exit."""
        while True:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    sys.exit()
            self.screen.fill(self.bg_color)
            self.screen.blit(self.image, self.char_rect)
            pygame.display.flip()

    def set_background(self, r=127, g=185, b=196):
        """Set background color with RGB values."""
        self.bg_color = (r, g, b)

if __name__ == '__main__':
    gc = Character("Irelia.bmp")
    gc.run()