#!/usr/bin/env python
# coding: utf-8
# vim: fileencoding=utf8

import math

if __name__ == "__main__":
    N, M, K = map(int, raw_input().rstrip().split(' '))
    cs = map(float, raw_input().rstrip().split(' '))
    ks = []
    for i in xrange(M):
        xs = map(int, raw_input().rstrip().split(' '))
        k = 0
        for j in xrange(len(xs)):
            k += cs[j] * xs[j]
        ks.append(int(round(k)))
    ks.sort()
    ks.reverse()

    for i in xrange(K):
        print ks[i]

