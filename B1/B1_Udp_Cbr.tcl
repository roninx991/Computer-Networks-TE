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

#$ns queue-limit $n1 $n2 5

set udp0 [new Agent/UDP]
set null [new Agent/Null]

$ns attach-agent $n0 $udp0
$ns attach-agent $n2 $null

$udp0 set fid_ 1

set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp0
#$cbr set packet_size_ 500
#$cbr set rate_ 1mb

$ns connect $udp0 $null

proc finish { } {

    global ns f fr
    $ns flush-trace
    close $f
    close $fr
    exec nam out.nam &
    
}
$ns at 0.1 "$cbr start"
$ns at 4.0 "$cbr stop"
$ns at 4.2 "finish"  

$ns run
