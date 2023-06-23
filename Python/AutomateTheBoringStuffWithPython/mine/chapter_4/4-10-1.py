def list_to_fmt_str(in_list: list):
    return ', '.join([str(element) for element in in_list[:-1]]) + f', and {in_list[-1]}'
