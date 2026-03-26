#include <pcap/pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/if_ether.h> 
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
void udp_inspect(u_char *user_data, const struct pcap_pkthdr *pkthdr, const u_char *upkt) 
{
    	struct ethhdr *eth_header = (struct ethhdr *)upkt;
    	if (ntohs(eth_header->h_proto) != ETHERTYPE_IP) 
	{
        	return; // Not an IP upkt
    	}

    	struct iphdr *ip_header = (struct iphdr *)(upkt + ETH_HLEN);
    	if (ip_header->protocol != IPPROTO_UDP) 
	{
        	return; // Not a UDP upkt
    	}
    	struct udphdr *udp_header = (struct udphdr *)(upkt + ETH_HLEN + (ip_header->ihl * 4));


    	u_char *contents = (u_char *)(upkt + ETH_HLEN + (ip_header->ihl * 4) + sizeof(struct udphdr));
    	int contents_len = ntohs(udp_header->len) - sizeof(struct udphdr);

	if (ntohs(udp_header->dest)==53 || contents_len>64)
	{
    		printf("UDP Packet (DNS or message len>64) \n");
    		printf("Src IP: %s\n", inet_ntoa(*(struct in_addr *)&ip_header->saddr));
    		printf("Dst IP: %s\n", inet_ntoa(*(struct in_addr *)&ip_header->daddr));
    		printf("Src Port: %d\n", ntohs(udp_header->source));
    		printf("Dst Port: %d\n", ntohs(udp_header->dest));
    		printf("UDP Length: %d\n", ntohs(udp_header->len));

    		printf("Contents Length: %d\n", contents_len);
    		printf("Contents: ");
    		for (int i = 0; i < contents_len ; i++) 
		{
        		printf("%02x ", contents[i]);
    		}
    		printf("\n\n");
	}
}

int main() 
{
    	char *dev = "enx00e04d6df09d";  // Replace with your interface
    	char errbuf[PCAP_ERRBUF_SIZE];
    	pcap_t *handle;
    	handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    	if (handle == NULL) 
	{
        	fprintf(stderr, "Couldn't open network device %s: %s\n", dev, errbuf);
        	return 2;
    	}

    	pcap_loop(handle, 0, udp_inspect, NULL);
    	pcap_close(handle);
    	return 0;
}
