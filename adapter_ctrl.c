#include<stdio.h>
#include<string.h>
int main(int argc, char *argv[]) {
	if(!strcmp(argv[1],"enable"))
		system("netsh interface set interface name=\"Wi-Fi\" admin=enabled & "
			"netsh interface set interface name=\"이더넷\" admin=enabled &"
			"netsh interface set interface name=\"Bluetooth 네트워크 연결\" admin=enabled");
	else if(!strcmp(argv[1], "disable"))
		system("netsh interface set interface name=\"Wi-Fi\" admin=disabled & "
			"netsh interface set interface name=\"이더넷\" admin=disabled &"
			"netsh interface set interface name=\"Bluetooth 네트워크 연결\" admin=disabled");
	return 0;
}