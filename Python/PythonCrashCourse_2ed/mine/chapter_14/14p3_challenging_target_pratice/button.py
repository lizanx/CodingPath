import pygame

class Button:
    def __init__(self, game, msg):
        self.scr = game.scr
        
        self.width, self.height = 200, 50
        self.bg_color = (0, 255, 0)
        self.text_color = (255, 255, 255)
        self.font = pygame.font.SysFont(None, 48)

        self.rect = pygame.Rect(0, 0, self.width, self.height)
        self.rect.center = self.scr.get_rect().center

        self._create_msg(msg)

    def _create_msg(self, msg):
        self.msg_img = self.font.render(msg, True,
            self.text_color, self.bg_color)
        self.msg_rect = self.msg_img.get_rect()
        self.msg_rect.center = self.rect.center

    def draw(self):
        self.scr.fill(self.bg_color, self.rect)
        self.scr.blit(self.msg_img, self.msg_rect)