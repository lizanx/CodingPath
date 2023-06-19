class Privileges:
    def __init__(self, privileges):
        self.privileges = privileges
    def show_privileges(self):
        print("Privileges include:", self.privileges)


class User:
    def __init__(self, first_name, last_name, age, career):
        self.first_name, self.last_name, self.age, self.career = first_name, last_name, age, career
    def describe_user(self):
        print(f"{self.first_name.title()} {self.last_name.title()} is a "
            f"{self.age}-year-old {self.career}.")
    def greet_user(self):
        print(f"Hello, {self.first_name.title()} {self.last_name.title()}!")


class Admin(User):
    def __init__(self, first_name, last_name, age, career, privileges):
        super().__init__(first_name, last_name, age, career)
        self.privileges = Privileges(privileges)


admin = Admin("Bruce", "Lee", 33, "warrior", ["can add post", "can delete post", "can ban user"])
admin.describe_user()
admin.privileges.show_privileges()