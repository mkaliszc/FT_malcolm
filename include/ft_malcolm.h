#ifndef FT_MALCOLM
# define FT_MALCOLM

# include "../OctoLIB/include/libft.h"

// * Authorized function's lib
# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <signal.h>
# include <netdb.h>
# include <ifaddrs.h>
# include <string.h>

// * Lib used for their define
# include <sys/ioctl.h>
# include <net/if.h>
# include <linux/if_ether.h>
# include <linux/if_packet.h>

// * error lib
# include <errno.h>

typedef struct s_eth
{
	uint8_t  dst[6];
	uint8_t  src[6];
	uint16_t ethertype;
} __attribute__((packed)) t_eth;

typedef struct s_arp
{
	uint16_t htype;
	uint16_t ptype;
	uint8_t  hlen;
	uint8_t  plen;
	uint16_t oper;
	uint8_t  sha[6];
	uint8_t  spa[4];
	uint8_t  tha[6];
	uint8_t  tpa[4];
} __attribute__((packed)) t_arp;

typedef struct s_frame
{
	t_eth eth;
	t_arp arp;
} __attribute__((packed)) t_frame;


typedef struct s_malcolm
{
	char				**src_mac_addr;
	char				**dst_mac_addr;
	int					sockfd;
	struct sockaddr_ll	*addr;
	struct s_frame		*buf;
} t_malcolm;

// * ft_malcolm function


// * Function in common
int			find_interface();
char		**parse_mac_address(char *mac_address);
void		fill_mac_address(unsigned char	*addr, char **mac_address);
int			set_frame(struct s_frame *buf, char **mac_address_dst, char **mac_address_src);
t_malcolm	*init_t_malcolm(char *src_mac_addr, char *dst_mac_addr);
void		clean_malcolm(t_malcolm	*data);

// * target's function
int			set_sockadrr_ll(struct sockaddr_ll *addr, char **mac_address);

#endif