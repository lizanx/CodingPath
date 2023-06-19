class Settings:
    def __init__(self):
        # self.game = game
        self.scr_width, self.scr_height = 1500, 800
        self.bg_color = (230, 230, 230)

        self.rocket_speed = 1.5
        self.rocket_left = 3

        self.bullet_speed = 1.5
        self.bullet_width = 15
        self.bullet_height = 4
        self.bullet_color = (22, 128, 170)
        self.bullet_limit = 3
        self.bullet_max_miss = 3

        self.target_width = 20
        self.target_height = 50
        self.target_speed = 1.0
        self.target_forward_speed = 5
        # 1 -> moving down, -1 -> moving up
        self.target_direction = 1

        self.speed_scale = 2

    def reset(self):
        self.rocket_left = 3
        self.rocket_speed = 1.5
        self.bullet_speed = 1.5
        self.target_speed = 1.0
        self.target_direction = 1

    def scale_up_speed(self):
        self.rocket_speed *= self.speed_scale
        self.bullet_speed *= self.speed_scale
        self.target_speed *= self.speed_scale

    def set_difficulty_level(self, level):
        self.reset()
        self.rocket_speed *= level
        self.bullet_speed *= level
        self.target_speed *= level
