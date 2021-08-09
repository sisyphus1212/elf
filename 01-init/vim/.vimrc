if has("cscope")
          set csprg=/usr/bin/cscope
          set csto=0
          set cst
          set nocsverb
          " add any database in current directory
          if filereadable("cscope.out")
            cs add cscope.out
          " else add database pointed to by environment
          elseif $CSCOPE_DB != ""
            cs add $CSCOPE_DB
          endif
          set csverb
:map \ :cs find g <C-R>=expand("<cword>")<CR><CR>
:map s :cs find s <C-R>=expand("<cword>")<CR><CR>
:map t :cs find t <C-R>=expand("<cword>")<CR><CR>
:map c :cs find c <C-R>=expand("<cword>")<CR><CR>
:map C :cs find d <C-R>=expand("<cword>")<CR><CR>
:map f :cs find f <C-R>=expand("<cword>")<CR><CR>
endif
