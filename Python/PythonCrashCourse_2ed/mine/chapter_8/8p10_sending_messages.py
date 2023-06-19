msgs = ["Hello World", "This is gavin", "It's a nice day today!"]
def show_messages(msgs):
    for msg in msgs:
        print("Message content:", msg)
show_messages(msgs)

print()
sent_msgs = []
def send_messages(msgs, sent_msgs):
    while msgs:
        msg = msgs.pop()
        print("Message sent:", msg)
        sent_msgs.append(msg)
send_messages(msgs, sent_msgs)
print(f"\nmsgs: {msgs}\nsent messages:{sent_msgs}")