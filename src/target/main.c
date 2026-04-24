# include "ft_malcolm.h"

/* TODO: 
	- To keep it simple this program will just send an arp addr to
		someone to be poisoned by malcolm
*/

int main(int argc, char **argv) {
	if (argc != 5) {
		printf_fd(2, "[ERROR] main : Invalid number of parameters.\n");
		return(1);
	}

	int	val = 1;
	int	sockfd = socket(AF_PACKET, SOCK_RAW, 0); // * need sudo to workl
	if (sockfd < 0) {
		printf_fd(2, "[ERROR] main : Failed to create the socket.\n");
		return (1);
	}
	if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &val, sizeof(val)) < 0) {
		printf_fd(2, "[ERROR] main : Couldn't set socket option, %s.\n", strerror(errno));
		return(close(sockfd), 1);
	}

	t_malcolm	*data = init_struct(argv[1], argv[2], argv[3], argv[4]);
	if (data == NULL) {
		return(close(sockfd), 1);
	}
	data->sockfd = sockfd;

	if (set_sockadrr_ll(&(data->addr), data->dst_mac_addr) < 0) {
		printf_fd(2, "[ERROR] main : Couldn't set sockaddr_ll.\n");
		return(clean_malcolm(data), 1);
	}

	if (set_frame(data, REQUEST) < 0) {
		printf_fd(2, "[ERROR] main : Couldn't set frame.\n");
		return(clean_malcolm(data), 1);
	}

	sendto(sockfd, &data->buf, sizeof(data->buf), 0, (struct sockaddr *)&data->addr, sizeof(data->addr));
	clean_malcolm(data);
	return(0);
}