var X1 : integer,
var X2 : integer,
var X3 : array of integer,
var X4 : array of array of integer

X3 := new array of integer[100];
if (X1 < X2)
    then
        X1 := X3[(X1 + X2) * 10]
    else
        X1 := X3[1]
