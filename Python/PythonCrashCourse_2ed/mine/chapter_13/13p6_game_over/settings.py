class Settings:
    def __init__(self):
        self.screen_width = 1200
        self.screen_height = 800
        self.bg_color = (255, 255, 255)
        # Ship settings.
        self.ship_speed = 1
        # Bullet settings.
        self.bullet_speed = 1.5
        self.bullet_width = 15
        self.bullet_height = 3
        self.bullet_color = (60, 60, 60)
        # Enemy settings.
        self.enemy_speed = 0.7
        self.enemy_forward_speed = 7
        # 1: moving down, -1: moving up
        self.enemy_direction = 1
        # Game over settings: the ship is hit 3 times or more than 5 enemies are shot down.
        self.ship_limit = 3
        self.shoot_limit = 5
