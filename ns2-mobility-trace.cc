#include <iostream>
#include <fstream>
#include <sstream>

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/ns2-mobility-helper.h"
#include "ns3/aodv-module.h"
#include "ns3/aodv-helper.h"
#include "ns3/wifi-helper.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/ipv4-address-helper.h"
#include "ns3/wifi-phy.h"
#include "ns3/wifi-mac.h"
#include "ns3/internet-stack-helper.h"
#include "ns3/type-id.h"
#include "ns3/nqos-wifi-mac-helper.h"
#include "ns3/trace-helper.h"
#include "ns3/animation-interface.h"

using namespace ns3;

int main (int argc, char *argv[]) {

  std::string traceFile;

  int    nodeNum;
  double duration;

  // Parse command line attribute
  CommandLine cmd;
  cmd.AddValue ("traceFile", "Ns2 movement trace file", traceFile);
  cmd.AddValue ("nodeNum", "Number of nodes", nodeNum);
  cmd.AddValue ("duration", "Duration of Simulation", duration);
  cmd.Parse (argc,argv);

  WifiHelper wifi;
  wifi.SetStandard (WIFI_PHY_STANDARD_80211b);

  NqosWifiMacHelper wifiMac = NqosWifiMacHelper::Default ();
  YansWifiPhyHelper wifiPhy = YansWifiPhyHelper::Default ();

  YansWifiChannelHelper wifiChannel;
  wifiChannel.SetPropagationDelay ("ns3::ConstantSpeedPropagationDelayModel");
  wifiChannel.AddPropagationLoss ("ns3::FriisPropagationLossModel");
  wifiPhy.SetChannel (wifiChannel.Create ());

  NodeContainer c;
  c.Create (nodeNum);

  Ns2MobilityHelper ns2 = Ns2MobilityHelper (traceFile);
  ns2.Install ();
  NetDeviceContainer devices = wifi.Install (wifiPhy, wifiMac, c);

  AodvHelper aodv;
  InternetStackHelper internet;
  internet.SetRoutingHelper (aodv);
  internet.Install (c);

  Ipv4AddressHelper ipv4;
  ipv4.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer i = ipv4.Assign (devices);

  // AODV Route table snapshot
  Ptr<OutputStreamWrapper> routingStream = Create<OutputStreamWrapper> ("aodv.routes", std::ios::out);
  aodv.PrintRoutingTableAllAt (Seconds (8), routingStream);

  AsciiTraceHelper ascii;
  wifiPhy.EnableAsciiAll (ascii.CreateFileStream ("wifi-tracing.tr"));

  // Export an animation xml trace
  AnimationInterface anim ("vanet-animation.xml");
  anim.EnableIpv4RouteTracking ("route-tracking.xml", Seconds(5), Seconds(25), Seconds(1));
  anim.EnablePacketMetadata (true);

  Simulator::Stop (Seconds (duration));
  Simulator::Run ();
  Simulator::Destroy ();

  return 0;
}
