#!/usr/bin/env python

import zipapp

zipapp.create_archive("myapp", target="myapp2.pyz", interpreter="/usr/bin/env python", compressed=True)
# refer to https://docs.python.org/zh-cn/3.13/library/zipapp.html#command-line-interface for option details.
