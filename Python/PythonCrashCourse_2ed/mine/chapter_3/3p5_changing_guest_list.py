invite_list = ["Avril", "Jingru Liang", "Song Xu", "Tom Bruce"]
# assume that Tom Bruce cannot come, while Bill Gates and Alice Ann Munro can come
print("It's really a pity that Tom Bruce cannot come!")
invite_list.remove("Tom Bruce")
invite_list.append("Bill Gates")
invite_list.append("Alice Ann Munro")
print(f"But I'm glad that {invite_list} can come!")