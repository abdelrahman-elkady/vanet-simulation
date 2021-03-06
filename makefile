# export the following ENV_VARS before running the make file (i.e. run export X=Y && make)
#
# SUMO_TOOLS = path_to_sumo_tools_dir (example: usr/share/sumo/tools)
# NS_HOME = path_to_ns_installation_dir (example: $HOME/Downloads/ns3/ns-allinone-3.26/ns-3.26)
# PROJECT_ROOT = Current Dir EPIC FAIL To get it programmatically :D
#

all: check_env generate_network prepare_dump run_simiulation

sumo: generate_network
	sumo-gui -c main.sumocfg

# NS_LOG="AodvRoutingTable"  # AodvRoutingProtocol || AodvRoutingTable
run_simiulation: copy_ns2_file
	cd $(NS_HOME) && ./waf --run 'scratch/ns2-mobility-trace --traceFile=scratch/ns2mobility.tcl --nodeNum=27 --duration=45.0' # > $(PROJECT_ROOT)main-ns2-mob.log 2>&1
	# Copy the trace logs
	cd $(NS_HOME) && cp aodv.routes $(PROJECT_ROOT)trace && cp wifi-tracing.tr $(PROJECT_ROOT)trace

copy_ns2_file:
	cp ns2-mobility-trace.cc $(NS_HOME)/scratch

generate_network:
	netconvert -n main.nod.xml -e main.edg.xml -o main.net.xml
	duarouter -n main.net.xml -f main.flow.xml -o main.rou.xml

prepare_dump:
	sumo -c main.sumocfg --fcd-output sumoTrace.xml
	$(SUMO_TOOLS)/traceExporter.py --fcd-input sumoTrace.xml --ns2mobility-output ns2mobility.tcl
	$(SUMO_TOOLS)/traceExporter.py --fcd-input sumoTrace.xml --ns2activity-output ns2activity.tcl
	$(SUMO_TOOLS)/traceExporter.py --fcd-input sumoTrace.xml --ns2config-output ns2config.tcl

	cp ns2mobility.tcl $(NS_HOME)/scratch
	cp ns2activity.tcl $(NS_HOME)/scratch
	cp ns2config.tcl $(NS_HOME)/scratch


check_env:
ifndef SUMO_TOOLS
  export SUMO_TOOLS=/usr/share/sumo/tools
endif
ifndef NS_HOME
	export NS_HOME=$(HOME)/Downloads/ns3/ns-allinone-3.26/ns-3.26
endif
	export PROJECT_ROOT=$(HOME)/projects-workspace/GUC/CSEN_1066_NETW/project-02-vanet/
