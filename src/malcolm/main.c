# include "ft_malcolm.h"

/* TODO: 
	- Check parameters to be sure (order, host, etc)
	- create socket, recvfrom and sendto
	- Final goal is to wait for an arp request from the target and
		give an arp reply to poison the arp cache of the target.
*/

int main(int argc, char **argv) {
	int	sockfd = socket(AF_PACKET, SOCK_RAW, ETH_P_ARP);
}