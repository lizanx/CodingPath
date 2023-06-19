def make_car(manufacturer, model, **info):
    info["Manufacturer"] = manufacturer.title()
    info["Model"] = model.title()
    return info
