# include "ft_malcolm.h"

void	clean_malcolm(t_malcolm	*data) {
	ft_free_char_tab(data->dst_mac_addr);
	ft_free_char_tab(data->src_mac_addr);
	free(data->addr);
	free(data->buf);
	close(data->sockfd);
}