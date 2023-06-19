def make_album(artist, title):
    return {"Artist": artist, "Album Title": title}

while True:
    artist = input("Please enter the artist name('quit' to quit): ")
    if artist == 'quit':
        break
    title = input("Please enter the album title('quit' to quit): ")
    if title == 'quit':
        break
    album = make_album(artist, title)
    print("The input album:", album, "\n")