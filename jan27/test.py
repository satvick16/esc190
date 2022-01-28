L = [1, 4, 2, 7, 6, 3, 2, 9, 2]

#############################

new = []

small = 0

for x in range(len(L)):

    for i in range(len(L)):
        if L[i] < L[small]:
            small = i

    new.append(L[small])
    L.remove(L[small])

print(new)
