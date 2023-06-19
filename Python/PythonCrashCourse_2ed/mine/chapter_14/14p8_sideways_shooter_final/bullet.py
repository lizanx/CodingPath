import pygame

class Bullet(pygame.sprite.Sprite):
    def __init__(self, game):
        super().__init__()
        self.settings = game.settings
        self.scr = game.scr
        self.scr_rect = game.scr_rect
        self.rocket = game.rocket

        self.rect = pygame.Rect(0, 0, self.settings.bullet_width,
            self.settings.bullet_height)
        self.rect.midleft = self.rocket.rect.midright
        self.x = float(self.rect.x)

    def draw(self):
        pygame.draw.rect(self.scr, self.settings.bullet_color, self.rect)

    def update(self):
        self.x += self.settings.bullet_speed
        self.rect.x = int(self.x)

    def check_range(self):
        if self.rect.left > self.scr_rect.right:
            return True
        return False