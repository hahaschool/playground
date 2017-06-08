input = raw_input #Remove if on Python 3
n = int(input())
ls = [[],[],[]]
for each_ls in ls:
    li = input().split()
    for i in range(n):
        each_ls.append(int(li[i]))

def isequ(x,y):
    global ls
    if ls[0][x] == ls[0][y] and ls[1][x] == ls[1][y] and ls[2][x] == ls[2][y]:
        return 1
    elif ls[0][x] == ls[0][y]^1 and ls[1][x] == ls[1][y]^1 and ls[2][x] == ls[2][y]^1:
        return -1
    else:
        return 0

def issig(x):
    if ls[0][x] == ls[1][x] and ls[1][x] == ls[2][x]:
        if ls[0][x] == 1:
            return 1
        else:
            return -1
    else:
        return 0

delst = set()
res = list()

for i in range(n):
    jug = issig(i)
    if jug != 0:
        if jug == 1:
            delst.add(i)
            res.append('!x'+str(i+1)+" -> x"+str(i+1))
        elif jug == -1:
            delst.add(i)
            res.append('x'+str(i+1)+" -> !x"+str(i+1))

for i in range(n):
    if i in delst: continue
    for j in range(i+1,n,1):
        if j in delst: continue
        jug = isequ(i,j)
        if jug == 1:
            delst.add(j)
            res.append('x'+str(i+1)+" -> x"+str(j+1))
            res.append('!x'+str(i+1)+" -> !x"+str(j+1))
        elif jug == -1:
            delst.add(j)
            res.append('x'+str(i+1)+" -> !x"+str(j+1))
            res.append('!x'+str(i+1)+" -> x"+str(j+1))

free = set(range(n))-delst
freels = list(free)
flg = 1

if len(free) > 2:
    flg = -1
else:
    if len(free) == 2:
        typ = 15
        for i in range(3):
            if ls[i][freels[0]] == 0 and ls[i][freels[1]]==0:
                typ -= 1
            elif ls[i][freels[0]] == 0 and ls[i][freels[1]]==1:
                typ -= 2
            elif ls[i][freels[0]] == 1 and ls[i][freels[1]]==0:
                typ -= 4
            elif  ls[i][freels[0]] == 1 and ls[i][freels[1]]==1:
                typ -= 8
        if typ == 1:
            res.append('!x'+str(freels[0]+1)+" -> x"+str(freels[1]+1))
        elif typ == 2:
            res.append('!x'+str(freels[0]+1)+" -> !x"+str(freels[1]+1))
        elif typ == 4:
             res.append('x'+str(freels[0]+1)+" -> x"+str(freels[1]+1))
        elif typ == 8:
             res.append('x'+str(freels[0]+1)+" -> !x"+str(freels[1]+1))
if flg == -1:
    print(-1)
else:
    print(len(res))
    for each_str in res:
        print(each_str)



