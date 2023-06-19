import pygame
import sys

from raindrop import Raindrop

class ShowRaindrops:
    def __init__(self):
        pygame.init()
        self.screen = pygame.display.set_mode((800, 800))
        pygame.display.set_caption("Raindrops")
        self.rect = self.screen.get_rect()
        self.bg_color = (255, 255, 255)
        self.drop_speed = 1
        self.raindrops = pygame.sprite.Group()
        self._create_raindrops()

    def _create_raindrops(self):
        r = Raindrop(self)
        width, height = r.rect.size
        cols = self.rect.width // (3 * width)
        rows = self.rect.height // (3 * height) // 3
        for row in range(rows):
            for col in range(cols):
                rd = Raindrop(self)
                rd.set_position(width + 3 * col * width,
                    height + 3 * row * height)
                self.raindrops.add(rd)


    def run(self):
        while True:
            self._check_events()
            self._update_raindrops()
            self._update_screen()

    def _check_events(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit()

    def _update_raindrops(self):
        self.raindrops.update()
        need_new_raindrops = False
        for r in self.raindrops.copy():
            if r.rect.top >= self.rect.bottom: 
                self.raindrops.remove(r)
                if not need_new_raindrops:
                    need_new_raindrops = True
        if need_new_raindrops:
            self._create_new_raindrops_row()

    def _create_new_raindrops_row(self):
        r = Raindrop(self)
        width, height = r.rect.size
        cols = self.rect.width // (3 * width)
        for col in range(cols):
            rd = Raindrop(self)
            rd.set_position(width + 3 * col * width, height)
            self.raindrops.add(rd)

    def _update_screen(self):
        self.screen.fill(self.bg_color)
        self.raindrops.draw(self.screen)
        pygame.display.flip()



if __name__ == "__main__":
    game = ShowRaindrops()
    game.run()