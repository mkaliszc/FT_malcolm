# include "ft_malcolm.h"

char	**parse_mac_address(char *mac_address) {
	char	**return_value;
	size_t	len = ft_strlen(mac_address);

	if (len < 17) {
		return (NULL);
	}

	for (size_t i = 0; i < len; i++) {
		if (i % 3 == 0 && mac_address[i] != ':') {
			return (NULL);
		}
		else if (!ft_isalnum(mac_address[i])) {
			return (NULL);
		}
	}

	return_value = ft_split(mac_address, ':');
	return(return_value);
}