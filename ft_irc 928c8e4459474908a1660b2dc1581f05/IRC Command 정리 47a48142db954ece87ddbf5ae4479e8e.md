# IRC Command 정리

## 클라이언트

- 닉네임은 최대 9자
- 프로토콜 문법 관련된 단어 사용 불가

## 연결 등록

"PASS" 명령은 클라이언트 또는 서버 연결을 등록하기 위해 필요하지 않지만, 서버 메시지 또는 NICK/USER 조합의 후자보다 앞에 와야 합니다.

실제 연결에 일정 수준의 보안을 제공하기 위해 모든 서버 연결에 암호를 사용하는 것이 좋습니다.

고객이 등록하기 위한 권장 순서는 다음과 같습니다.

1. Pass message
2. Nick message
3. User message

### Pass <password>

- client가 연결 시도하기 전 진행되어야함. nick/ user 전에 처리
- 연결 등록 전에는 계속 바꿀 수 있지만 등록되면 바꿀 수 없다.
- numeric return
    - 461 `ERR_NEEDMOREPARAMS` : 파라미터 부족할 때 `"<command> :Not enough parameters"`
    - 462 `ERR_ALREADYREGISTRED` : 등록된 후 바꾸려 시도할 때  `":Password incorrect"`

### Nick <nickname>

- 중복된 닉네임이 있는 경우 모든 닉네임 인스턴스들은 서버 db에서 제거되어야 한다.
- 두 사람이 닉네임을 선택하면 둘 중 하나가 성공하지 못하거나 둘 다 KILL을 사용하여 제거됩니다.
(공식 문서 발췌, 중복 처리 방식은 우리가 채택하면 될 듯)
- 변경할 닉네임이 중복일 경우, 기존 닉네임도 제거되어야 한다.
- numeric return
    - 431 `ERR_NONICKNAMEGIVEN` : 닉네임 없을 시 `:No nickname given`
    - 432 `ERR_ERRONEUSNICKNAME` : 정의 안된 문자가 들어갔을 시
    - 433 `ERR_NICKNAMEINUSE` : 닉네임 중복

### User <username> <hostname> <servername> <realname>

- 새 사용자의 사용자 이름, 호스트 이름, 서버 이름 및 실명을 지정하는 데 사용
- USER와 NICK가 클라이언트로부터 수신된 후 사용자가 등록 → 서버에 새 유저 알리는 통신에 사용
- 새 사용자가 서버에 소개될 때 함께 제공된 USER가 전송되기 전에 항상 NICK을 원격 서버로 전송해야 함
- username : IRC의 다른 사용자에게 나타나는 사용자@host 호스트 마스크의 사용자 부분
- hostname, servername : IRC 서버에 의해 일반적으로 무시되지만, 서버 간 통신에서 사용
- realname : 공백 문자를 포함할 수 있으며 콜론(':') 앞에 붙여 인식해야 하므로 마지막 파라미터여야 함, 다른 사용자가 WHOIS 명령을 사용할 때 나타나는 실명 필드를 채우는 데 사용
- numeric return
    - 461 `ERR_NEEDMOREPARAMS` : 파라미터 부족할 때 `"<command> :Not enough parameters"`
    - 462 `ERR_ALREADYREGISTRED` : 이미 등록했을 때

### OPER <user> <password>

- 일반 사용자가 조작자 권한을 얻기 위해 사용
- 연산자 권한을 얻기 위해서는 <user>와 <password>의 조합이 필요
- OPERATE 명령을 보내는 클라이언트가 주어진 사용자를 위해 정확한 비밀번호를 제공하면, 서버는 클라이언트 닉네임을 위해 "MODE +o"를 발행하여 새 운영자의 나머지 네트워크에 알림
- OPER 메시지는 클라이언트-서버 전용.
- numeric return
    - 461 `ERR_NEEDMOREPARAMS` : 파라미터 부족할 때 `"<command> :Not enough parameters"`
    - 381 `RPL_YOUREOPER` : OPER 실행 성공 후 운영자 상태를 얻은 클라이언트로 다시 전송
    `":You are now an IRC operator"` 메세지 전송
    - 491 `ERR_NOOPERHOST` : 클라이언트가 OPER 메시지를 보내고 서버가 운영자로서 클라이언트의 호스트에서 연결을 허용하도록 구성되지 않은 경우 이 오류를 반환해야 함
    `":No O-lines for your host"` 메세지 전송 & nosuchnick도 필요할듯
    - 464 `ERR_PASSWDMISMATCH` : 패스워드 불일치. `":Password incorrect"` 메세지 전송
    - 401 `ERR_NOSUCHNICK` : 해당 닉네임 없음.  `"<nickname> :No such nick/channel"` 메세지 전송

