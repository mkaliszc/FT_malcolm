# include "ft_malcolm.h"

void	clean_malcolm(t_malcolm	*data) {
	if (data->dst_mac_addr) {
		ft_free_char_tab(data->dst_mac_addr);
	}

	if (data->src_mac_addr) {
		ft_free_char_tab(data->src_mac_addr);
	}

	if (data->sockfd != -1) {
		close(data->sockfd);
	}

	free(data);
}