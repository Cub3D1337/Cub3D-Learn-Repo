Learn about Ray-Casting principles
Learn Super Fast Ray Casting in Tiled Worlds using DDA

I have a right-angle triangle (dx - dy - c)

m = dy / dx, if dx = 1
m = dy / 1
dy = m * 1 = m

Then from
c =  √dx**2 + dy**2
we get
c =  √1**2 + m**2  =  √dx**2 + (dy/dx)**2

so the previous formula describe the lenth of hypotenuse after 1 unit move across (x-axe)
Then if i want to determie the lenght of hypotenuse after x unit simply I do:
Sx = √1**2 + (dy/dx)**2
so;
c = dx * Sx

Same think i want to determie the lenth of hypotenuse after 1 unit move across (y-axe):
I do:
Sy = √1**2 + (dx/dy)**2
so;
c = dy * Sy

## Sources
[ DDA Raycasting algorithm ](https://www.youtube.com/watch?v=IDmWuSrEkow&ab_channel=kitrofimov)

