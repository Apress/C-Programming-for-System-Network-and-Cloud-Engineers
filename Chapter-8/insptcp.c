#include <pcap/pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

void tcp_inspect(u_char *args, const struct pcap_pkthdr *hdr, const u_char *tpkt) 
{
    	struct ip *iphdr;
    	struct tcphdr *tcph;
    	u_int ipsz;
    	u_int tcpsz;
    	iphdr = (struct ip*)(tpkt + 14); 
    	ipsz = iphdr->ip_hl * 4;
    	if (ipsz < 20) 
	{
        	printf("   * Invalid IP hdr length: %u bytes\n", ipsz);
        	return;
    	}

    	if (iphdr->ip_p != IPPROTO_TCP) 
	{
        	return; 
    	}

    	tcph = (struct tcphdr*)(tpkt + 14 + ipsz);
    	tcpsz = tcph->th_off * 4;
    	if (tcpsz < 20) 
	{
        	printf("   * Invalid TCP hdr length: %u bytes\n", tcpsz);
        	return;
    	}
	int syn = (tcph->th_flags & TH_SYN) ? 1 : 0;

	if (syn==1)
	{
		printf(" TCP new connection\n");
    		printf("  Source IP: %s\n", inet_ntoa(iphdr->ip_src));
    		printf("  Destination IP: %s\n", inet_ntoa(iphdr->ip_dst));
    		printf("  Source Port: %d\n", ntohs(tcph->th_sport));
    		printf("  Destination Port: %d\n", ntohs(tcph->th_dport));
    		printf("  Sequence Number: %u\n", ntohl(tcph->th_seq));
    		printf("  Acknowledgement Number: %u\n", ntohl(tcph->th_ack));
    	
		printf("  Header Length: %d\n", tcph->th_off * 4);
    		printf("  Window Size: %d\n", ntohs(tcph->th_win));
    		printf("  Checksum: %d\n", ntohs(tcph->th_sum));
    		printf("  Urgent Pointer: %d\n", ntohs(tcph->th_urp));
	}

	int fin = (tcph->th_flags & TH_FIN) ? 1 : 0;
	int rst = (tcph->th_flags & TH_RST) ? 1 : 0;
	if (fin==1 || rst==1)
	{
		printf(" TCP connection close or abort\n");
		printf("  Source IP: %s\n", inet_ntoa(iphdr->ip_src));
                printf("  Destination IP: %s\n", inet_ntoa(iphdr->ip_dst));
                printf("  Source Port: %d\n", ntohs(tcph->th_sport));
                printf("  Destination Port: %d\n", ntohs(tcph->th_dport));
	}

}

int main() 
{
    	char *dev = "enx00e04d6df09d";  
    	char errbuf[PCAP_ERRBUF_SIZE];
    	pcap_t *handle;

    	handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    	if (handle == NULL) 
	{
        	fprintf(stderr, "Couldn't open network device %s: %s\n", dev, errbuf);
        	return 2;
    	}
    	pcap_loop(handle, 0, tcp_inspect, NULL);
    	pcap_close(handle);
    	return 0;
}
