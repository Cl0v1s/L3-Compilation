var X1 : integer,
var X2 : integer,
var X3 : array of integer,
var X4 : array of array of integer

X3 := new array of integer[100];
X2 := 4;
X1 := 1;
while (X1 < X2) do
    {
    X1 := X3[(X1 + X2) * 10];
    X2 := X2 - 1
    }



