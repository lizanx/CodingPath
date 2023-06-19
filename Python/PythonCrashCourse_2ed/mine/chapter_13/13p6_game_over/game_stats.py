class GameStats:
    """Represent the state of the game."""
    def __init__(self, game):
        self.settings = game.settings
        self.ships_left = self.settings.ship_limit
        self.enemies_destroed = 0
