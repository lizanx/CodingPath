import pygame

class Enemy(pygame.sprite.Sprite):
    """Represent the targets of shooter."""
    def __init__(self, game):
        super().__init__()
        self.game = game
        self.settings = self.game.settings
        self.image = pygame.image.load("enemy.bmp")
        self.rect = self.image.get_rect()
        self.y = float(self.rect.y)

    def update(self):
        self.y += self.settings.enemy_direction * self.settings.enemy_speed
        self.rect.y = int(self.y)
    
    def check_edges(self):
        screen_rect = self.game.screen.get_rect()
        if self.rect.bottom >= screen_rect.bottom or self.rect.top <= screen_rect.top:
            return True
        return False