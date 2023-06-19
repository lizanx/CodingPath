class User:
    def __init__(self, first_name, last_name, age, career):
        self.first_name, self.last_name, self.age, self.career = first_name, last_name, age, career
    def describe_user(self):
        print(f"{self.first_name.title()} {self.last_name.title()} is a "
            f"{self.age}-year-old {self.career}.")
    def greet_user(self):
        print(f"Hello, {self.first_name.title()} {self.last_name.title()}!")

user_1 = User("zetao", "chen", 26, "engineer")
user_1.describe_user()
user_1.greet_user()
print()

user_2 = User("bruce", "lee", 33, "warrior")
user_2.describe_user()
user_2.greet_user()
