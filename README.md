# Link-disjoint-routing-and-MPLS
Instruction for the cpp file sol1.cpp

-->the input file topology file and connection file should be available 
   in same directory in sol1.cpp
-->How to run
-----------------
$g++ sol1.cpp -o sol1
./sol1 -top top14.txt -conn NSFNET_100.txt -rt routing.txt -ft forwading.txt -path path.txt -flag hop -p 1

Then the four csaes for each network:
_____________________________________________
output file formate:routing14_dist_0.txt here
14 : topology file top14.txt and connection file NSFNET_100.txt is used
dist : flag dist is used
0 : p=0 (Optimistic Approach)

$./sol1 -top top14.txt -conn NSFNET_100.txt -rt routing14_dist_0.txt -ft forwading14_dist_0.txt -path path14_dist_0.txt -flag dist -p 0
$./sol1 -top top14.txt -conn NSFNET_100.txt -rt routing14_dist_1.txt -ft forwading14_dist_1.txt -path path14_dist_1.txt -flag dist -p 1
$./sol1 -top top14.txt -conn NSFNET_100.txt -rt routing14_hop_0.txt -ft forwading14_hop_0.txt -path path14_hop_0.txt -flag hop -p 0
$./sol1 -top top14.txt -conn NSFNET_100.txt -rt routing14_hop_1.txt -ft forwading14_hop_1.txt -path path14_hop_1.txt -flag hop -p 1


$./sol1 -top top24.txt -conn ARPANET_100.txt -rt routing24_dist_0.txt -ft forwading24_dist_0.txt -path path24_dist_0.txt -flag dist -p 0
$./sol1 -top top24.txt -conn ARPANET_100.txt -rt routing24_dist_1.txt -ft forwading24_dist_1.txt -path path24_dist_1.txt -flag dist -p 1
$./sol1 -top top24.txt -conn ARPANET_100.txt -rt routing24_hop_0.txt -ft forwading24_hop_0.txt -path path24_hop_0.txt -flag hop -p 0
$./sol1 -top top24.txt -conn ARPANET_100.txt -rt routing24_hop_1.txt -ft forwading24_hop_1.txt -path path24_hop_1.txt -flag hop -p 1



File Formats:
--------------------------------------------------------------------------------------------------------

1. Routing Table: 

	- [ Destination Node ||Path || Path Cost ]
	- For each node, two consecutive lines represent the shortest and second-shortest paths respectively for the current source-destination pair.

2. Forwarding file( for each admitted connection):
	- [ Interface in || Label in || Interface out || Label out ] 

3. path file (for each admitted connection):
	- [Connection Id || Source || Destination || path || Label List || Path Cost ]





