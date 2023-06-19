import pygame

class Star(pygame.sprite.Sprite):
    """Represent a single star."""
    def __init__(self, game):
        super().__init__()
        self.game = game
        self.image = pygame.image.load("star.bmp")
        self.rect = self.image.get_rect()
        self.x = float(self.rect.x)
        self.y = float(self.rect.y)
