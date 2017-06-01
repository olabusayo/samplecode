#!/usr/bin/python

total_1 = 1; # This is global variable.
total_2 = 2;

# Function definition is here
def sum( arg1, arg2 ):
   # Add both the parameters and return them."
   global total_1
   total_1 = arg1 + arg2; # Here total_1 is global variable due to statement above.
   total_2 = arg1 + arg2; # Here total_2 is local variable.
   print "Inside the function global total_1 : ", total_1, "\t total_2 : ", total_2

# Now you can call sum function
sum( 10, 20 );
print "Outside the function global total_1 : ", total_1, "\t total_2  : ", total_2
