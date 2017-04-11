var X1 : integer,
var X2 : integer

defun foo2(X : integer):integer
    var T : integer
    T := 1;
    foo2 := X+T

defun foo2(V : integer):integer
    var Z : integer
    foo2:= V-1
    


X2 := 3;
if true
   then X1 := foo2(X1)
   else X1 := foo2(X2)
