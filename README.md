# unreal-practice-3
* TPS 장르 프로젝트 연습
* 마찬가지로 연습 목적으로 알파 단계까지 구현

# 1. 프로토타입
- 순서 : 프로젝트 설정 → 플레이어 제작 → 적 제작
    - 프로젝트 진행에 필요한 매크로 함수 작성
## 작업 내용
1. TPS 프로젝트 생성
2. **유틸리티 매크로** 작성
3. 플레이어 생성
4. 플레이어 3인칭 카메라 및 외관 붙이기
5. 플레이어 이동 처리
6. 총알 제작
7. 총알 발사
8. 스나이퍼 모드 구현
9. 적 생성
10. 적 AI 제어를 위한 FSM 제작
    *  `세부 카메라 모션 처리`, `애니메이션 처리`는 알파 단계에서 진행
# 2. 알파
- 프로토타입 : 프로젝트에서 검증하고자하는 핵심 기능 구현 단계
- 알파 : 기획의 전체적인 내용을 구현하는 단계
    - 보통 알파까지 구현하고 나면 선별된 테스터에게 테스트를 진행하여 의견을 반영하고
    베타 버전으로 넘어감
## 작업할 내용
1. 주인공, 적 디자인 에셋 처리
    1. 애니메이션 처리 포함
        1. 상태머신
        2. 블렌드 스페이스
        3. 애니메이션 몽타주
2. 적 AI 내비게이션 시스템
    1. 지능화된 AI를 위한 복잡한 환경에서의 길찾기 기능
3. 카메라 셰이크
4. 다중 적 생성

# 학습 내용
* [유틸리티 매크로](https://defiant-scilla-378.notion.site/1f003e1dfb178034aeb8eb602da3e5e3?pvs=74)
* [UClass와 CDO](https://defiant-scilla-378.notion.site/UClass-CDO-Class-Default-Object-1f003e1dfb1780ea889ef82ea3a1c2f7)
* [UE C++ 라인트레이스](https://defiant-scilla-378.notion.site/UE-C-1e403e1dfb17801d8767fc46ab07b2e6)
* [UE 애니메이션 블루프린트 워크플로우](https://defiant-scilla-378.notion.site/UE-1f003e1dfb17800f8fd3d2fa633458f9)
* [카메라 쉐이크](https://defiant-scilla-378.notion.site/1f003e1dfb17803692c8dd4ac3bf1959)
* [UE C++ 적 AI 구성 : 내비게이션 적용](https://defiant-scilla-378.notion.site/UE-C-AI-1f003e1dfb1780af9c3dc6d086e22be7)
