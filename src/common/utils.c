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

void	fill_mac_address(unsigned char	addr[8], char **mac_address) {
	int	i = 0;

	while(i < 6) {
		addr[i] = ft_strtol(mac_address[i++], 16);
	}
}

t_malcolm	*init_t_malcolm(char *src_mac_addr, char *dst_mac_addr) {
	t_malcolm	*return_value = malloc(sizeof(t_malcolm));

	if (return_value == NULL) {
		return(printf_fd(2,"[ERROR] : malloc error.\n"), NULL);
	}

	ft_memset(return_value, '\0', sizeof(t_malcolm));

	return_value->src_mac_addr = parse_mac_addr(src_mac_addr);
	if (return_value->src_mac_addr == NULL) {
		printf_fd(2, "[ERROR] : Not a MAC adress.\n");
		return(clean_malcolm(return_value), NULL);
	}
	return_value->dst_mac_addr = src_mac_addr;

	return_value->dst_mac_addr = parse_mac_adress(dst_mac_addr);
	if (return_value->dst_mac_addr == NULL) {
		printf_fd(2, "[ERROR] : Not a MAC adress.\n");
		return(clean_malcolm(return_value), NULL);
	}
	return_value->dst_mac_addr = dst_mac_addr;

	return_value->addr = malloc(sizeof(struct sockaddr_ll));
	if (return_value->addr == NULL) {
		return(clean_malcolm(return_value), printf_fd(2,"[ERROR] : malloc error.\n"), NULL);
	}

	return_value->buf = malloc(sizeof(struct sockaddr_ll));
	if (return_value->buf == NULL) {
		return(clean_malcolm(return_value), printf_fd(2,"[ERROR] : malloc error.\n"), NULL);
	}

	return_value->sockfd = -1;
	
	return (return_value);
}