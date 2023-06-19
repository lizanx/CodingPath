import pygame
import sys

from settings import Settings
from ship import Ship
from bullet import Bullet

class SidewaysShooter:
    def __init__(self):
        pygame.init()
        self.settings = Settings()
        self.screen = pygame.display.set_mode(size=(self.settings.screen_width, self.settings.screen_height))
        self.screen.fill(self.settings.bg_color)
        pygame.display.set_caption("Sideways Shooter")
        self.ship = Ship(self)
        self.bullets = pygame.sprite.Group()
    
    def run(self):
        while True:
            self._check_events()
            self.ship.update()
            self._update_bullets()
            self._update_screen()

    def _update_bullets(self):
        self.bullets.update()
        for bullet in self.bullets.copy():
            if bullet.rect.left > self.screen.get_rect().right:
                self.bullets.remove(bullet)

    def _update_screen(self):
        self.screen.fill(self.settings.bg_color)
        self.ship.draw_ship()
        for bullet in self.bullets:
            bullet.draw_bullet()
        pygame.display.flip()

    def _check_events(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit()
            elif event.type == pygame.KEYDOWN:
                self._handle_keydown_events(event)
            elif event.type == pygame.KEYUP:
                self._handle_keyup_events(event)
    
    def _handle_keydown_events(self, event):
        if event.key == pygame.K_q:
            sys.exit()
        elif event.key == pygame.K_UP:
            self.ship.moving_up = True
        elif event.key == pygame.K_DOWN:
            self.ship.moving_down = True
        elif event.key == pygame.K_SPACE:
            self.bullets.add(Bullet(self))

    def _handle_keyup_events(self, event):
        if event.key == pygame.K_UP:
            self.ship.moving_up = False
        elif event.key == pygame.K_DOWN:
            self.ship.moving_down = False


if __name__ == '__main__':
    game = SidewaysShooter()
    game.run()