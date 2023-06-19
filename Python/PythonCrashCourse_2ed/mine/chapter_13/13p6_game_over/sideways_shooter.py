import pygame
import sys
import time

from settings import Settings
from ship import Ship
from bullet import Bullet
from enemy import Enemy
from game_stats import GameStats

class SidewaysShooter:
    def __init__(self):
        pygame.init()
        self.settings = Settings()
        self.screen = pygame.display.set_mode(size=(self.settings.screen_width, self.settings.screen_height))
        self.rect = self.screen.get_rect()
        self.screen.fill(self.settings.bg_color)
        pygame.display.set_caption("Sideways Shooter")
        self.ship = Ship(self)
        self.bullets = pygame.sprite.Group()
        self.enemies = pygame.sprite.Group()
        self._create_enemies()
        self.stats = GameStats(self)
        self.game_active = True
    
    def _create_enemies(self):
        e = Enemy(self)
        rows = (self.rect.height - 6 * e.rect.height) // (2 * e.rect.height)
        cols = self.rect.height // 2 // (2 * e.rect.width)
        for row in range(rows):
            for col in range(cols):
                self._create_enemy(row, col)

    def _create_enemy(self, row, col):
        e = Enemy(self)
        e.rect.x = self.rect.width - e.rect.width * (1 + 2 * col)
        e.y = e.rect.height * (1 + 2 * row)
        self.enemies.add(e)
    
    def run(self):
        while True:
            self._check_events()
            if self.game_active:
                self.ship.update()
                self._update_bullets()
                self._update_enemies()
            self._update_screen()

    def _update_bullets(self):
        self.bullets.update()
        for bullet in self.bullets.copy():
            if bullet.rect.left > self.screen.get_rect().right:
                self.bullets.remove(bullet)
        self._check_bullet_enemy_collision()

    def _check_bullet_enemy_collision(self):
        collisions = pygame.sprite.groupcollide(self.bullets,
            self.enemies, True, True)
        self.stats.enemies_destroed += len(collisions)
        if self.stats.enemies_destroed >= self.settings.shoot_limit:
            self.game_active = False
        if not self.enemies:
            self.enemies.empty()
            self._create_enemies()

    def _update_enemies(self):
        for enemy in self.enemies:
            if enemy.check_edges():
                self.settings.enemy_direction *= -1
                for e in self.enemies:
                    e.rect.x -= self.settings.enemy_forward_speed
                break
        self.enemies.update()
        # Handle: enemy-ship collision and enemy hits left edge.
        for enemy in self.enemies.sprites():
            if pygame.sprite.spritecollideany(self.ship, self.enemies):
                self._ship_hit()
                break
        self._check_enemies_bottom()

    def _check_enemies_bottom(self):
        for enemy in self.enemies.sprites():
            if enemy.rect.left <= self.rect.left:
                self._ship_hit()
                break

    def _ship_hit(self):
        if self.stats.ships_left > 0:
            self.stats.ships_left -= 1
            self.bullets.empty()
            self.enemies.empty()
            self.ship.center_ship()
            self._create_enemies()
        else:
            self.game_active = False
        # Pause for 1s to show the collision.
        time.sleep(1)

    def _update_screen(self):
        self.screen.fill(self.settings.bg_color)
        self.ship.draw_ship()
        for bullet in self.bullets:
            bullet.draw_bullet()
        self.enemies.draw(self.screen)
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