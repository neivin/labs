# Write a program that builds a string containing:
# X < i > Y such that divisibl by M and not a multiple of N
# X,Y,M,N -> inputted from stdin

import sys;

arglist = sys.argv;

x = int(arglist[1])
y = int(arglist[2])
m = int(arglist[3])
n = int(arglist[4])

output = "";

for i in xrange(x,y):
    if (i%m == 0) and (i%n != 0):
        output += str(i) + ','

print "Built string: " + output

print "Last 15 characters:" + output[-15:]
