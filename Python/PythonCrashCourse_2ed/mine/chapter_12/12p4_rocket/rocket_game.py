import pygame
import sys

from rocket import Rocket

class RocketGame:
    def __init__(self, image="rocket.bmp"):
        pygame.init()
        self.screen = pygame.display.set_mode(size=(800, 800))
        pygame.display.set_caption("Rocket Game")
        self.bg_color = (255, 255, 255)
        self.screen.fill(self.bg_color)
        self.rocket = Rocket(self, image)

    def run(self):
        while True:
            self._check_events()
            self.rocket.update()
            self._update_screen()

    def _update_screen(self):
        self.screen.fill(self.bg_color)
        self.rocket.draw_self()
        pygame.display.flip()

    def _check_events(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit()
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_UP:
                    self.rocket.moving_up = True
                elif event.key == pygame.K_DOWN:
                    self.rocket.moving_down = True
                elif event.key == pygame.K_RIGHT:
                    self.rocket.moving_right = True
                elif event.key == pygame.K_LEFT:
                    self.rocket.moving_left = True
            elif event.type == pygame.KEYUP:
                if event.key == pygame.K_UP:
                    self.rocket.moving_up = False
                elif event.key == pygame.K_DOWN:
                    self.rocket.moving_down = False
                elif event.key == pygame.K_RIGHT:
                    self.rocket.moving_right = False
                elif event.key == pygame.K_LEFT:
                    self.rocket.moving_left = False


if __name__ == '__main__':
    game_instance = RocketGame()
    game_instance.run()