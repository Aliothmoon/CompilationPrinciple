{ {
int int
ID sum
; ;
int int
ID mul
; ;
int int
ID i
; ;
read read
ID sum
; ;
read read
ID mul
; ;
write write
ID sum
; ;
write write
ID mul
; ;
for for
( (
ID i
= =
NUM 1
; ;
ID i
<= <=
NUM 10
; ;
ID i
= =
ID i
+ +
NUM 1
) )
{ {
ID sum
= =
ID i
+ +
ID sum
; ;
ID mul
= =
ID i
* *
ID mul
; ;
} }
write write
ID sum
; ;
write write
ID mul
; ;
} }