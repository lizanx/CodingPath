class State:
    def __init__(self, game):
        self.active = False

        self.settings = game.settings
        self.miss_shoots = 0

    def reset(self):
        # self.active = False
        self.miss_shoots = 0
