reset
set xlabel 'count'
set ylabel 'time (ns)'
set title 'loop vs clz'
set term png enhanced font 'Verdana,10'
set output 'plot_clz_test.png'
set grid
plot [0:1000][0:70] \
'out_plot_clz' using 1:2 with linespoints linewidth 2 title "loop",\
'' using 1:3 with linespoints linewidth 2 title "clz",\
