import pygame

class Bullet(pygame.sprite.Sprite):
    def __init__(self, game):
        super().__init__()
        self.game = game
        self.settings = self.game.settings
        self.screen = self.game.screen
        self.rect = pygame.Rect(0, 0, self.settings.bullet_width,
            self.settings.bullet_height)
        self.rect.midleft = self.game.ship.rect.midleft
        self.x = float(self.rect.x)
    
    def update(self):
        self.x += self.settings.bullet_speed
        self.rect.x = self.x

    def draw_bullet(self):
        pygame.draw.rect(self.screen, self.settings.bullet_color, self.rect)