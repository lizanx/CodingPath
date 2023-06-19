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

print("Oops! The new table cannot arrive in time, so I can only invite two people now!")
while len(invite_list) > 2:
    print(f"Dear {invite_list.pop()}, I'm sorry that I cannot invite you for dinner!")
while len(invite_list) > 0:
    print(f"Dear {invite_list.pop()}, you can still come for dinner!")

print("list:", invite_list)