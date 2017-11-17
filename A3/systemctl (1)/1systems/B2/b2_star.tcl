set ns [new Simulator]

$ns color 1 Red
$ns color 2 Blue

set f [open "out.tr" w]
$ns trace-all $f

set fr [open "out.nam" w]
$ns namtrace-all $fr

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]

$ns duplex-link $n0 $n1 2mb 30ms DropTail
$ns duplex-link $n0 $n2 2mb 30ms DropTail
$ns duplex-link $n0 $n3 1.5mb 30ms DropTail
$ns duplex-link $n0 $n4 2mb 30ms DropTail
$ns duplex-link $n0 $n5 2mb 30ms DropTail

$ns queue-limit $n0 $n3 5

set tcp1 [new Agent/TCP]
$ns attach-agent $n1 $tcp1
set sink1_3 [new Agent/TCPSink]
$ns attach-agent $n3 $sink1_3

set cbr1 [new Application/Traffic/CBR]
$cbr1 attach-agent $tcp1
$cbr1 set packet_size_ 1000
$cbr1 set rate_ 1ms

$tcp1 set fid_ 1
$ns connect $tcp1 $sink1_3


set tcp2 [new Agent/TCP]
$ns attach-agent $n2 $tcp2 
set sink2_3 [new Agent/TCPSink]
$ns attach-agent $n3 $sink2_3 

set cbr2 [new Application/Traffic/CBR]
$cbr2 attach-agent $tcp2
$cbr2 set packet_size_ 1000
$cbr2 set rate_ 1ms

$tcp2 set fid_ 2
$ns connect $tcp2 $sink2_3

set tcp4 [new Agent/TCP]
$ns attach-agent $n4 $tcp4
set sink4_3 [new Agent/TCPSink]
$ns attach-agent $n3 $sink4_3

set ftp4 [new Application/FTP]
$ftp4 attach-agent $tcp4

$ns connect $tcp4 $sink4_3

proc finish { } {
	global ns f fr
	$ns flush-trace
	close $f
	close $fr
	exec nam out.nam &

}

$ns at 0.1 "$cbr1 start"
$ns at 4.0 "$cbr1 stop"
$ns at 1.0 "$cbr2 start"
$ns at 4.0 "$cbr2 stop"
$ns at 1.2 "$ftp4 start"
$ns at 4.5 "$ftp4 stop"
$ns at 5.0 "finish"

$ns run




