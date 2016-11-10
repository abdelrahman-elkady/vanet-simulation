#### [1] Find SUMO Tools here if installed with dpkg [APT] on Linux ####
# usr/share/sumo/tools

#### [2] Creating the network file ####
#
# netconvert -n $NODE_FILE -e $EDGE_FILE -o $TO_BE_GENERATED_OUTPUT_NETWORK_FILE
#
# Example:
# netconvert -n main.nod.xml -e main.edg.xml -o main.net.xml

#### [3] export netstate dump ####
#
# sumo -c main.sumocfg --fcd-output sumoTrace.xml

#### [4] Exporting the trace file ####
#
# $PATH_TO_TRACE_EXPORTER is in your tools dir, check number [1]
# $PATH_TO_TRACE_EXPORTER --fcd-input sumoTrace.xml --ns2mobility-output ns2mobility.tcl




############ NS ############
#
# cp ns2-mobility-trace.cc  $NS3_INSTALLATION_DIR/ns3/ns-allinone-3.26/ns-3.26/examples/scratch/
