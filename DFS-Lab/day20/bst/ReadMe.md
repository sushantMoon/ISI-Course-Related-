* Generating Random BST
    Author: Prof. Mandar Maitra

```sh
    gcc -g -Wall -o bst1 bst1.c bst-utils.c
    ./bst1 10 2> bst1.tex
    latex tree.tex; dvips -o tree.ps tree; ps2pdf tree.ps
    <view tree.ps using installed document viewer>
```
Note : tree.tex is the boiler plate, it includes the bast1.tex


If using OverLeaf.com

You would need to upload, 
1. macros.tex
2. tree.tex
2. bst1.tex 

Compile the `tree.tex` file,using compiler XeLatex
