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

using namespace ns3;

// Callback for recieving UDP packet
void ReceivePacket (Ptr<Socket> socket){
  NS_LOG_UNCOND ("PACKET RECIEVED");
}

int main (int argc, char *argv[]) {

  std::string traceFile;
  std::string logFile;

  int    nodeNum;
  double duration;

  // Parse command line attribute
  CommandLine cmd;
  cmd.AddValue ("traceFile", "Ns2 movement trace file", traceFile);
  cmd.AddValue ("nodeNum", "Number of nodes", nodeNum);
  cmd.AddValue ("duration", "Duration of Simulation", duration);
  cmd.AddValue ("logFile", "Log file", logFile);
  cmd.Parse (argc,argv);

  // open log file for output
  std::ofstream os;
  os.open (logFile.c_str ());

  WifiHelper wifi;
  wifi.SetStandard (WIFI_PHY_STANDARD_80211b);

  NqosWifiMacHelper wifiMac = NqosWifiMacHelper::Default ();
  YansWifiPhyHelper wifiPhy = YansWifiPhyHelper::Default ();

  YansWifiChannelHelper wifiChannel;
  wifiChannel.SetPropagationDelay ("ns3::ConstantSpeedPropagationDelayModel");
  wifiChannel.AddPropagationLoss ("ns3::FriisPropagationLossModel");
  wifiPhy.SetChannel (wifiChannel.Create ());


  NodeContainer c;
  c.Create (150);
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

  // Setting UDP application
  uint16_t Port = 12345;

  TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");

  Ptr<Socket> recvSink = Socket::CreateSocket (c.Get (71), tid);
  InetSocketAddress local = InetSocketAddress ((Ipv4Address::GetAny()), Port);
  recvSink->Bind (local);
  recvSink->SetRecvCallback (MakeCallback (&ReceivePacket));

  Ptr<Socket> source;
  source = Socket::CreateSocket (c.Get (23), tid);
  InetSocketAddress remote = InetSocketAddress (("10.1.1.72"), Port);
  source->Connect (remote);


  Simulator::Stop (Seconds (duration));
  Simulator::Run ();
  Simulator::Destroy ();

  os.close (); // close log file
  return 0;
}
