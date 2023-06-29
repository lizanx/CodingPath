import os, requests, bs4

os.makedirs('xkcd', exist_ok=True)
url = 'https://xkcd.com/'

while not url.endswith('#'):
    print(f'Downloading page {url}...')
    content = requests.get(url)
    content.raise_for_status()

    contSoup = bs4.BeautifulSoup(content.text)

    comicElem = contSoup.select('#comic img')
    if comicElem:
        imgUrl = f'https:{comicElem[0].get("src")}'
        print(f'Downloading image {imgUrl}...')
        imgContent = requests.get(imgUrl)
        imgContent.raise_for_status()

        imgFile = open(os.path.join('xkcd', os.path.basename(imgUrl)), 'wb')
        for chunk in imgContent.iter_content(100_000):
            imgFile.write(chunk)
        imgFile.close()

    prevBtnElem = contSoup.select('a[rel="prev"]')
    if not prevBtnElem:
        print('Cannot find next prev button, exit.')
        break
    url = f'https://xkcd.com/{prevBtnElem[0].get("href")}'

print('Done.')
