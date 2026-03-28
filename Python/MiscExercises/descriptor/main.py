from typing import Callable
import datetime

def property_check():
    class Integer:
        def __init__(self, name: str) -> None:
            self.name = name

        def __get__(self, instance: object | None, owner: type):
            if instance is None:
                return self
            return instance.__dict__[self.name]
    
        def __set__(self, instance: object, value: int):
            if not isinstance(value, int):
                raise TypeError(f"{self.name} must be an integer")
            instance.__dict__[self.name] = value
    
    class Person:
        age = Integer("age")
    
    p = Person()
    p.age = 28
    print(f"Age of the person: {p.age}")
    try:
        p.age = "28"
    except TypeError as e:
        print(f"Failed to set p.age, error: {e}")

def lazy_calculation_and_cache():
    class LazyProperty:
        def __init__(self, func: Callable) -> None:
            self.func = func
        
        def __get__(self, instance, owner):
            if instance is None:
                return self
            value = self.func(instance)
            instance.__dict__[self.func.__name__] = value # cache
            return value
    
    class Circle:
        def __init__(self, radius: float) -> None:
            self.radius = radius
        
        @LazyProperty
        def area(self) -> float:
            print("Calculating area..")
            return self.radius**2 * 3.14
        
    circle = Circle(2.0)
    print(f"1st - circle area: {circle.area}")
    print(f"2nd - circle area: {circle.area}")

def property_access_control():
    class Readonly:
        def __init__(self, value) -> None:
            self.value = value
        
        def __get__(self, instance, owner):
            return self.value
        
        def __set__(self, instance, value):
            raise AttributeError("Cannot change readonly property")
    
        def __delete__(self, instance):
            raise AttributeError("Cannot delete readonly property")
    
    class File:
        created = Readonly(datetime.datetime.now())
    
    file = File()
    print(f"file created at: {file.created}")
    try:
        file.created = datetime.datetime.now()
    except AttributeError as e:
        print(f"Failed to set file 'created' property, error: {e}")
    try:
        del file.created
    except AttributeError as e:
        print(f"Failed to delete file 'created' property, error: {e}")

if __name__ == "__main__":
    property_check()
    print("--------------")
    lazy_calculation_and_cache()
    print("--------------")
    property_access_control()

