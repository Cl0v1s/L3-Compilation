var X3 : array of integer,
var X4 : array of array of integer

X3 := new array of integer[4];
X3[0] := 12;
X4 := new array of array of integer[3];
X4[0] := X3;
X4[0][0] := 2;
X4[1] := X4[0];
X4[1][1] := X4[0][0]


