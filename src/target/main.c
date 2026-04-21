# include "ft_malcolm.h"

/* TODO: 
	- To keep it simple this program will just send an arp addr to
		someone to be poisoned by malcolm
*/

int main() {
	struct sockaddr_ll	*addr;
	t_frame				*buf;
	int					val = 1;
	int					sockfd = socket(AF_PACKET, SOCK_RAW, 0);
	

	if (sockfd < 0) {
		printf_fd(2, "[ERROR] : Failed to create the socket\n");
		return(close(sockfd), 1);
	}

	if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &val, sizeof(val)) < 0) {
		printf_fd(2, "[ERROR] : Couldn't set socket option, %s\n", strerror(errno));
		return(close(sockfd), 1);
	}

	addr = malloc(sizeof(struct sockaddr_ll));
	if (addr == NULL) {
		return(printf_fd(2,"[ERROR] : malloc error.\n"));
	}

	if (set_sockadrr_ll(addr) < 0) {
		printf_fd(2, "[ERROR] : Couldn't set sockaddr_ll\n");
		return(close(sockfd), free(addr), 1);
	}

	if (set_target_frame(buf) < 0) {

	}

	// sendto(sockfd);
}