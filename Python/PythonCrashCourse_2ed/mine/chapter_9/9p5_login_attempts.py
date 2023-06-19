class User:
    def __init__(self, first_name, last_name, age, career):
        self.first_name, self.last_name, self.age, self.career = first_name, last_name, age, career
        self.login_attempts = 0
    def describe_user(self):
        print(f"{self.first_name.title()} {self.last_name.title()} is a "
            f"{self.age}-year-old {self.career}.")
    def greet_user(self):
        print(f"Hello, {self.first_name.title()} {self.last_name.title()}!")
    def increment_login_attempts(self):
        self.login_attempts += 1
    def reset_login_attempts(self):
        self.login_attempts = 0

user_1 = User("zetao", "chen", 26, "engineer")
user_1.describe_user()
user_1.greet_user()
print()

user_1.increment_login_attempts()
user_1.increment_login_attempts()
user_1.increment_login_attempts()
user_1.increment_login_attempts()
print("Login attemps:", user_1.login_attempts)
user_1.reset_login_attempts()
print("Login attemps:", user_1.login_attempts)
