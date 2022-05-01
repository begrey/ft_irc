# Subject external functions 조사

| External functions | C++98의 모든 것, socket, setsockopt, getsockname, getprotobyname, gethostbyname, getaddrinfo, freeaddrinfo, bind, connect, listen, accept, htons, htonl, ntohs, ntohl, inet_addr, inet_ntoa, send, recv, signal, lseek, fstat, fcntl, poll (or equivalent) |
| --- | --- |

| Name | Description |
| --- | --- |
| socket | int socket(int domain, int type, int protocol);
소켓을 만들기 위해 사용한다.

- return: 해당 소켓을 가리키는 소켓 디스크립터를 반환한다. -1이 반환되면 생성에 실패했다는 것이고, 0 이상의 값이 나오면 성공.

- domain: 어떤 영역에서 통신할 것인지에 대한 영역을 지정한다. (AF_UNIX(프로토콜 내부), AF_INET(ipv4), ...)
- type: 어떤 타입의 프로토콜을 사용할 것인지 설정. (SOCK_STREAM(irc로 추정), ...)
- protocol: 어떤 프로토콜의 값을 결정하는 것. (0을 써도 되고, IPPROTO_TCP(TCP인 경우), ...) |
| setsockopt | int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
생성된 socket의 속성값을 변경하는 함수.

- return: 0이 아닌 값, -1 이 반환되면 오류가 발생하였음을 의미한다. 상세 오류 내용은 errno에 기제된다.

