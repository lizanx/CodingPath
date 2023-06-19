def make_car(manufacturer, model, **info):
    info["Manufacturer"] = manufacturer.title()
    info["Model"] = model.title()
    return info

car = make_car('subaru', 'outback', color='blue', tow_package=True)
print(car)