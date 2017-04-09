var X1 : array of integer,
var X2 : array of array of integer,
var I : integer,
var S1 : integer,
var S2  integer

X1 := new array of integer[5];
X2 := new array of array of integer[5];
I := 0;
S1 := 5;
S2 := 5;
while I < S1 do
    X1[I] := I;
    I := I + 1

I := 0;

while I < S2 do
    X2[I][I] = X1[I];
    I := I + 1;


