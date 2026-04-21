# include "ft_malcolm.h"

int	find_interface() {
	struct ifaddrs	*interfaces_info;
	struct ifaddrs	*tmp;
	int				index = 0;

	if (getifaddrs(&interfaces_info) < 0) {
		printf_fd(2, "[ERROR] : couldn't get interface info, %s\n", strerror(errno));
		return(0);
	}

	tmp = interfaces_info;
	while(tmp) {
		if ((tmp->ifa_flags & IFF_UP) && !(tmp->ifa_flags & IFF_LOOPBACK) && (tmp->ifa_flags & IFF_NOARP)) {
			index = if_nametoindex(tmp->ifa_name);
			break;
		}
		tmp = tmp->ifa_next;
	}

	freeifaddrs(interfaces_info);
	return(index);
}

int	set_sockadrr_ll(struct sockaddr_ll *addr) {
	int	ifid = find_interface();
	
	if (ifid == 0) {
		printf_fd(2, "[INFO] : No valid interface found.\n");
		return(-1);
	}

	ft_memset(addr, 0, sizeof(addr));
	addr->sll_family = AF_PACKET;
	addr->sll_ifindex = ifid;
	addr->sll_halen = 6;	
	ft_memset(addr->sll_addr, 0xFF, 6);

	return(0);
}

int	set_target_frame(struct s_frame *buf) {
	
}