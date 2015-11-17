# Write a SHORT piece of code that demonstrates a side effect of python's
# method of passing by assignment

def modify(someList):
    someList[3] = 'not a four anymore hahahaha'

x = [1,2,3,4,5]

print "original list: " + str(x)

modify(x)

print "modified list: " + str(x)
