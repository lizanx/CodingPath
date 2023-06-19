import pygame

class Raindrop(pygame.sprite.Sprite):
    def __init__(self, game):
        super().__init__()
        self.image = pygame.image.load("raindrop.bmp")
        self.rect = self.image.get_rect()
        self.game = game

    def set_position(self, x, y):
        self.rect.x = x
        self.rect.y = y

    def update(self):
        self.rect.y += self.game.drop_speed