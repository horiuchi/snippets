#!/usr/bin/env python
# coding: utf-8
# vim: fileencoding=utf8

import re

def search(p, line, start):
    return p.search(line[start:])


if __name__ == "__main__":
    A, B = raw_input().rstrip().split(' ')
    line = raw_input();

    start = 0
    p = re.compile(re.escape(A) + '(.+?)' + re.escape(B))
    while True:
        m = search(p, line, start)
        if m is not None:
            print m.group(1)
            start += m.end() + 1
            if start >= len(line):
                break
        else:
            print '<blank>'
            break


