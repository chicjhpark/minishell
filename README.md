# minishell - 팀 프로젝트
### Intoduction
- bash나 zsh과 같은 작고 간단한 쉘 프로그램입니다.
```
$> make
```
![minishell_directions](https://user-images.githubusercontent.com/69841779/211287293-3b0b73f6-ec0c-4532-9a45-de90007e83b8.gif)
### Implementation List
- 작업 히스토리
- PATH 변수나 상대, 절대 경로를 활용하여 실행 파일을 찾아 실행
- 빌트인
  - `-n` 옵션을 사용할 수 있는 `echo`
  - 상대 또는 절대 경로만 사용하는 `cd`
  - 옵션이 없는 `pwd`
  - 옵션이 없는 `export`
  - 옵션이 없는 `unset`
  - 옵션이나 인자값이 없는 `env`
  - 옵션이 없는 `exit`
- 리다이렉션 `<, >, <<, >>`
- 파이프 `|`
- 환경 변수 `$`
- 종료 상태 코드 (exit status) `$?`
- `ctrl-C`, `ctrl-D`, `ctrl-\`
### Development Report
#### 파싱 순서
1. 파이프, 리다이렉션, 띄어쓰기 단위로 구분해서 나눈다.
2. 위 구분자들이 정상적으로 들어왔는지 체크한다.
3. 자식 프로세스를 생성하고 그 안에서 프로세스 단위로 파싱을 한다.
#### 문제 해결
1. 리다이렉션, 파이프, 환경변수, 따옴표 등 구분자들이 어떻게, 어떤 순서로 들어오냐에 따라서 결과값이 달라진다.
<img width="415" alt="스크린샷 2023-01-13 오후 6 48 58" src="https://user-images.githubusercontent.com/69841779/212297687-e0ef69e0-b19d-4bd5-b31d-4495bddec0a6.png">

> 최대한 많은 케이스를 bash에서 실행해가며 어떤 원리로 작동하는지 알아보았고, 그에 맞는 파싱 순서를 만들어 보았다.
2. 파이프는 비동기 처리가 되어야한다.
