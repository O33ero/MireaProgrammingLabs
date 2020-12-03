file = open('tree.txt')

while True:
    ch = file.read(1)
    if ch == '':
        break
    print(ch, end = '')