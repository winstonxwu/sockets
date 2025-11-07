// Stream Server in C

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define PORT "1999" // defining a port for the user to connect to, can be 1024-49151
#define BACKLOG 10 // the number of pending connections the queue will hold

void sigchld_handler(int s) {
  (void)s; // variable warning, casting s to void as we are not using it

  int saved_errno = errno; // saving error variable "errno", because it can be
                           // lost by signal handler interruption

  while (waitpid(-1, NULL, WNOHANG) > 0); // reap any terminated child process. waitpid(pid=-1 [wait for any child
      // process to change its state], status=NULL [do not store status],
      // options=WNOHANG [return immediately if no child has exited])

  errno = saved_errno;
}

/* #include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>


struct addrinfo {
  int ai_flags;      // AI_PASSIVE, AI_CANNONNAME, etc.
  int ai_family;     // AF_INET, AF_INET6, AF_UNSPEC
  int ai_socktype;   // SOCK_STREAM, SOCK_DGRAM (These are the types of sockets
                     // there are)
  int ai_protocol;   // use 0 for "any"
  size_t ai_addrlen; // Represents unsigned integer, stores the size of an
                     // object in memory, stores the size of ai_addr in bytes
  struct sockaddr *ai_addr; // struct sockaddr_in or _in6
  char *ai_canonname;       // full canonical hostname

  struct addrinfo *ai_next; // linked list, that points to the next node
};

struct sockaddr {
  unsigned short sa_family; // address family, AF_xxx
  char sa_data[14];         // 14 bytes of protocol address
};

struct sockaddr_in {
  short int sin_family;        // Address family, AF_INET
  unsigned short int sin_port; // Port number
  struct in_addr sin_addr;     // Internet Address
  unsigned char sin_zero[8];   // Same size as struct sockaddr
};

struct in_addr {
  uint32_t s_addr; // 32-bit int (4 bytes, 32/8)
};

struct sockaddr_storage {
  sa_family_t ss_family;

  char __ss_pad1[_SS_PAD1SIZE];
  int64_t __ss_align;
  char __ss_pad2[_SS_PAD2SIZE];
}

struct sockaddr_in sa;
struct sockaddr_in6 sa6;

inet_pton(AF_INET, "10.12.110.57", &(sa.sin_addr));
inet_pton(AF_INET6, "2001:db8:63b3:1::3490", &(sa6.sin6_addr));

char ip4[INET_ADDRSTRLEN];
struct sockaddr_in sa;

inet_ntop(AF_INET, &(sa.sin_addr), ip4, INET_ADDRSTRLEN);

printf("The IPv4 address is: %s\n", ip4);

char ip6[INET6_ADDRSTRLEN];
struct sockaddr_in sa6;

inet_ntop(AF_INET6, &(sa6.sin6_addr), ip6, INET6_ADDRSTRLEN);

printf("The address is: %s\n", ip6); */
