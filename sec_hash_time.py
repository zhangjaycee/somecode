#!/usr/bin/env python
# coding:utf-8

import hashlib
import time
import os
import sys



if len(sys.argv) == 2:
    print "input filename path:", sys.argv[1]
    f = open(sys.argv[1], 'rb')
    data = f.read()
    print "read done"
else:
    data =  'This a md5 test!'
    print '[no input filename path, default test content:]', data

start = time.clock()
hash_md5 = hashlib.md5(data)
print hash_md5.hexdigest()
end = time.clock()


print "execution time: %f s" % (end - start)
