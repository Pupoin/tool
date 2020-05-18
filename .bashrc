# .bashrc
# Source global definitions
if [ -f /etc/bashrc ]; then
	. /etc/bashrc
fi



####################################### Universe ###############################################

#...................................  for color set   .........................................#
export CLICOLOR=1
export LSCOLORS=ExGxFxdaCxDaDahbadeche
export PS1='\[\033[01;36m\]\u@\h: \W\$\[\033[00m\] '

#..............................................................................................#

alias ll='ls -hl'
alias ycd='func() { cd $@; ll;}; func'
alias ymake='func()
	{ 
		cmake ..; 
		echo \ ;
		echo \ ;
		make -j $1;
	};func'

#...................................  define dustBin  ..........................................#



export dust='/Users/zhaoyangyuan/.dustBin'
if [ ! -d $dust ]; then
	mkdir -p $dust
fi
alias rl='ll -a $dust'
alias rm='func() { 		
					for i in $@
					do	
						str=${i}
						if test ${str:0:1} != "-"; then
							mv -iv ${i} $dust/"$(basename ${i})_$(date +"%F_%H:%M:%S")"
						else
							echo "dimiss ${i} ! "
						fi
					done
				}; func'

alias unrm='func() { 
					for i in $@
					do
						mv -iv $dust/${i} ./;
					done		
					}; func'
alias cleardust='func()
			{
				echo -e "\033[01;31mare you sure to deleate all in $dust ？[y/n] \033[0m" && 
				read confirm && 
				if [ $confirm == 'y' ] || [ $confirm == 'Y' ];then
					/bin/rm -rfv $dust/*;
				fi
			};func'
#..............................................................................................#



################################################################################################

