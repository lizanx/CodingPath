from operator import attrgetter

class User:
    def __init__(self, user_id) -> None:
        self.user_id = user_id
    
    def __repr__(self) -> str:
        return f'User({self.user_id})'

users = [User(5), User(3), User(1)]
print(sorted(users, key=attrgetter('user_id')))
