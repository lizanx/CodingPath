import pygame
import sys

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
        self.star_cnt = 0
        self._create_stars()

    def _create_stars(self):
        star = Star(self)
        star_width, star_height = star.rect.size
        cols = (self.rect.width - star_width) // (2 * star_width)
        rows = (self.rect.height - star_height) // (2 * star_height)
        print("cols:", cols, "rows:", rows)
        for col in range(cols):
            for row in range(rows):
                self._create_star(star_width + 2 * col * star_width,
                    star_height + 2 * row * star_height)
        print(f"create {self.star_cnt} stars done.")

    def _create_star(self, x, y):
        star = Star(self)
        star.rect.x = x
        star.rect.y = y
        self.star_cnt += 1
        self.stars.add(star)


    def run(self):
        while True:
            self._check_events()
            self.screen.fill(self.bg_color)
            self.stars.draw(self.screen)
            pygame.display.flip()
    
    def _check_events(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit()

if __name__ == '__main__':
    game = Stars()
    game.run()