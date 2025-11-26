def log_function(fn):
    def tagged_fn(*args):
        fn(*args, fn.__name__)

    return tagged_fn


def print_msg(msg: str, tag: str | None = None):
    tag = f"[{tag}] " if tag else ""
    print(f"{tag}{msg}")


@log_function
def print_msg_with_func_name(msg: str, tag: str | None = None):
    tag = f"[{tag}] " if tag else ""
    print(f"{tag}{msg}")


if __name__ == "__main__":
    print_msg("Hello, world!")
    print_msg_with_func_name("Hello, world!")
