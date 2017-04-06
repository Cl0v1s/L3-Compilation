var X1 : integer,
var X2 : integer

defpro proo(X : integer, Y : boolean)
    var Z : integer, var U : integer
    X1:= X+1;
    X1 := X1+1
    
defun foo(X : integer, Y : boolean):integer
    var T : integer, var U : integer
    T := 20;
    if Y
       then foo := X + T
       else foo := X - T

X2 := 10;
if false then
{
    proo(X2,true)
}
else
{
    X2 := foo(X2,false)
};
X2 := X2 - 1

