import pygame
import sys
import time

from settings import Settings
from state import State
from button import Button
from rocket import Rocket
from target import Target
from bullet import Bullet

class Game:
    def __init__(self):
        pygame.init()

        self.settings = Settings()

        self.state = State(self)

        self.scr = pygame.display.set_mode((self.settings.scr_width, self.settings.scr_height))
        self.scr_rect = self.scr.get_rect()

        self.start_button = Button(self, "Start")

        self.rocket = Rocket(self)

        self.target = Target(self)

        self.bullets = pygame.sprite.Group()

    def run(self):
        while True:
            self._check_events()
            if self.state.active:
                self.rocket.update()
                self._update_bullets()
                self.target.update()
                self._handle_shoot()
                self._check_end()

            self._update_scr()

    def _check_events(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            elif event.type == pygame.KEYDOWN:
                self._handle_key_down(event)
            elif event.type == pygame.KEYUP:
                self._handle_key_up(event)
            elif event.type == pygame.MOUSEBUTTONDOWN:
                self._handle_click(pygame.mouse.get_pos())

    def _handle_key_down(self, event):
        if event.key == pygame.K_q:
            pygame.quit()
            sys.exit()
        if self.state.active:
            if event.key == pygame.K_UP:
                self.rocket.moving_up = True
            elif event.key == pygame.K_DOWN:
                self.rocket.moving_down = True
            elif event.key == pygame.K_SPACE:
                if len(self.bullets) < self.settings.bullet_limit:
                    self.bullets.add(Bullet(self))

    def _handle_key_up(self, event):
        if event.key == pygame.K_UP:
            self.rocket.moving_up = False
        elif event.key == pygame.K_DOWN:
            self.rocket.moving_down = False

    def _handle_click(self, mouse_pos):
        if self.start_button.rect.collidepoint(mouse_pos) and not self.state.active:
            self.state.reset()
            self.rocket.reset()
            self.bullets.empty()
            self.target.reset()

            self.state.active = True
            pygame.mouse.set_visible(False)

    def _update_bullets(self):
        for bullet in self.bullets.copy():
            if bullet.check_range():
                self.bullets.remove(bullet)
                self.state.miss_shoots += 1
        self.bullets.update()

    def _handle_shoot(self):
        hit_bullet = pygame.sprite.spritecollideany(self.target, self.bullets)
        if hit_bullet:
            # self.bullets.remove(hit_bullet)
            self.state.active = False
            pygame.mouse.set_visible(True)

    def _check_end(self):
        if not self.state.active or self.state.miss_shoots >= self.settings.bullet_max_miss:
            self.state.active = False
            self.bullets.empty()
            pygame.mouse.set_visible(True)
            print("END:", self.state.active, self.state.miss_shoots)

    def _update_scr(self):
        self.scr.fill(self.settings.bg_color)
        self.rocket.draw()
        for bullet in self.bullets:
            bullet.draw()
        self.target.draw()
        if not self.state.active:
            self.start_button.draw()
        pygame.display.flip()



if __name__ == '__main__':
    game = Game()
    game.run()