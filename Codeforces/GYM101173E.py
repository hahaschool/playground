st = set()
visa = set()
visb = set()
visc = set()
k = -1
n = -1

def bfs():
    global st,visa,visb,visc,k,n
    que = list()
    que.append([0,1,k])
    while n > 0:
        a = que[-1][0]
        b = que[-1][1]
        c = que[-1][2]
        que.pop()
        if a < 0 or b < 0 or c < 0:
            continue
        ls = [a,b,c]
        ls.sort()
        if ls[0] in visa and ls[1] in visb and ls[2] in visc:
            continue;
        visa.add(ls[0])
        visb.add(ls[1])
        visc.add(ls[2])
        if a not in st and b not in st and c not in st:
            if a != 0 and b != 0 and c != 0:
                print(" ".join([str(a),str(b),str(c)]))
                st.add(a)
                st.add(b)
                st.add(c)
                n = n-1
        que.insert(0,[b*k+c*k-a,b,c]);
        que.insert(0,[a,a*k+c*k-b,c]);
        que.insert(0,[a,b,k*a+k*b-c]);

k,n = map(int,raw_input().split())
bfs()

