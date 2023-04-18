def f(x, a):
    return not(x%a==0) <= ((x%24==0) <= not(96%x==0) )
l =0    
for a in range(1000):
    k = True
    for x in range(1000):
        if f(x, a):
             l+=1
        else:
            k =False
            break
    if k:
        print(a)