import pygame

from rocket import Rocket

class Scoreboard:
    def __init__(self, game):
        self.game = game
        
        self.color = (30, 30, 30)
        self.font = pygame.font.SysFont(None, 35)

        self.create_boards()
    
    def create_boards(self):
        self.update_score()
        self.update_highest_score()
        self.update_level()
        self.update_chance()

    def update_score(self):
        self.score_img = self.font.render(str(self.game.state.score),
            True, self.color, self.game.settings.bg_color)
        self.score_rect = self.score_img.get_rect()
        
        self.score_rect.top = self.game.scr_rect.top + 10
        self.score_rect.centerx = self.game.scr_rect.centerx

    def update_highest_score(self):
        self.highest_score_img = self.font.render("Highest: " + str(self.game.state.highest_score),
            True, self.color, self.game.settings.bg_color)
        self.highest_score_rect = self.highest_score_img.get_rect()
        
        self.highest_score_rect.bottom = self.game.scr_rect.bottom - 10
        self.highest_score_rect.centerx = self.game.scr_rect.centerx

    def update_level(self):
        self.level_img = self.font.render("Level " + str(self.game.state.level),
            True, self.color, self.game.settings.bg_color)
        self.level_rect = self.level_img.get_rect()
        
        self.level_rect.top = self.score_rect.bottom + 10
        self.level_rect.centerx = self.score_rect.centerx

    def update_chance(self):
        self.game.chances.empty()
        for chance in range(self.game.state.rocket_left):
            r = Rocket(self.game)
            r.rect.y = 10
            r.rect.x = chance * (50 + r.rect.width) + r.rect.width
            self.game.chances.add(r)

    def draw(self):
        self.game.scr.blit(self.score_img, self.score_rect)
        self.game.scr.blit(self.highest_score_img, self.highest_score_rect)
        self.game.scr.blit(self.level_img, self.level_rect)
        for r in self.game.chances.sprites():
            r.draw()