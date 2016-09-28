reset
set ylabel 'time (10e-6 s)'
set style fill solid
set title 'clz time compare'
set term png enhanced font 'Verdana,10'
set output 'result.png'
#set format y "%.6f"

plot [:][0:2] 'output/output_clz_binary_search.txt' using 1:2 with linespoints title "binary_search", \
	'output/output_clz_Harley.txt' using 1:2 with linespoints title "Harley" \
#	'output/output_clz_recursive.txt' using 1:2 with linespoints title "recursive", \
#	'output/output_clz_byte_shift.txt' using 1:2 with linespoints title "byte_shift", \
#	'output/output_clz_iteration.txt' using 1:2 with linespoints title "iteration"
