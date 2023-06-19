class State:
    def __init__(self, game):
        self.active = False

        self.settings = game.settings
        self.miss_shoots = 0
        self.level = 1
        self.level_selected = False
        self.score = 0
        self.rocket_left = 3
        with open("highest_score.txt") as file_object:
            data = file_object.read()
            if data.strip() != "":
                self.highest_score = int(data)
            else:
                self.highest_score = 0

    def reset(self):
        # self.active = False
        self.miss_shoots = 0
        self.level = 1
        self.level_selected = False
        self.score = 0
        self.rocket_left = 3

    def set_level(self, level):
        self.level = level
        self.settings.set_difficulty(self.level)