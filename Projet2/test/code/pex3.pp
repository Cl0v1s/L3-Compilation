var X1 : integer,
var X2 : integer,
var X3 : boolean,
var X4 : boolean,
var X5 : array of boolean,
var X6 : array of integer

X2 := 5;
X5 := new array of boolean [6];
X5[0] := true;
X5[1] := false;
X5[2] := X5[1];
X5[1] := X2

