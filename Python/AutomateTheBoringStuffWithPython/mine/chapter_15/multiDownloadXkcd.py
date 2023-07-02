import os, requests, bs4, threading

os.makedirs('xkcd', exist_ok=True)
url = 'https://xkcd.com/'

def downloadXkcd(startComic: int, endComic: int):
    for urlNum in range(startComic, endComic):
        print(f'Downloading page {url}{urlNum}...')
        content = requests.get(url + str(urlNum))
        try:
            content.raise_for_status()
        except:
            print(f'Failed to fetch {url}{urlNum}, skip it.')
            continue


        contSoup = bs4.BeautifulSoup(content.text)

        comicElem = contSoup.select('#comic img')
        if comicElem:
            imgUrl = f'https:{comicElem[0].get("src")}'
            print(f'Downloading image {imgUrl}...')
            imgContent = requests.get(imgUrl)
            try:
                imgContent.raise_for_status()
            except:
                print(f'Failed to download comic {os.path.basename(imgUrl)}, skip it.')
                continue

            imgFile = open(os.path.join('xkcd', os.path.basename(imgUrl)), 'wb')
            for chunk in imgContent.iter_content(100_000):
                imgFile.write(chunk)
            imgFile.close()

downloadThreads = []
for i in range(0, 1000, 100):
    downloadThread = threading.Thread(target=downloadXkcd, args=[i, i + 100])
    downloadThreads.append(downloadThread)
    downloadThread.start()

for downloadThread in downloadThreads:
    downloadThread.join()

print('Done.')
