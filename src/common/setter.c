# include "ft_malcolm.h"

int	set_sockadrr_ll(struct sockaddr_ll *addr, char **mac_address) {
	int	ifid = find_interface();
	
	if (ifid == 0) {
		printf_fd(2, "[INFO] set_sockadrr_ll : No valid interface found.\n");
		return(-1);
	}

	ft_memset(addr, 0, sizeof(addr));
	addr->sll_family = AF_PACKET;
	addr->sll_ifindex = ifid;
	addr->sll_halen = 6;
	fill_mac_address(addr->sll_addr, mac_address);

	return(0);
}

int	set_frame(t_malcolm	*data, int type) {
	fill_mac_address(data->buf.eth.dst, data->dst_mac_addr);
	fill_mac_address(data->buf.eth.src, data->src_mac_addr);
	data->buf.eth.ethertype = htons(0x0806);

	data->buf.arp.htype = htons(1);
	data->buf.arp.ptype = htons(0x0800);
	data->buf.arp.hlen = 6;
	data->buf.arp.plen = 4;
	data->buf.arp.oper = htons(type);

	fill_mac_address(data->buf.arp.sha, data->src_mac_addr);
	if (inet_pton(AF_INET, data->ip_src,data->buf.arp.spa) != 1) {
		printf_fd(2, "[INFO] inet_pton : Invalid ip string, %s.\n", data->ip_src);
		return(clean_malcolm(data), -1);
	}

	fill_mac_address(data->buf.arp.tha, data->dst_mac_addr);
	if (inet_pton(AF_INET, data->ip_dst,data->buf.arp.tpa) != 1) {
		printf_fd(2, "[INFO] inet_pton : Invalid ip string, %s.\n", data->ip_dst);
		return(clean_malcolm(data), -1);
	}

	return(0);
}