### QUIT [quit message]

- 클라이언트 세션 종료. 인자로 넘어오는 메세지는 선택사항
- 클라이언트가 죽고 소켓에서 EOF가 발생하는 등 QUIT 없이 연결이 닫히면, 서버가 적당한 QUIT 메세지 전송해야함

## 채널 작업

채널, 속성(채널 모드) 및 내용(일반적으로 클라이언트)을 조작하는 것과 관련 있는 명령어들이다.
명령어 수행 중, 충돌될 작업들에 대한 서순을 잘 고려해야 한다. 
서버는 닉네임 히스토리(nick history)를 보관하여 <nick> 파라미터가 넘어올 때 마다 최근에 변경된 이력이 있는지 확인해야 함

### JOIN <channel>{,<channel>} [<key>{,<key>}]

- 클라이언트가 특정 채널의 수신을 시작하는 데 사용
- 선행 조건
    - 채널이 초대 전용인 경우 사용자를 초대해야 함
    - 사용자의 nick/username/hostname이 활성화된 ban과 일치하지 않을 것
    - key가 설정된 경우, 올바른 key를 입력해야함
- 사용자가 채널에 가입하면, 서버가 채널에 영향을 미치는 모든 명령에 대한 통지를 받음
MODE, KICK, PART, KIT 및 PRIVMSG/NOTICE가 포함
- JOIN에 성공하면 채널의 주제(RPL_TOPIC)와 채널에 있는 사용자 목록(RPL_NAMREPLY)이 사용자에게 전송, 여기엔 지금 JOIN한 USER도 포함되어야 한다.
    - RPL_TOPIC : `"<channel> :<topic>"`  
    RPL_NOTOPIC :`"<channel> :No topic is set"`  주제 설정 안됨
    - RPL_NAMREPLY : `"<channel> :[[@|+]<nick> [[@|+]<nick> [...]]]"`
- numeric return
    - 461 `ERR_NEEDMOREPARAMS` : 파라미터 부족할 때 `"<command> :Not enough parameters"`
    - 474 `ERR_BANNEDFROMCHAN` : 채널에서 ban 당할경우 `"<channel> :Cannot join channel (+b)"`
    - 473 `ERR_INVITEONLYCHAN` : 초대전용 채널일경우 `"<channel> :Cannot join channel (+i)"`
    - 405 `ERR_TOOMANYCHANNELS` : 허용 채널 수 이상일 경우
     `"<channel> :You have joined too many channels"`
    - 403 `ERR_NOSUCHCHANNEL` : 채널 이름이 잘못됨 `"<channel name> :No such channel"`
    - 475 `ERR_BADCHANNELKEY` : 잘못된 채널 키 `"<channel> :Cannot join channel (+k)"`

### PART <channel>

- JOIN 했던 채널 연결 해제
- 인자 없는 경우 JOIN 했던 모든 채널 연결 해제
- numeric return
    - 461 `ERR_NEEDMOREPARAMS` : 파라미터 부족할 때 `"<command> :Not enough parameters"`
    - 403 `ERR_NOSUCHCHANNEL` : 채널 이름이 잘못됨 `"<channel name> :No such channel"`
    - 442 `ERR_NOTONCHANNEL` : 해당 채널 JOIN 안함 `"<channel> :You're not on that channel"`

## **Mode message**

