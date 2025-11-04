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
