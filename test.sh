local="$(cd "$(dirname "$0")"; pwd)"
tool="$local/bin/ipmt"
file="$1"
time='/usr/bin/time --quiet -f "%E"'

if [ $1 = "clean" ]; then
    rm -f {*.i,*.p,*.s}
    exit 0
fi

if [ ! -f $file ]; then
    echo 'Falta arquivo válido'
    exit 1
fi

function i() {
    i=''
    p=''
    s=''
    filec=$(echo -n $file | sed s/[.][a-zA-Z0-9]*$//)
    filec+=".idx"
    p+=$(echo -en 'RAW ' && ls -lah $file | awk '{print $5}')
    
    i+=$(echo -en '\nLZ78 ' && $time $tool index -z LZ78 $file 2>&1)
    p+=$(echo -en '\nLZ78 ' && (ls -lah $filec | awk '{print $5}'))
    s+=$(echo -en '\nLZ78 ' && $time $tool search a $filec 2>&1 >/dev/null)


    i+=$(echo -en '\nLZ77 ' && $time $tool index -z LZ77 $file 2>&1)
    p+=$(echo -en '\nLZ77 ' && (ls -lah $filec | awk '{print $5}'))
    s+=$(echo -en '\nLZ77 ' && $time $tool search a $filec 2>&1 >/dev/null)



    i+=$(echo -en '\nGZIP ' && $time gzip -kf $file 2>&1)
    p+=$(echo -en '\nGZIP ' && (ls -lah $file.gz | awk '{print $5}'))
    s+=$(echo -en '\nGZIP ' && $time gzip -df $file.gz 2>&1)

    rm $filec

    echo "$i" > $file.i
    echo "$p" > $file.p
    echo "$s" > $file.s
}



# i=0
# while read pat; do
#     ((i++))

#     ("$time" $tool "search" "$pat" $file | wc -l) 2>> $save
# done < $patfile

# cat $save | sed s/'^.*:'// | nl > $save.i
# rm $save

# gnuplot -p -e "set term png;
# set output '$1.png';
# set xlabel '$xlabel';
# set ylabel '$ylabel';
# set grid back ls 0;
# filelist=system('ls $file.i*');
# plot for [filename in filelist]
#     filename using 2:1 title filename[*:(strlen(filename)-3)]
# w lp pt 1 ps 1"
i