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

$ns duplex-link $n0 $n1 2mb 10ms DropTail 
$ns duplex-link $n1 $n2 2mb 10ms DropTail

#$ns queue-limit $n1 $n2 10

$ns duplex-link-op $n1 $n0 orient left
$ns duplex-link-op $n1 $n2 orient right

set tcp0 [new Agent/TCP]
set sink2 [new Agent/TCPSink] 

$ns attach-agent $n0 $tcp0
$ns attach-agent $n2 $sink2

set ftp [new Application/FTP]
$ftp attach-agent $tcp0
#$ftp set type_ FTP

$tcp0 set fid_ 1

#set cbr [new Application/Traffic/CBR]
#$cbr attach-agent $tcp0
#$tcp0 set fid_ 2

$ns connect $tcp0 $sink2

proc finish { } {

    global ns f fr
    $ns flush-trace
    close $f
    close $fr
    exec nam out.nam &
    
}

#perform same for cbr below instead of ftp
$ns at 0.1 "$ftp start"
$ns at 1.5 "$ftp stop"
$ns at 2.0 "finish"  

$ns run
