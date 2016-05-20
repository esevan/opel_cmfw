#!/bin/bash

WFD_DIR=/tmp/wifi/wifi-direct/
INIT_PATH=/tmp/wifi/wifi-direct/init
WFD_STAT_PATH=/tmp/wifi/wifi-direct/wfd_stat
DHCP_STAT_PATH=/tmp/wifi/wifi-direct/dhcp_stat
IFACE_PATH=/tmp/wifi/wifi-direct/iface

P2P_CONF_PATH="/home/pi/workspace/hostap/wpa_supplicant/p2p.conf"
DHCP_CONF_PATH="/home/pi/workspace/dhcp/dhcpd.conf"


init_wf()
{
	sudo mkdir -p ${WFD_DIR}
	sudo mkdir -p ${INIT_PATH}
	sudo mkdir -p ${WFD_STAT_PATH}
	sudo mkdir -p ${DHCP_STAT_PATH}
	sudo mkdir -p ${IFACE_PATH}
	
	sudo touch ${INIT_PATH}/self
	sudo echo 0 > ${INIT_PATH}/self
	sudo touch ${WFD_STAT_PATH}/self
	sudo touch ${IFACE_PATH}/self
	sudo touch ${DHCP_STAT_PATH}/self
	sudo echo 0 > ${WFD_STAT_PATH}/self
	sudo echo 0 > ${DHCP_STAT_PATH}/self
	sudo echo 1 > ${INIT_PATH}/self
}
start_wfd()
{
	sudo ifconfig wlan0 up
	sudo wpa_supplicant -Dnl80211 -iwlan0 -c${P2P_CONF_PATH} -Bd
	sudo wpa_cli p2p_group_add
	P2P_IFNAME=`ifconfig | awk '/p2p/ {print $1}'`
	echo ${P2P_IFNAME} > ${IFACE_PATH}/self
	sudo ip addr add 192.168.49.1/24 brd 192.168.49.255 dev ${P2P_IFNAME}
	sudo ifconfig ${P2P_IFNAME} 192.168.49.1 up
	sudo wpa_cli wps_pbc
	sudo udhcpd ${DHCP_CONF_PATH} -f &
	sleep 1;
}

stop_wfd()
{
	sudo pkill -x udhcpd
	sudo echo 0 > ${DHCP_STAT_PATH}/self

	sudo pkill -x wpa_supplicant
	sudo ifconfig wlan0 down
	sudo echo 0 > ${WFD_STAT_PATH}/self
}

case $1 in
"start")
start_wfd
;;
"stop")
stop_wfd
;;
"init")
init_wf
;;
*)
/bin/echo $0 [init/start/stop]
exit 1
;;
esac
