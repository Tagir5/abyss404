def f(x, a):
  return ((x % 24 == 0) and (96 % x == 0)) <= (x % a == 0)


l = 0
for a in range(1000):
  k = True
  for x in range(1000):
    if f(x, a):
      l += 1
    else:
      k = False
      break
  if k:
    print(a)
