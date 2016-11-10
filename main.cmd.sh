#### [1] Find SUMO Tools here if installed with dpkg [APT] on Linux ####
# usr/share/sumo/tools

#### [2] Creating the network file ####
#
# netconvert -n $NODE_FILE -e $EDGE_FILE -o $TO_BE_GENERATED_OUTPUT_NETWORK_FILE
#
# Example:
# netconvert -n example.nod.xml -e example.edg.xml -o example.net.xml

#### [3] export netstate dump ####
#
# sumo -n example.net.xml -r example.rou.xml --netstate-dump sumoTrace.xml

#### [4] Exporting the trace file ####
#
# $PATH_TO_TRACE_EXPORTER is in your tools dir, check number [1]
# $PATH_TO_TRACE_EXPORTER --fcd-input sumoTrace.xml --ns2mobility-output ns2mobility.tcl
