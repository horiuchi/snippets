import hashlib


expected = [
    '0f1aae8b8398c20f81e1c36e349a7880c9234c63',
    '01821f5469967540a5a774197463e8c4d658f588',
    '264f39cab871e4cfd65b3a002f7255888bb5ed97'
]
result = []

def check(hash, s):
    global result
    for e in expected:
        if e == hash:
            result.append({ 'hash': hash, 'result': s })

alpha = 'abcdefghijklmnopqrstuvwxyz'
#alpha = ' 0123456789' + alpha + alpha.upper()

def hash(s):
    return hashlib.sha1(s).hexdigest()

def create():
    for i in xrange(len(alpha)):
        for j in xrange(len(alpha)):
            for k in xrange(len(alpha)):
                for l in xrange(len(alpha)):
                    yield alpha[i] + alpha[j] + alpha[k] + alpha[l]

print hash('tokyo')

l = len(expected)
for s in create():
    h = hash(s)
    check(h, s)
    if len(result) >= l:
        break

print result

