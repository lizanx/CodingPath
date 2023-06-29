import sys, os, requests, bs4

if len(sys.argv) != 2:
    print('Please enter a URL.')
    sys.exit(0)

resp = requests.get(sys.argv[1])
resp.raise_for_status()

siteSoup = bs4.BeautifulSoup(resp.text)
linkElems = siteSoup.select('a')
if not linkElems:
    print('No link found.')
    sys.exit(0)

outFile = open('InvalidLinks.txt', 'w')
for linkElem in linkElems:
    url = linkElem.get('href')
    if not url.startswith('http'):
        url = os.path.join(sys.argv[1], url)
    print(f'Testing link {url}...')
    try:
        linkResp = requests.get(url)
        if linkResp.status_code == requests.codes.not_found:
            outFile.write(url + '\n')
    except:
        print(f'\tConnection Error: {url}')

outFile.close()

print('Done.')
