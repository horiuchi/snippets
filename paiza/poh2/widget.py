#!/usr/bin/env python
# coding: utf-8
# vim: fileencoding=utf8

def read_stdin():
    return raw_input().rstrip().split(' ')

def read_data(f):
    return map(int, read_stdin())


def check_widget(D, s, t, y, x):
    for r in xrange(s):
        for c in xrange(t):
            if not D[y+r][x+c]:
                return False
    return True

def solve(D, S):
    h = len(D)
    w = len(D[0])
    result = []
    for (s, t) in S:
        count = 0
        for r in xrange(h - s + 1):
            for c in xrange(w - t + 1):
                if check_widget(D, s, t, r, c):
                    count += 1
        result.append(count)
    return result


if __name__ == "__main__":
    H, W = read_data(int)
    D = []
    for i in xrange(H):
        D.append(map(lambda x: x == '0', raw_input()))
    N, = read_data(int)
    S = []
    for i in xrange(N):
        S.append(read_data(int))

    res = solve(D, S)
    for r in res:
        print r

