var X1 : integer,
var X2 : integer,
var X3 : array of integer,
var X4 : array of array of integer

X3 := new array of integer[100];
X3[1] := 12;
X2 := 1;
X3[(X1 + X2) * 10] := 14;
if (X1 < X2)
    then
        X1 := X3[(X1 + X2) * 10]
    else
        X1 := X3[1]
