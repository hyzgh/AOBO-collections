syntax on
set nu
set tabstop=4
set shiftwidth=4
colo evening
set mouse=a
set cin

map <F2> :call Import() <CR>
map <F3> :only<CR>:60vsp in<CR>:sp out<CR><C-W><RIGHT>
nnoremap <F9>   <Esc>:w<CR> :! ctags %<CR> :!g++ -std=c++11 % -o /tmp/a.out && /tmp/a.out<CR>
map <F10> <Esc>:w<CR>gg"+1000Y

func Import()
	exec "r ~/code/z"
endfunc