IRC의 이중 목적 명령으로 사용자 이름과 채널 모두 모드를 변경할 수 있다.

### Channel modes
MODE <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>] [<ban mask>]

- 해당 채널의 oper유저가 채널 모드를 변경하는데 사용
- mode flag
    - o : 채널 운영자 권한을 부여/획득
    - p : private 채널 (채널 목록 표시 o, 어느 private 채널에 있는진 알 수 없음, 닉네임 표시 x)
    - s : secret 채널  (채널 목록 표시 x join 후에 topic 알 수 있음, 유저정보 보이지 않음)
    - i : invite_only 채널
    - t : 채널 운영자 전용으로 topic 설정 가능
    - m : 채널 moderate
    - v : moerate 한 채널에 음성기능 제공
    - l : 사용자 수 제한
    - b : 금지 마스크 설정
    - k : 채널 key(암호) 설정
- reply
    - 324 `RPL_CHANNELMODEIS` : Channel 모드 성공적 변환시 반환
    - 367 `RPL_BANLIST` **:** 지정된 채널의 ban 목록 나열 `"<channel> <banid>"`
    - 367 `RPL_ENDOFBANLIST` : ban리스트 마지막(ban없어도)에 출력
    `"<channel> :End of channel ban list"`
- numeric return
    - 461 `ERR_NEEDMOREPARAMS` : 파라미터 부족할 때 `"<command> :Not enough parameters"`
    - 482 `ERR_CHANOPRIVSNEEDED` : 채널 oper가 아닌데 해당 명령어를 사용할 경우
    `"<channel> :You're not channel operator"`
    - 401 `ERR_NOSUCHNICK` : 해당 닉네임 없음.  `"<nickname> :No such nick/channel"`
    - 442 `ERR_NOTONCHANNEL` : 해당 채널 JOIN 안함 `"<channel> :You're not on that channel"`
    - 467 `ERR_KEYSET` : 이미 key가 set된 경우 `"<channel> :Channel key already set"`
    - 472 `ERR_UNKNOWNMODE` : 없는 mode flag 입력 시 `"<char> :is unknown mode char to me"`
    - 403 `ERR_NOSUCHCHANNEL` : 채널 이름이 잘못됨 `"<channel name> :No such channel"`

### User modes
MODE <nickname> {[+|-]|i|w|s|o}

- 명령어를 날리는 주체의 nickname과 일치해야함
- mode flag
    - i : 사용자를 보이지 않도록 설정 (invisible)
    - s : 서버 notice를 수신하도록 사용자를 표시
    - w : 유저가 wallops 메세지 수신 (네트워크 정보 및 상태를 팔로잉 사용자에게 브로드캐스트)
    - o : 연산자 flag (사용자가 o+로 연산자 만들려고 하면 무시해야함. o- 해제만 가능)
- reply
    - 221 `RPL_UMODEIS` : user mode 변경 후 `"<user mode string>"`
- numeric return
    - 502 `ERR_USERSDONTMATCH` : 내가 아닌 다른 nickname `":Cant change mode for other users"`
    - 501 `ERR_UMODEUNKNOWNFLAG` : mode flag 인식 못함

### TOPIC <channel> [<topic>]

- 채널의 주제를 변경하거나 보는 데 사용
- 인자에 <topic>이 없으면 주제를 반환, <topic>이 있으면 주제 변경 (channel mode 허용될 시)
- reply (응답)
    - 331 `RPL_NOTOPIC` : topic이 정해지지 않았을 경우  `"<channel> :No topic is set"`
    - 332 `RPL_TOPIC` :  topic이 정해졌을 경우 `"<channel> :<topic>"`
- numeric return
    - 461 `ERR_NEEDMOREPARAMS` : 파라미터 부족할 때 `"<command> :Not enough parameters"`
    - 442 `ERR_NOTONCHANNEL` : 해당 채널 JOIN 안함 `"<channel> :You're not on that channel"`
    - 482 `ERR_CHANOPRIVSNEEDED` : 채널 oper가 아닌데 해당 명령어를 사용할 경우
    `"<channel> :You're not channel operator"`

