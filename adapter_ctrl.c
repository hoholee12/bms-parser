#include<stdio.h>
#include<string.h>
#include<windows.h>
int main(int argc, char *argv[]) {
	if (!strcmp(argv[1], "enable"))
		system(
			"netsh interface set interface name=\"이더넷\" admin=enabled &"
			"netsh interface set interface name=\"Bluetooth 네트워크 연결\" admin=enabled &"
			"netsh interface set interface name=\"VMware Network Adapter VMnet8\" admin=enabled &"
			"netsh interface set interface name=\"VMware Network Adapter VMnet1\" admin=enabled");
	else if (!strcmp(argv[1], "disable"))
		system(
			"netsh interface set interface name=\"이더넷\" admin=disabled &"
			"netsh interface set interface name=\"Bluetooth 네트워크 연결\" admin=disabled &"
			"netsh interface set interface name=\"VMware Network Adapter VMnet8\" admin=disabled &"
			"netsh interface set interface name=\"VMware Network Adapter VMnet1\" admin=disabled");
	Sleep(1000);
	return 0;
}