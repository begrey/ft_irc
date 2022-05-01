# RFC 1459

[https://datatracker.ietf.org/doc/html/rfc1459](https://datatracker.ietf.org/doc/html/rfc1459)

- 사용자의 nick은 중복이 불가하며, 최대 길이는 9이다. 프로토콜 문법에 관연관 단어는 사용 불가능하다.
- 서버는 모든 클라이언트에 대하여 host real name(hostname?)과, username 정보를 가지고 있어야 한다.
- password → 4.1.1 참고
- nick → 4.1.2
- user → 4.1.3
: USER 메시지는 특정 username, hostname, servername(서버간 통신 구현 생략으로 무시), realname으로 접속하고자 할때, 사용한다.
- ...