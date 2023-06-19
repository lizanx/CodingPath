from user import User

class Privileges:
    def __init__(self, privileges):
        self.privileges = privileges
    def show_privileges(self):
        print("Privileges include:", self.privileges)


class Admin(User):
    def __init__(self, first_name, last_name, age, career, privileges):
        super().__init__(first_name, last_name, age, career)
        self.privileges = Privileges(privileges)
