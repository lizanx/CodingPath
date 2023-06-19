def make_album(artist, title, num_of_songs = None):
    dict = {"Artist": artist, "Album Title": title}
    if num_of_songs:
        dict["Number of Songs"]  = num_of_songs
    return dict

print(make_album("Avril", "Head Above Water"))
print(make_album("Taylor Switft", "Shake It Off"))
print(make_album("Rihanna", "Hotness", 13))