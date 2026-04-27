# include "ft_malcolm.h"

int	find_interface() {
	struct ifaddrs	*interfaces_info;
	struct ifaddrs	*tmp;
	int				index = 0;

	if (getifaddrs(&interfaces_info) < 0) {
		printf_fd(2, "[ERROR] find_interface : couldn't get interface info, %s\n", strerror(errno));
		return(0);
	}

	tmp = interfaces_info;
	while(tmp) {
		if (tmp->ifa_addr->sa_family == AF_PACKET) {
			if ((tmp->ifa_flags & IFF_UP) && !(tmp->ifa_flags & IFF_LOOPBACK) && !(tmp->ifa_flags & IFF_NOARP)) {
				index = if_nametoindex(tmp->ifa_name);
				break;
			}
			tmp = tmp->ifa_next;
		}
	}

	if (index != 0) {
		printf("Found available interface: %s\n", tmp->ifa_name);
	}
	freeifaddrs(interfaces_info);
	return(index);
}

void	fill_mac_address(unsigned char	*addr, char **mac_address) {
	int	i = 0;

	while(i < 6) {
		addr[i] = ft_strtol(mac_address[i], 16);
		i++;
	}
}

t_malcolm	*init_struct(char *src_mac_addr, char *dst_mac_addr, char *ip_src, char *ip_dst) {
	t_malcolm	*return_value = malloc(sizeof(t_malcolm));

	if (return_value == NULL) {
		return(printf_fd(2,"[ERROR] init_struct : malloc error.\n"), NULL);
	}

	ft_memset(return_value, '\0', sizeof(t_malcolm));

	return_value->src_mac_addr = parse_mac_address(src_mac_addr);
	if (return_value->src_mac_addr == NULL) {
		printf_fd(2, "[ERROR] init_struct : Not a MAC adress, %s.\n", src_mac_addr);
		return(clean_malcolm(return_value), NULL);
	}

	return_value->dst_mac_addr = parse_mac_address(dst_mac_addr);
	if (return_value->dst_mac_addr == NULL) {
		printf_fd(2, "[ERROR] init_struct : Not a MAC adress, %s.\n", dst_mac_addr);
		return(clean_malcolm(return_value), NULL);
	}
	return_value->ip_src = ip_src;
	return_value->ip_dst = ip_dst;
	return_value->sockfd = -1;
	return (return_value);
}