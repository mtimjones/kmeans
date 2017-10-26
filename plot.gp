set terminal x11
set palette model RGB defined (0 "red", 1 "blue", 2 "green")
set xrange[0:1000]
set yrange[0:1000]
plot ("data.txt") with points pt 2 palette
