import sys
import unicodedata

s = 'pýtĥöñ\fis\tawesome\r\n'
remap = {
    ord('\f'): ' ',
    ord('\t'): ' ',
    ord('\r'): None, # '\r' will be omitted
}
s = s.translate(remap)
print(s)

cmb_chrs = dict.fromkeys(c for c in range(sys.maxunicode) if unicodedata.combining(chr(c)))
s = unicodedata.normalize('NFD', s).translate(cmb_chrs)
print(s)
