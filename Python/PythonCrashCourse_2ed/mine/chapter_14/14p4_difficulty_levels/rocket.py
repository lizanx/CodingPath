import pygame

class Rocket:
    def __init__(self, game):
        self.game = game

        self.image = pygame.image.load("rocket.bmp")
        self.rect = self.image.get_rect()

        self.y = 0.0

        self.reset()
    
    def reset(self):
        self.moving_up = False
        self.moving_down = False

        self.rect.midleft = self.game.scr_rect.midleft
        self.y = float(self.rect.y)

    def update(self):
        if self.moving_down and self.rect.bottom < self.game.scr_rect.bottom:
            self.y += self.game.settings.rocket_speed
        if self.moving_up and self.rect.top > self.game.scr_rect.top:
            self.y -= self.game.settings.rocket_speed
        self.rect.y = int(self.y)

    def draw(self):
        self.game.scr.blit(self.image, self.rect)