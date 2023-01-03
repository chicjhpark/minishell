# minishell - 팀 프로젝트
### Intoduction
- bash나 zsh과 같은 작고 간단한 쉘 프로그램입니다.
### Directions
```
$> make
$> ./minishell
$>
```
### Rules
|   |   |
| - | - |
| **Allowed functions** | readline, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, malloc, free, write, open, read, close, fork, wait, waitpid, wait3, wait4, signal, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, errno, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs |

- 닫히지 않은 따옴표나 특정되지 않은 특수문자 (\나 ; 등...) 을 해석하지 않아야 합니다.
- 전역변수는 한 개 이상을 사용할 수 없으며, 왜 전역변수를 사용했는지 깊게 생각해 보고 그 이유를 설명할 수 있어야 합니다.
- 새로운 명령어를 입력할 수 있는 프롬프트를 보여줘야 합니다.
- 작업 히스토리를 갖고 있어야 합니다.
- (PATH 변수나 상대, 절대 경로를 활용하여) 올바른 실행 파일을 찾아 실행할 수 있어야 합니다.
- 다음의 내장 기능을 실행할 수 있어야 합니다.
  - -n 옵션을 사용할 수 있는 echo
  - 오직 상대 또는 절대경로만 사용하는 cd
  - 옵션이 없는 pwd
  - 옵션이 없는 export
  - 옵션이 없는 unset
  - 옵션이나 인자값이 없는 env
  - 옵션이 없는 exit
- `'`는 일련의 문자열에 대한 해석을 금지합니다.
- `"`는 `$`를 제외한 모든 문자열에 대한 해석을 금지합니다.
- 리다이렉션
  - `<` 는 입력을 리다이렉션 하여야 합니다
  - `>` 는 출력을 리다이렉션 하여야 합니다
  - `<<` 는 현재 소스에서 구분자를 포함한 줄을 만나기 전까지 입력값을 읽어들입니다. 기록을 업데이트할 필요는 없습니다!
  - `>>` 는 출력을 추가 모드로 리다이렉션합니다.
- 파이프 `|` : 각 파이프라인마다 명령어의 출력값은 파이프로 연결되어 다음 명령어의 입력값으로 들어가야 합니다.
- 환경 변수 ($ 다음에 문자열이 오는 형식) 은 그들의 값으로 확장되어야 합니다.
- `$?`는 가장 최근에 실행한 포그라운드 파이프라인의 종료 상태를 확장하여야 합니다
- ctrl-C, ctrl-D, ctrl-\ 는 bash와 동일하게 동작하여야 합니다.
- 상호작용이 가능할 때:
  - ctrl-C는 새로운 줄에 새로운 프롬프트를 출력합니다
  - ctrl-D는 쉘을 종료합니다.
  - ctrl-\은 아무런 동작도 하지 않습니다.
### [Development document](https://github.com/chicjhpark/minishell.wiki.git)
