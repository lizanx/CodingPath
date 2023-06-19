def build_profile(first_name, last_name, **info):
    info["first name"] = first_name
    info["last name"] = last_name
    return info
print(build_profile("gavin", "xu", birth="11/26", nation="china", age=24))