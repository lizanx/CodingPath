class Person:
    def __init__(self, name: str, age: int) -> None:
        self.name = name
        self._age = age

    def __repr__(self) -> str:
        return f"Name: {self.name}, age: {self.age}"

    @property
    def age(self) -> int:
        return self._age
    
    @age.setter
    def age(self, value: int) -> None:
        if value <= 0 or value >= 150:
            raise RuntimeError(f"Invalid age {value}")
        self._age = value
    

if __name__ == "__main__":
    a = Person("A", 18)
    print(a)
    a.age = 33
    print(a)

    print("=====================")

    # Add "is_adult" attribute to Person class.
    def get_is_adult(self) -> bool:
        return self.age >= 18
    def set_is_adult(self, value: bool) -> None:
        if self.is_adult != value:
            if value:
                self.age = 18
            else:
                self.age = 17
    setattr(Person, "is_adult", property(fget=get_is_adult, fset=set_is_adult))
    b = Person("B", 15)
    print(b)
    print(f"b is adult: {b.is_adult}")
    b.is_adult = True
    print(f"b is adult: {b.is_adult}")
    print(b)
    b.is_adult = False
    print(b)
    
