# minishell - 팀 프로젝트
### Intoduction
- bash나 zsh과 같은 작고 간단한 쉘 프로그램입니다.
### Directions
```
$> make
$> ./minishell
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
- `ctrl-C`, `ctrl-D`, `ctrl-\`
### Development Report
