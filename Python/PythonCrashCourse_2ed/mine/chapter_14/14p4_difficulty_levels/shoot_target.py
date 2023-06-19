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
        # buttons to select difficulty level
        center_x, center_y = self.scr_rect.center
        self.level_1_button = Button(self, "Level 1")
        self.level_1_button.set_pos(center_x + 2 * self.start_button.rect.width,
            center_y - 2 * self.level_1_button.rect.height)
        self.level_2_button = Button(self, "Level 2")
        self.level_2_button.set_pos(center_x + 2 * self.start_button.rect.width,
            center_y)
        self.level_3_button = Button(self, "Level 3")
        self.level_3_button.set_pos(center_x + 2 * self.start_button.rect.width,
            center_y + 2 * self.level_3_button.rect.height)

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
        if not self.state.active:
            if self.start_button.rect.collidepoint(mouse_pos):
                # self.state.reset()
                self.rocket.reset()
                self.bullets.empty()
                self.target.reset()
                if not self.state.level_selected:
                    self.settings.reset()

                self.state.active = True
                pygame.mouse.set_visible(False)
            elif not self.state.level_selected:
                if self.level_1_button.rect.collidepoint(mouse_pos):
                    self.state.level_selected = True
                    self.settings.set_difficulty_level(1)
                    self.level_1_button.set_msg("Level 1 selected")
                elif self.level_2_button.rect.collidepoint(mouse_pos):
                    self.state.level_selected = True
                    self.settings.set_difficulty_level(2)
                    self.level_2_button.set_msg("Level 2 selected")
                elif self.level_3_button.rect.collidepoint(mouse_pos):
                    self.state.level_selected = True
                    self.settings.set_difficulty_level(3)
                    self.level_3_button.set_msg("Level 3 selected")

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
        hit_bullet = pygame.sprite.spritecollideany(self.target, self.bullets)
        if hit_bullet or self.state.miss_shoots >= self.settings.bullet_max_miss:
            self.state.miss_shoots = 0
            self.rocket.reset()
            self.bullets.empty()
            self.target.reset()
            self.settings.scale_up_speed()
            self.settings.rocket_left -= 1
            if self.settings.rocket_left >= 0:
                time.sleep(1)
            else:
                self.state.active = False
                self.state.reset()
                self.state.level_selected = False
                self.level_1_button.set_msg("Level 1")
                self.level_2_button.set_msg("Level 2")
                self.level_3_button.set_msg("Level 3")

    def _update_scr(self):
        self.scr.fill(self.settings.bg_color)
        self.rocket.draw()
        for bullet in self.bullets:
            bullet.draw()
        self.target.draw()
        if not self.state.active:
            self.start_button.draw()
            self.level_1_button.draw()
            self.level_2_button.draw()
            self.level_3_button.draw()
        pygame.display.flip()



if __name__ == '__main__':
    game = Game()
    game.run()