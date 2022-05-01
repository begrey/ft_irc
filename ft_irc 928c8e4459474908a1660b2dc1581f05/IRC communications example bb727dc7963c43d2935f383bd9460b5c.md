# IRC communications example

> [http://chi.cs.uchicago.edu/chirc/irc_examples.html](http://chi.cs.uchicago.edu/chirc/irc_examples.html) 해석
> 

여기서는 3가지 IRC 통신의 예시를 설명한다. IRC RFCs에 빠져들기 전, IRC 클라이언트와 서버 사이의 대화 형식이 어떤지에 대해 더 좋은 이해를 할 수 있도록 도움이 되는 이 3가지 예시를 읽기를 권장한다. 이 3개의 예시들은 또한 메시지 포멧, prefixes 그리고 replies에 대한 명확한 이해를 도울 것이다.

## Logging into an IRC server

---

![Connecting to an IRC server](http://chi.cs.uchicago.edu/_images/connect.png)

Connecting to an IRC server

IRC 클라이언트가 IRC 서버에 접속할 때, 먼저 이 connection을 register해야 한다. 이것은 `NICK`과 `USER`, 이 두개의 메시지로 마무리된다(위 그림 1, 2를 참조). `NICK`은 사용자 닉네임을 명시하고(사진의 amy가 이러한 것), `USER`는 사용자에 대한 추가적인 정보를 제공한다. 좀 더 구체적으로, USER는 사용자의 username(amy), 그리고 위 사용자의 풀 네임(Amy Pond)(여기서는 `USER`의 두 번째, 세 번째 파라미터는 구현하지 않음). Username은 일반적으로 사용자 ID에 기반한 IRC 클라이언트에서 자동으로 가져온다. 예를 들어, 만약 당신이 jrandom 사용자로 UNIX 머신에 로그인한다면, 대부분의 IRC 클라이언트는 디폴트로 그것을 너의 username으로 인지할 것이다. 그러나, username이 nick과 매치되야할 필요는 없다.

당신이 아직 존재하지 않은 nick을 선택했다고 가정하며, IRC 서버는 `PRL_WELCOM`이라고 답신할 것이다(assigned code 001). 이 답신은 다음의 컴포넌트를 가진다:

- `:bar.example.com`: 접두어(prefix). Prefix는 메시지의 기원을 나타내기 위해 사용한다는 것을 기억해라. `bar.example.come` 답신은 서버에서 발송한 것으로, prifix는 단순히 hostname만 포함한다. 이것은 불필요해 보이지만, 클라이언트로 하여금 짐작컨데 이미 서버에 연결되었음을 알 수 있다. 그러나, IRC 네트워크에서 서버에서 발송한 응답은 클라이언트가 연결된 서버가 아닌, 다른 서버에서 발생할 수도 있다.
- `001`: numeric code for `PRL_WELCOME`.
- `amy`: 답신 메시지의 첫 번째 파리미터로, 이 파트는 항상 사용자의 `nick`이여야 한다.
- `:Welcome to the Internet Relay Network borja!borja@polaris.cs.uchicago.edu`: 두 번째 파라미터. 이 파라미터의 내용은 RFC2812에 명시되어 있다.
    
    ```bash
    001    RPL_WELCOME
           "Welcome to the Internet Relay Network <nick>!<user>@<host>"
    ```
    
    답신에서 항상 회신 수신인인 첫 번째 파라미터가 생략되는 것을 주목하라. 따라서, 사양에는 두 번째와 그 이후의 파라미터가 나열된다.
    `PRL_WELCOME` 답신에서 전송되는 항목 중 하나는 전체 클라이언트 식별자(<nick>!<user>@<host>)이고, 이는 다른 타입의 메시지에서도 사용된다. 이것은 `NICK` 커맨드에 명시된 nick, `USER`에 명시된 username, 그리고 클라이언트의 hostname(만약 서버가 클라이언트의 hostname을 특정할 수 없다면, IP 주소가 사용됨)으로 구성된다.
    

다음 그림은 위에서 설명한 통신의 변형을 보여준다.

![http://chi.cs.uchicago.edu/_images/duplicatenick.png](http://chi.cs.uchicago.edu/_images/duplicatenick.png)

만약 사용자가 이미 존재하는 nick으로 register하려고 한다면, 서버는 `ERR_NICKNAMEINUSE`(code 433)를 답신할 것이다. 일부 파라미터의 차이점을 알 필요가 있다:

- `*`: 첫 번째 파라미터는 반드시 답신의 대상인 사용자의 nick이여야 한다. 하지만, 여기서는 사용자가 nick을 가지지 않았으니, asterisk 문자가 대신 사용된다.
- `amy`: ERR_NICKNAMEINUSE 답신에서, 두 번째 파라미터는 “offending nick”(이미 존재하는 nick으로 사용할 수 없음)이다.
- `:Nickname is already in use`: 세 번째 파라미터는 에러를 사람이 읽을 수 있는 형태의 설명을 포함한다. IRC 클라이언트는 이 메시지를 보통 그대로 출력할 것이다.

따라서, 모든 응답에서는 동일한 파라미터 집합이 재전송되지 않는다(다만 수신인 nick인 첫 파라미터는 제외). 이런 답신이 수행될 때, 반드시 정확히 어떠한 답신을 보낼지에 대해 RFC2812를 따라야 한다.

## Messaging between users

---

![http://chi.cs.uchicago.edu/_images/privmsg.png](http://chi.cs.uchicago.edu/_images/privmsg.png)

채널에 다수의 사용자가 접속해 있으면, 심지어 채널에서 오프라인 상태더라도 서로에게 메시지를 보내는 것이 가능하다. 실제로는, 두 번째 assignment의 대부분이 사용자간의 메시징 구현에 초점을 맞추고 있는 반면, 다음의 세 번째 assignment는 채널에 대한 지원을 추가하는데 초점을 맞췄다.

특정 nick에 메시지를 보내기 위해, 사용자는 반드시 서버에 `PRIVMSG`를 전송해야 한다. 위 그림은 `amy`와 `rory`라는 nick을 가진 두명의 사용자가 3개의 메시지를 주고받는 것을 보여준다. 메시지 1에서 amy는 rory에게 메시지를 전송한다. `PRIVMSG`의 파라미터는 매우 단순한데: 첫 번째 파라미터는 대상이 될 사용자의 nick이고, 두 번째 파라미터는 메시지이다.

서버가 위 메시지를 수신할 때, `rory` 사용자가 있다고 가정하면, 해당 nick으로 등록된 IRC 클라이언트에 메시지를 전달할 것이다. 이것은 메시지 2에서 수행되며, 이것이 단순히 메시지 1을 그래도 복사한 것이지만, `amy`의 전체 클라이언트 식별자를 앞에 붙이는것을 주목헤야 한다(만약 이 내용이 없다면 IRC 클라이언트는 메시지가 누구에게로 왔는지 알 수 없다.). 메시지 3과 4는 비슷한 통신을 보이고, `rory`가 `amy`에게 메시지를 보낸다. 그리고 메시지 5와 6은 `amy`가 `rory`에게로 보내는 또 다른 메시지를 보인다.

모든 메시지들이 어떻게 IRC 서버를 통해 relay되는지에 주목하라.

IRC 명세에서는 non-relay 메시지에 대한 지원을 하지 않고, 이번 글에서 이러한 기능을 만들지도 않을 것이다. 그러나, IRC에는 두개의 extension(CTCP, DCC)이 있는데, 이들은 non-relay IRC에서 사실상의 표준으로 자리하고 있다. 대부분의 IRC 서버와 클라이언트는 이러한 extension을 지원하고, 심지어 RFC를 지키지 않아도 된다.

## Joining, talking in, and leaving a channel

---

![http://chi.cs.uchicago.edu/_images/channel_join.png](http://chi.cs.uchicago.edu/_images/channel_join.png)

IRC 서버에 연결된 사용자는 `JOIN` 메시지를 사용함으로써 존재하고 있는 채널에 참가할 수 있다. 이 메시지의 포벳은 지극히 단순하지만(참가하고자 하는 채널의 이름만을 파라미터로 가짐), 이는 채널에 가입하려는 사용자 뿐 아니라, 현재 채널에 있는 모든 유저에게 여러가의 답장을 전송하는 결과를 낳는다. 위 그림은 amy라는 사용자가 이미 두명의 사용자가 있는 #tardis 채널에 참가할 때 벌어지는 일을 담았다. 

메시지 1은 서버로 발송되는 `amy`의 `JOIN` 메시지이다. 이 메시지가 수신되면, 서버는 이미 채널에 있는 두 사용자에게 새로운 사용자가 왔음을 알리기 위해 해당 메시지를 둘 모두에게 relay한다(메시지 2a, 2b). `JOIN`이 `amy`의 전체 클라이언트 식별자와 함께 어떻게 relay되는지에 주목하라. 이러한 JOIN은 amy에게도 또한 relay되는데, 이는 그녀가 채널에 참가되었는지 확인하는 역할을 한다.

그 후의 메시지 3, 4a, 4b는 이 채널에 대한 정보를 `amy`에게 제공한다. 메시지 3은 `RPL_TOPIC` 답신으로, 채널의 토픽을 제공한다. 메시지 4a와 4b는 `RPL_NAMREPLY`와 `RPL_ENDOFNAMES` 답신인데, 제각각 amy에게 현재 채널에 누구누구가 있는지를 알린다. `doctor` 사용자가 그의 nick 전에 어떻게 인증하는지를 주목하라. `doctor`는 #tardis 채널의 channel operator라는 것을 보여준다. 세 번째 assignment에 따르면, 사용자는 mode를 가질 수 있으며, 그것은 그들로 하여금 서버에서, 혹은 채널에서 특수한 권한을 가지고 있음을 뜻한다. 예를 들어, 채널 관리자는 보통 채널의 토픽을 바꿀 수 있는 유일한 사용자이다.

![http://chi.cs.uchicago.edu/_images/channel_privmsg.png](http://chi.cs.uchicago.edu/_images/channel_privmsg.png)

사용자가 체널에 참가한 경우, 채널에 메시지를 보내는 것은 근본적으로 개인 메시지를 보내는 것과 동일하다. 차이점은 서버가 이 메시지를 채널의 모든 사용자에게 relay한다는 것이다. 위 그림은 #tardis 채널에서 보내진 두개의 메시지 흐름을 보여준다. 먼저, `doctor` 사용자가 채널을 대상으로 `PRIVMSG` 메시지를 전송한다. 그러면 서버는 이 메시지를 `river`와 `amy`에게 relay하는데, `doctor`의 전체 클라이언트 식별자를 메시지에 prefix한다(메시지 1, 2a, 2b). 유사하게, `amy`가 채널에 전송한 메시지도, `doctor`와 `river`에게 `amy`의 전체 클라이언트 식별자를 prefix한 메시지를 relay한다(메시지 3, 4a, 4b).

![http://chi.cs.uchicago.edu/_images/channel_part.png](http://chi.cs.uchicago.edu/_images/channel_part.png)

채널에서 나가는 것은 `PART` 메시지로 완료되는데, 채널에 참가하고 대화하는 패턴과 유사하다. 사용자가 PART 메시지를 전송함으로써 나가길 원하면, 이 메시지는 채널의 모든이에게 relay되어, 그들로 하여금 해당 유저가 나갔다는것을 알게한다. 서버는 또한 채널에서 해당 클라이언트를 내부적으로 삭제하여, 해당 클라이언트가 채널에서 어떠한 메시지나 답장을 받지 못하도록 한다. 위 그림은 이 내용들이 어떻게 벌어지는지 보여준다. `PART` 메시지가 두개의 파리미터를 포함한 것에 주목하라. 채널 사용자가 나가게 되면 `PART` 메시지의 일부는 채널의 모든 사용자에 relay된다.