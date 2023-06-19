import pygame
import sys
import random
import time

from star import Star

class Stars:
    """The overall class to draw stars on the screen."""
    def __init__(self):
        pygame.init()
        self.screen = pygame.display.set_mode((800, 800))
        self.rect = self.screen.get_rect()
        self.stars = pygame.sprite.Group()
        pygame.display.set_caption("Stars")
        self.bg_color = (255, 255, 255)
        self.max_star_cnt = 5
        # self._create_stars()

    def _create_stars(self):
        star = Star(self)
        star_width, star_height = star.rect.size
        cols = (self.rect.width - star_width) // star_width
        rows = (self.rect.height - star_height) // star_height
        for i in range(self.max_star_cnt):
            col = random.randint(0, cols)
            row = random.randint(0, rows)
            self._create_star(star_width * col, star_height * row)

    def _create_star(self, x, y):
        star = Star(self)
        star.rect.x = x
        star.rect.y = y
        self.stars.add(star)

    def _clear_stars(self):
        for star in self.stars.copy():
            self.stars.remove(star)

    def run(self):
        while True:
            self._check_events()
            self._clear_stars()
            self._create_stars()
            self.screen.fill(self.bg_color)
            self.stars.draw(self.screen)
            pygame.display.flip()
            # time.sleep(1)
    
    def _check_events(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit()

if __name__ == '__main__':
    game = Stars()
    game.run()