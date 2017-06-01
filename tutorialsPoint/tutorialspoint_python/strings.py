#!/usr/bin/python

from string import maketrans

intab="aeiou"
outtab="43102"
transtab=maketrans(intab, outtab)

str = "This is my test string that uses almost all vowels"
print str.translate(transtab)
str[0] = "P"
print str

