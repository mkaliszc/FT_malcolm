# include "ft_malcolm.h"

void	clean_malcolm(t_malcolm	*data) {
	if (data->dst_mac_addr) {
		ft_free_char_tab(data->dst_mac_addr);
		data->dst_mac_addr = NULL;
	}

	if (data->src_mac_addr) {
		ft_free_char_tab(data->src_mac_addr);
		data->src_mac_addr = NULL;
	}

	if (data->sockfd != -1) {
		close(data->sockfd);
		data->sockfd = -1;
	}

	free(data);
}