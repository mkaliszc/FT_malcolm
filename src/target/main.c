# include "ft_malcolm.h"

/* TODO: 
	- To keep it simple this program will just send an arp addr to
		someone to be poisoned by malcolm
*/

// TODO : rewrite everything to adapt to struct s_malcolm

int main(int argc, char **argv) {
	char	**mac_address;
	char	**broadcast;

	if (argc !=  2) {
		printf_fd(2, "[ERROR] : Invalid number of parameters.\n");
		return(1);
	}
	mac_address = parse_mac_addr(argv[1]);
	if (mac_address == NULL) {
		printf_fd(2, "[ERROR] : Not a MAC adress.\n");
		return(1);
	}

	struct sockaddr_ll	*addr;
	t_frame				*buf;
	int					val = 1;
	int					sockfd = socket(AF_PACKET, SOCK_RAW, 0);
	

	if (sockfd < 0) {
		printf_fd(2, "[ERROR] : Failed to create the socket\n");
		return(ft_free_char_tab(mac_address), close(sockfd), 1);
	}

	if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &val, sizeof(val)) < 0) {
		printf_fd(2, "[ERROR] : Couldn't set socket option, %s\n", strerror(errno));
		return(close(sockfd), 1);
	}

	addr = malloc(sizeof(struct sockaddr_ll));
	if (addr == NULL) {
		return(ft_free_char_tab(mac_address), printf_fd(2,"[ERROR] : malloc error.\n"));
	}

	broadcast = parse_mac_adress("FF:FF:FF:FF:FF:FF");
	if (set_sockadrr_ll(addr, broadcast) < 0) {
		printf_fd(2, "[ERROR] : Couldn't set sockaddr_ll\n");
		return(ft_free_char_tab(mac_address), close(sockfd), free(addr), 1);
	}

	if (set_frame(buf, broadcast, mac_address) < 0) {

	}

	// sendto(sockfd);
}