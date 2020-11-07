import random
import sys

if(len(sys.argv) != 3):
	exit(0)

if(not sys.argv[1].isdigit()):
	exit(0)

n = int(sys.argv[1])
ret = [sys.argv[1]+'\n']
m = [-1 for i in range(n)]

for i in range(n):
	if(m[i] != -1):
		continue;
	j = random.randint(0, n-1)
	while(i==j or m[j] != -1):
		j = random.randint(0, n-1)
	m[i] = j
	m[j] = i

for i in range(n):
	if(m[i] != -1):
		ret.append(str(i) + ' ' + str(m[i]) + '\n')
		m[m[i]] = -1

with open(sys.argv[2], 'w') as f:
	f.writelines(ret)
