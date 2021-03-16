reset
set xlabel 'offset'
set ylabel 'time (ns)'
set title 'fibdrv kernel vs userspace'
set term png enhanced font 'Verdana,10'
set output 'plot_output.png'
set grid
plot [0:92][0:1800] \
'out_plot' using 1:3 with linespoints linewidth 2 title "kernel",\
'' using 1:4 with linespoints linewidth 2 title "userspace",\
'' using 1:5 with linespoints linewidth 2 title "kernel to userspace",\
