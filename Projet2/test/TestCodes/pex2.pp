var X1 : array of array of array of integer,
var X2 : array of array of array of boolean

X1 := new array of array of array of integer[3];
X2 := new array of array of array of boolean[3];
X1[0][0][0] = 0;
X1[0][0][1] = 1;
X1[0][0][2] = 2;
X1[0][1][0] = 3;
X1[0][1][1] = 4;
X1[0][1][2] = 5;
X1[1][1][0] = 6;
X1[1][1][1] = 7;
X2[0][0][0] = true;
X2[0][0][1] = true;
X2[0][0][2] = true;
X2[0][1][0] = false;
X2[0][1][1] = false;
X2[0][1][2] = false;
X2[1][1][0] = true;
X2[1][1][1] = true;
X2[1][1][2] = true;
