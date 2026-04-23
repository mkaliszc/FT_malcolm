# include "ft_malcolm.h"

/* TODO: 
	- To keep it simple this program will just send an arp addr to
		someone to be poisoned by malcolm
*/

int main(int argc, char **argv) {
	if (argc !=  2) {
		printf_fd(2, "[ERROR] : Invalid number of parameters.\n");
		return(1);
	}

	int	val = 1;
	int	sockfd = socket(AF_PACKET, SOCK_RAW, 0);
	if (sockfd < 0) {
		printf_fd(2, "[ERROR] : Failed to create the socket.\n");
		return (1);
	}
	if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &val, sizeof(val)) < 0) {
		printf_fd(2, "[ERROR] : Couldn't set socket option, %s.\n", strerror(errno));
		return(close(sockfd), 1);
	}

	t_malcolm	*data = init_t_malcolm(argv[1], "FF:FF:FF:FF:FF:FF");
	if (data == NULL) {
		return(close(sockfd), 1);
	}
	data->sockfd = sockfd;

	if (set_sockadrr_ll(data->addr, data->dst_mac_addr) < 0) {
		printf_fd(2, "[ERROR] : Couldn't set sockaddr_ll.\n");
		return(clean_malcolm(data), 1);
	}

	if (set_frame(data->buf, data->dst_mac_addr, data->src_mac_addr) < 0) {
		printf_fd(2, "[ERROR] : Couldn't set frame.\n");
		return(clean_malcolm(data), 1);
	}

	// sendto
}