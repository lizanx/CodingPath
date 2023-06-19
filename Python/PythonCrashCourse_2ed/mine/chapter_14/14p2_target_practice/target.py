import pygame

class Target:
    def __init__(self, game):
        self.settings = game.settings
        self.scr = game.scr
        self.scr_rect = game.scr_rect

        self.rect = pygame.Rect(0, 0,
            self.settings.target_width, self.settings.target_height)

        self.color = (133, 153, 0)
        self.y = 0.0

        self.reset()

    def reset(self):
        self.rect.midright = self.scr_rect.midright
        self.y = float(self.rect.y)

    def update(self):
        if self._check_edges():
            self.rect.x -= self.settings.target_forward_speed
            self.settings.target_direction *= -1
        # 1: moving down, -1: moving up
        self.y += self.settings.target_direction * self.settings.target_speed
        self.rect.y = int(self.y)

    def _check_edges(self):
        if self.rect.bottom >= self.scr_rect.bottom or self.rect.top <= self.scr_rect.top:
            return True
        return False

    def draw(self):
        pygame.draw.rect(self.scr, self.color, self.rect)