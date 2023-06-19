invite_list = ["Avril", "Jingru Liang", "Song Xu", "Tom Bruce"]
# assume that Tom Bruce cannot come, while Bill Gates and Alice Ann Munro can come
print("It's really a pity that Tom Bruce cannot come!")
invite_list.remove("Tom Bruce")
invite_list.append("Bill Gates")
invite_list.append("Alice Ann Munro")
print(f"But I'm glad that {invite_list} can come!")

print("Since I have found a bigger table, I can invite more people now!")
invite_list.insert(0, "Taylor Swift")
invite_list.insert(3, "Adele")
invite_list.append("Laurence")
print(f"Now all guests of {invite_list} can come for dinner!")