# The function comes from exercise 8-14

# Version 1
import make_car
car = make_car.make_car('subaru', 'outback', color='blue', tow_package=True)
print(car)

# Version 2
from make_car import make_car
car = make_car('subaru', 'outback', color='green', tow_package=True)
print(car)

# Version 3
from make_car import make_car as mc
car = mc('subaru', 'outback', color='yellow', tow_package=True)
print(car)

# Version 4
import make_car as mc
car = mc.make_car('subaru', 'outback', color='white', tow_package=True)
print(car)

# Version 5
from make_car import *
car = make_car('subaru', 'outback', color='black', tow_package=True)
print(car)
