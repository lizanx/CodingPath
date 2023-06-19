class GameStats:
    """Track statistics for Alien Invasion."""
    def __init__(self, ai_game):
        self.settings = ai_game.settings
        self.game_active = False
        self.reset_stats()
    
    def reset_stats(self):
        self.game_active = False
        self.ships_left = self.settings.ship_limit
