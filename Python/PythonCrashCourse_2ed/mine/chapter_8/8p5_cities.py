def describe_city(name, country = "China"):
    print(f"{name} is in {country}")

describe_city("Beijing")
describe_city(name = "Shenzhen")
describe_city("Manchester", "England")