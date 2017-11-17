set ns [new Simulator]

$ns color 1 Green
$ns color 2 Red

set nf [open out.nam w]
$ns namtrace-all $nf
set f [open outtr.tr w]
$ns trace-all $f

proc finish {} {
        global ns nf
        $ns flush-trace
	close $nf
	exec nam out.nam &
	exit 0

}

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]

#define connection
$ns duplex-link $n0 $n1 2Mb 10ms DropTail
$ns duplex-link $n1 $n2 2Mb 10ms DropTail

#set queue size
$ns queue-limit $n1 $n2 100.

#SRC_AGENT(src)
set src [new Agent/TCP]
$src set class_ 1
$ns attach-agent $n0 $src

#DEST_AGENT(dest)
set dest [new Agent/TCPSink]

$ns attach-agent $n2 $dest


$ns connect $src $dest
$src set fid_ 2

#FTP traffic

set ftp [new Application/FTP]
$ftp attach-agent $src
$ftp set type_ FTP

$ns at 0.1 "$ftp start"
$ns at 1.0 " $ftp stop"

$ns at 5.0 "finish"

$ns run