### INVITE <nickname> <channel>

- 사용자를 채널에 초대
- 대상 사용자가 초대되는 채널이 존재하거나 유효한 채널이어야 할 필요는 없음
- 사용자를 초대 전용 채널(MODE +i)로 초대하려면 초대자가 채널 oper여야함
- reply (응답)
    - 342 `RPL_INVITING` : invite가 성공적으로 전달됨을 알림`"<channel> <nick>"`
    - 301 `RPL_AWAY` : 초대한 사용자가 부재중일 때, `"<nick> :<away message>"`
- numeric return
    - 461 `ERR_NEEDMOREPARAMS` : 파라미터 부족할 때 `"<command> :Not enough parameters"`
    - 442 `ERR_NOTONCHANNEL` : 해당 채널 JOIN 안함 `"<channel> :You're not on that channel"`
    - 401 `ERR_NOSUCHNICK` : 해당 닉네임 없음.  `"<nickname> :No such nick/channel"`
    - 443 `ERR_USERONCHANNEL` :  이미 채널에 있음 `"<user> <channel> :is already on channel"`
    - 482 `ERR_CHANOPRIVSNEEDED` : 채널 oper가 아님 `"<channel> :You're not channel operator"`

### KICK <channel> <user> [<comment>]

- 채널에서 사용자를 강제로 제거
- oper유저만 사용 가능하며 서버는 명령어 수행 전에 유효성을 체크해야함\
- numeric return
    - 461 `ERR_NEEDMOREPARAMS` : 파라미터 부족할 때 `"<command> :Not enough parameters"`
    - 403 `ERR_NOSUCHCHANNEL` : 채널 이름이 잘못됨 `"<channel name> :No such channel"`
    - 482 `ERR_CHANOPRIVSNEEDED` : 채널 oper가 아님 `"<channel> :You're not channel operator"`
    - 442 `ERR_NOTONCHANNEL` : 해당 채널 JOIN 안함 `"<channel> :You're not on that channel"`

## 메세지 전송

### PRIVMSG <receiver>{,<receiver>} <text to be sent>

- 사용자 간에 개인 메시지를 보내는 데 사용
- receiver는 이름이나 채널의 목록이 될 수도 있음
- receiver는 #mask를 사용하여 마스크와 일치하는 호스트를 가진 사용자에게 전소 가능
- mask는 적어도 1개 이상의 ‘.’ 이 있어야 하며 이 뒤에는 와일드 카드(*, ?) 불가능
- #mask, $server 사용은 oper 유저만 사용 가능
- reply (응답)
    - 301 `RPL_AWAY` : 초대한 사용자가 부재중일 때, `"<nick> :<away message>"`
- numeric return
    - 411 `ERR_NORECIPIENT` : 수신인이 없을 경우 `":No recipient given (<command>)"`
    - 412 `ERR_NOTEXTTOSEND` : 보낼 메세지를 안적은 경우 `":No text to send"`
    - 404 `ERR_CANNOTSENDTOCHAN` : 유효하지 않은 채널에 보내는 경우
    채널에 m모드 (oper유저나 보이스만 가능),  n(채널 밖에서 보내는 경우 금지), v(보이스)
    `"<channel name> :Cannot send to channel"`
    - 413 `ERR_NOTOPLEVEL` : oper유저 아닌데 #mask, $server 사용
    - 414 `ERR_WILDTOPLEVEL` : oper유저 아닌데 wild카드 사용
    - 407 `ERR_TOOMANYTARGETS` : 보내는 user가 여러 요청이 겹칠 때
    - 401 `ERR_NOSUCHNICK` : 해당 닉네임 없음.  `"<nickname> :No such nick/channel"`

### NOTICE <nickname> <text>

- PRIVMSG와 유사하게 사용됨
- 차이점 : NOTICE 메시지에 대한 응답으로 자동 회신이 전송되지 않아야 함
- 서버도 notice를 수신할 때 오류 응답을 클라이언트에 다시 보내지 않아야 한다