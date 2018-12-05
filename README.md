# DirectX11Sample
VC++ 2008 로 DirectX11 기반 샘플 프로그램을 개발하는 프로젝트입니다.

### 빌드 환경
본 프로젝트를 빌드하기 위한 조건은 다음과 같습니다.

* VC++ 2008 인스톨
* C:\Program Files (x86)\Microsoft DirectX SDK (June 2010) 폴더에 DXSDK_Jun10.exe 인스톨

### 개발자 정보
본 프로젝트의 개발자 정보는 다음과 같습니다.

* 블로그: http://blog.naver.com/websearch

### 폴더 설명
본 프로젝트에 포함된 DirectX11 기반 샘플 프로그램을 폴더별로 설명하면 다음과 같습니다.

* TestTriangle
  * DirectX11 기반 초간단 삼각형 그리기 예제
* TestCube
  * 큐브 그리기 예제
  * 큐브의 각 면을 다른 색으로 표시하여서 카메라 위치에 따른 큐브의 모양 변화를 확인할 수 있다
* TestCubeIndex
  * 인덱스를 이용한 큐브 그리기 예제
  * TestCube 소스 코드 기반으로 인덱스로 큐브를 그리기 기능을 추가함
* TestTwoCube
  * 2 개의 큐브 그리기 예제
  * TestCubeIndex 소스 코드 기반으로 2개의 큐브 그리기 기능을 추가함
* TestCubeLighting
  * 조명 예제
  * TestTwoCube 소스 코드 기반으로 1개의 큐브에 조명 처리하는 기능을 추가함
* TestCubeTexture
  * 텍스처 예제
  * TestCubeLighting 소스 코드 기반으로 큐브에 텍스처를 처리하는 기능을
* Tetris
  * DirectX11 3D 기반의 2차원 테트리스 프로그램
