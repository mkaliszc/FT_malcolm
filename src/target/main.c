# include "ft_malcolm.h"

/* TODO: 
	- To keep it simple this program will just send an arp request to
		someone to be poisoned by malcolm
*/

int main() {
	int	sockfd = socket(AF_PACKET, SOCK_RAW, 0);
	if (sockfd < 0) {
		printf_fd(2, "[ERROR] : Failed to create the socket\n");
	}

	int	val = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &val, sizeof(val));

	struct sockaddr_ll request;
	request.sll_family = AF_PACKET;
	request.sll_halen = 6;

	for(int i = 0; i < 6; i++) {
		request.sll_addr[i] = 0xFF;
	}
}