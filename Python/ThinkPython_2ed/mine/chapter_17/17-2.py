class Kangaroo:
    def __init__(self):
        self.pouch_contents = []

    def put_in_pouch(self, obj):
        self.pouch_contents.append(obj)

    def __str__(self):
        res = 'Kangaroo'
        for attr in vars(self):
            res += ' ' + str(getattr(self, attr))
        return res

if __name__ == '__main__':
    kanga, roo = Kangaroo(), Kangaroo()
    kanga.put_in_pouch("hello")
    kanga.put_in_pouch("world")
    kanga.put_in_pouch(roo)
    print(roo)
    print(kanga)