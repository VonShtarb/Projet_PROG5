# Projet_PROG5
Custom ELF Loader intended for pedagogic use

Requirements :
- Automake
- Autoconf

Steps to compile files :
1 - Clone the repository
2 - Extract directory from archive __V_base.tar.gz__
3 - Put it into V_base directory
4 - do ``cd V_base``
5 - do ``./configure`` then ``make``
6 - It should work if it's doesn't do ``autoreconf -vif`` then repeat step 5

execution : ``./ARM_runner_example  -<<A | B | C | D | H >>  (optional)<< num section | name section >>``
> A : display header
> B : display section table
> C : display a particular section __(given by optional parameter : section's name/num)__
> D : display symbol table
> H : display help

