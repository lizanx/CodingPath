import pygame

class Rocket:
    """A rocket which can move in 4 directions within a window."""
    def __init__(self, game, image):
        self.image = pygame.image.load(image)
        self.game = game
        self.rect = self.image.get_rect()
        self.rect.center = self.game.screen.get_rect().center
        self.moving_up = False
        self.moving_down = False
        self.moving_right = False
        self.moving_left = False

    def update(self):
        if self.moving_up and self.rect.top > 0:
            self.rect.y -= 1
        if self.moving_down and self.rect.bottom < self.game.screen.get_rect().bottom:
            self.rect.y += 1
        if self.moving_right and self.rect.right < self.game.screen.get_rect().right:
            self.rect.x += 1
        if self.moving_left and self.rect.left > 0:
            self.rect.x -= 1

    def draw_self(self):
        self.game.screen.blit(self.image, self.rect)