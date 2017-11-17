set ns [new Simulator]

$ns color 1 Red
$ns color 2 Blue

set f [open "out.tr" w]
$ns trace-all $f

set fr [open "out.nam" w]
$ns namtrace-all $fr

set n0 [$ns node]

set n1 [$ns node]
$n1 shape box

set n2 [$ns node]
set n3 [$ns node]

$ns duplex-link $n0 $n1 2mb 10ms DropTail
$ns duplex-link $n2 $n1 2mb 20ms DropTail
$ns duplex-link $n3 $n1 1.7mb 20ms DropTail

$ns queue-limit $n1 $n3 10

$ns duplex-link-op $n1 $n0 orient left-up
$ns duplex-link-op $n1 $n2 orient left-down
$ns duplex-link-op $n1 $n3 orient right

set tcp0 [new Agent/TCP]
$ns attach-agent $n0 $tcp0

$tcp0 set fid_ 1

set sink3 [new Agent/TCPSink]
$ns attach-agent $n3 $sink3

set ftp [new Application/FTP]
$ftp attach-agent $tcp0

$ns connect $tcp0 $sink3

set udp2 [new Agent/UDP]
$ns attach-agent $n2 $udp2

$udp2 set fid_ 2

set null3 [new Agent/Null]
$ns attach-agent $n3 $null3

set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp2
$cbr set packet_size_ 1000
$cbr set rate_ 1mb

$ns connect $udp2 $null3


proc finish { } {

	global ns f fr
	$ns flush-trace
	close $f
	close $fr
	exec nam out.nam &

}


$ns at 0.1 "$ftp start"
$ns at 1.0 "$cbr start"
$ns at 3.5 "$ftp stop"
$ns at 4.0 "$cbr stop"
$ns at 4.5 "finish"

$ns run


