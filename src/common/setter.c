# include "ft_malcolm.h"

int	set_sockadrr_ll(struct sockaddr_ll *addr, char **mac_address) {
	int	ifid = find_interface();
	
	if (ifid == 0) {
		printf_fd(2, "[INFO] : No valid interface found.\n");
		return(-1);
	}

	ft_memset(addr, 0, sizeof(addr));
	addr->sll_family = AF_PACKET;
	addr->sll_ifindex = ifid;
	addr->sll_halen = 6;
	fill_mac_address(addr->sll_addr, mac_address);

	return(0);
}

int	set_frame(struct s_frame *buf, char **mac_address_dst, char **mac_address_src) {
	fill_mac_address(buf->eth.dst, mac_address_dst);
	fill_mac_address(buf->eth.src, mac_address_src);
	buf->eth.ethertype = 0x0806;
	
	// TODO : fill arp
	return(0);
}