# DirectX11 기반으로 테트리스 게임 개발

### 게임 방법

* 좌/우 방향키로 이동 블록을 좌/우로 이동할 수 있다.
* 상 방향키로 이동 블록을 회전시킬 수 있다.
* 하 방향키로 이동 블록을 2 개 블록 높이만큼 아래로 이동할 수 있다.

### 알려진 버그

* float 로 큐브 위치를 저장하고 충돌 여부를 검사하는 과정에서 컴퓨터의 float 연산 결과가 실제 수학 연산과 달라서 이동 블록이 고정 블록 옆에 붙어 버리는 버그가 있는 것 같습니다.
* 블록이 좌/우 벽과 가까이 있을 경우 회전이 되지 않을 수 있습니다.
  * 회전시 좌/우 벽과 충돌된다고 판단되면 회전하지 못 하도록 개발하였습니다.

### 관련 포스트

https://blog.naver.com/websearch/221413061104

### 실행화면

![Alt text](https://blogfiles.pstatic.net/MjAxODEyMDVfMjE4/MDAxNTQzOTk5NDg1NzEy.zE6D7fo1nKiGWVKZW6FMSkrS4O6aKTmCk6T51hA5Sy4g.o9JdVWen1Ueqe-gh4KhYf3wu0BqMfoir4A_De5l5PKgg.PNG.websearch/%ED%85%8C%ED%8A%B8%EB%A6%AC%EC%8A%A4-2.png)