- sockfd: socket() 함수를 통해 생성된 소켓 디스크립터.
- level: optname 값이 socket level인지 특정 프로토콜에 대한 설정인지를 지정하는 값.
- optname: level의 종류에 따라 다른 설정이름을 가짐.
- optval: optname에 따른 설정 값
- optlen: optval의 크기 |
| getsockname | int getsockname(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
소켓 디스크립터에 할당된 자신의 address를 얻기 위해 사용한다.

- return: 0이 아닌 값이 반환되면 오류가 발생하였음을 의미한다. 오류대용은 errno에 기제된다.

- sockfd: 정상적으로 생성된 소켓 디스크립터.
- sockaddr: 자신의 주소를 저장할 버퍼이다.
- addrlen: 두번째 파라미터 addr 구조체의 크기를 설정하고 함수를 호출해야 한다. getsockname() 함수가 끝나면 실제로 addr에 채워진 사이즈가 저장된다. |
| getprotobyname | struct protoent *getprotobyname(const char *name);
프로토콜 데이터베이스에서 name의 항목을 탐색하여 필요로 하는 protoent 구조체를 반환한다. |
| gethostbyname | struct hostent *gethostbyname(const char *name);
도메인 주소로 IP 주소를 구하는 함수이다. (ex. www.naver.com → 23.65.188.81) |
| getaddrinfo | int getaddrinfo(const char* hostname, const char* service, const struct addrinfo hint, struct addrinfo* result);
도메인 주소를 받아 네트워크 IP를 가져오는 함수이다. |
| freeaddrinfo | void freeaddrinfo(struct addrinfo* res);
getaddrinfo() 함수의 사용을 끝낸 뒤 freeaddrinfo() 함수를 사용하여 메모리를 해제해야 한다. |
| bind | int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
socket()함수를 통해 만들어진 소켓은, 이름 공간은 가지지만 이러다 할 주소를 가지지 않는다. 이 함수는 소켓에 주소를 할당 해주는 함수이다.

- return: 성공시 0을 반환. 에러 발생시 -1 반환. 에러의 내용은 errno에 담긴다.

- sockfd: 대상이 될 소켓 디스크립터.
- addr: 주소 정보가 할당됨.
- addrlen: addr 구조체의 크기 |
| connect | int connect(int sockfd, const struct sockaddr* addr, socklen_t addrlen);
시스템 콜 함수로 sockfd로 전달된 소켓 디스크립터로 addr에 의해 지정된 주소를 연결한다.
addrlen 인자는 addr의 크기를 지정한다.

- return: 성공시 0 반환. 에러 발생시 -1 반환. 에러의 내용은 errno에 담긴다. |
| listen | int listen(int sockfd, int backlog);
이 함수는 sockfd로 제공된 소켓을 정적으로 마크한다. 즉, accept()를 사용하여 들어오는 연결 요청을 받는데 사용하는 소켓이다.

- return: 성공시 0 반환. 에러 발생시 -1 반환. 에러의 내용은 errno에 담긴다. |
| accept | int accept(int sockif, struct sockaddr* addr, socklen_t* addrlen);
시스템 콜 함수로 연결지향 소켓 타입(SOCK_STREAM, SOCK_SEQPACKET)에 사용한다. 이것은 아직 처리되지 않은 연결들이 대기하고 있는 큐에서 제일 처음 연결된 통신을 가져와 새로운 연결된 소켓을 만든다. 그리고 해당 소켓의 디스크립터를 할당하여 리턴한다.

- return: 성공시 만들어진 소켓의 디스크립터 반환. 실패시 -1 반환. |
| htons | uint16_t htons(uint16_t hostshort);
2 byte 데이터에 대해 호스트 바이트 순서를 빅 엔디안 순서로 변환할 때 사용.

* 빅 엔디안: 시작 주소에 데이터의 최상의 비트(MSB)가 오도록 저장.
* 리틀 엔디안: 시작 주소에 최하위 비트(LSB)가 오도록 저장.
* 0x12(빅엔디안) = 0x78(리틀엔디안), 0x34(빅) = 0x56(리틀) |
| htonl | uint32_t htonl(uint32_t hostlong);
위와 같은 역할로 4 byte 데이터를 사용하는 차이를 가짐. |
| ntohs | htons 역순. |
| ntohl | htonl 역순. |
| inet_ntoa | char *inet_ntoa(struct in_addr in);
네트워크 바이트 순서의 32비트 값을 Dotted-decimal notation의 주소값으로 변환한다. |
| send | ssize_t send(int sockfd, const void *buf, size_t len, int flags);
connect(), accept()등으로 연결된 socket으로 상대 시스템에 데이터를 전송한다. flags의 속성이 0이면 일반적인 데이터 전송방식인 write() 함수로 대체할 수 있다.

- return: 성공시 0 이상값을 반환하며, 실제 전송된 데이터 량을 반환한다. 실패시 -1을 반환한다.

- sockfd
- buf: 전송할 데이터
- len: 전송할 데이터 길이
- flags: 전송할 데이터 또는 읽는 방법에 대한 옵션이다. 0 또는 비트 OR 연산으로 설정할 수 있다. |
| recv | ssize_t recv(int sockfd, void* buf, size_t len, int flags);
connect() 또는 accept() 등으로 연결된 소켓으로부터 데이터를 수신한다. 일반적인 데이터를 읽을 때에는 read() 함수를 사용할 수 있다. read(sockfd, buf, len) == recv(sockfd, buf, len, 0) |
| signal | void ( *signal (int sig, void(*func)(int)) )(int);
리눅스(유닉스) 시그널 관련 함수. |
| lseek | off_t lseek(int fd, off_t offset, int whence);
함수의 seek pointer를 조정하는 함수로, 조정된 seek pointer는 파일의 read/write시 사용된다. 특정 위치부터 읽거나 쓸 때 유용하다. |
| fstat | int fstat(int fd, struct stat* buf);
열린 파일의 크기, 권한, 생성 일시, 최종 변경일 등, 파일의 상태나 데이터를 얻는 함수이다. |
| fcntl | int fcntl(int fd, int cmd, ...(int arg));
cmd 인자에 따라 파일의 속성을 가져오거나 설정할 수 있다. |
| poll (or equivalent) | int poll(struct pollfd* fds, nfds_t nfds, int timeout);
select()와 비슷한 기능을 하는 함수로, 소켓 혹은 파이프에서 동시에 여러 I/O를 대기할 경우 특정 fd에 blocking되지 않고 I/O를 수행할 수 있는 상태인 지를 모니터링하여 I/O가능한 상태의 fd인지 검사하는 함수이다. |