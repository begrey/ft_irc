# 우리거 error message 실험

## Hexchat으로 SwiftIRC 접속

- PF_PASS
    - `/pass` 띄어쓰기 없이 pass를 입력할 경우 아무런 행동을 하지 않음
    `/pass`  띄어쓰기가 있으면 제대로 에러메세지를 출력함 `Not enough parameters:(`
    띄어쓰기 유무로 파싱이 되고 안되고 하는 것 같음.
    아무튼 파싱이 잘 되었을 때에는 정상적으로 서버로 에러메세지를 잘 출력해주고 있음
    - `/pass 잘못된비번` → Invalid Password                  OK
    - `/pass 제대로된비번` → You may not reregister:(   OK
- PF_NICK
    - `/nick` 을 할 경우는 client 에서 가로채가는 것 같음. hexchat이 알아서 메세지를 내뱉어버림. 원래는 우리거 no nickname given이 떠야하나 이는 클라이언트 문제로 우리가 해결할 수 없음. 그냥 이대로 하면 될 듯함.
    - `/nick 1234567890` → The NICK cannot exceed 9 characters OK
    - 중복닉네임의 경우 또한 client에서 가로채며 대체 닉네임으로 자동으로 바꿔줌 이또한 우리가 해결할 부분이 아님 → 우리는 다른클라이언트 이용 시 동작을 할테니 그렇게 디펜스 하면 될듯 함.
    - 닉네임 아스키코드 확인하는 것은 변수를 못넣어봐서 확인 못해봄... 아무튼 동작은 잘 될거라 생각함..
- PF_JOIN
    - `/join` 의 경우도 hexchat 클라이언트가 가로채감. → 이하동문
    - `/join 123` → 123 :Cannot join channel: Channel name must start with a hash mark (#) 서버로 출력 OK
    - join 10개 이상 → 서버로 출력 잘해줌 You have joined too many channels OK