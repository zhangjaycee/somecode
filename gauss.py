#!/usr/bin/python
# coding: utf-8


import random

l = []

RANGE = 100000
ITER = 12

for i in range(RANGE):
    sum = 0
    for i in range(ITER):
        sum += 100 * random.random()
    l.append(sum/ITER)

l.sort()

for i in range(100):
    percent = float(i) / 100
    index = int(percent * RANGE )
    print "percent: %f\tindex: %d\t Number: %f" % (percent, index, l[index])

