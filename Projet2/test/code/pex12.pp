var X2 : integer

defun foo(X : integer) : integer
    if X = 0 then foo := 0 else foo := foo(X-1)


X2 := 4;
X2 := foo(X2)