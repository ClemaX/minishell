https://www.gnu.org/software/libc/manual/html_node/Input-Modes.html

https://blog.nelhage.com/2009/12/a-brief-introduction-to-termios-termios3-and-stty/


To do:

1) Style
- prompt
- edit a line where the cursor is
- move cursor right and left (+ edit)
- up down for history
- copy, paste, cut
- ctrl right ctrl left
- home and end
- last thing is weird


2) Use
- launch and search exe (a, b, c)
- builtings (a, c)
- ; use (a, b)
- ' " use (a, b)
- () (a, b)
- && || (a, b)
- wildcard * (a, b, c)
- > << >> < stuff (a, b)
- pipes (a, b)
- env var (all)
- $? (all)
- keys (ctrl) (none)


3) Structure
- a)lexer for tokens 
- b)tokens to btree 
- c)tbree for execution

t_token *k
-val = 
-flags