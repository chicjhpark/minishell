# minishell - 팀 프로젝트
### Intoduction
- bash나 zsh과 같은 작고 간단한 쉘 프로그램
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
- 리다이렉션, 파이프, 환경변수, 따옴표 등 구분자들이 어떻게 어떤 순서로 들어오냐에 따라서 결과값과 에러 처리가 달라진다.
<img width="406" alt="스크린샷 2023-01-18 오전 7 25 40" src="https://user-images.githubusercontent.com/69841779/213025909-e8639894-1ffb-46f0-bee5-73799ca60434.png">

> bash에서 명령어들을 실행해가며 어떤 순서로 동작하는지 유추해 가면서 그 순서에 맞게 파싱을 하고 에러 처리를 했다. 최대한 bash와 유사한 결과값과 에러 처리를 하고 싶어 다양한 케이스를 만들어 실행해가며 코드를 수정했다.
- 파이프는 병렬 처리가 되어야 한다.
<img width="571" alt="스크린샷 2023-01-16 오후 4 08 31" src="https://user-images.githubusercontent.com/69841779/212618154-42db0db6-1c56-498d-87e5-c0b1d6b73949.png">

[참조 페이지](http://web.cse.ohio-state.edu/~mamrak.1/CIS762/pipes_lab_notes.html)
  
> 자식 프로세스는 각자 병렬적으로 실행시키도록 하고 부모 프로세스에서 wait 함수를 이용해서 모든 자식 프로세스가 종료되기 전까지 반복문을 통해 기다리게 했다.

