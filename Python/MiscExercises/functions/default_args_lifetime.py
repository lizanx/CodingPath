def print_msg(msg: str, config: dict[str, bool] = {"UpperCase": False}):
    print(f"config dict id: {id(config)}")

    if msg.startswith("Error"):
        config["UpperCase"] = True

    if config.get("UpperCase", False):
        print(f"msg: {msg.upper()}")
    else:
        print(f"msg: {msg}")


if __name__ == "__main__":
    print_msg("hello")
    print_msg("Python", config={"UpperCase": True})
    print_msg("Error: demo")  # Changes the same default "config" permanently
    print_msg("why is this one upper-case?")  # Upper-case
