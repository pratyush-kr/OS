#KALI TYPE TERMINAL comment it to get back to normal
PS1="\[\e]0;\u@\h: \w\a\]\[\033[;32m\]┌──${debian_chroot:+($debian_chroot)──}${VIRTUAL_ENV:+(\[\033[0;1m\]$(basename $VIRTUAL_ENV)\[\033[;32m\])}(\[\033[1;34m\]\u@\h\[\033[;32m\])\$(__git_ps1)-[\[\033[0;1m\]\w\[\033[;32m\]]\n\[\033[;32m\]└─\[\033[1;34m\]\$\[\033[0m\] "
export GIT_PS1_SHOWDIRTYSTATE=1
export GIT_PS1_SHOWSTASHSTATE=1
export GIT_PS1_SHOWUPSTREAM=auto

# output filter
of() { 
    if [ -n "$*" ]; then   
        # write the real command to history without the prefix "of" 
        history -s "$*"

        # catch the command output
        errorMsg=$( $* 2>&1 )

        # check if the command output contains not a GTK-Warning
        echo "$errorMsg"2>>~/.errlog
    fi
}

#To Use this remove '#' write the function "of" before every command if the user presses F12
#bind '"\e[24~": "\e[1~ of \e[4~\n"'

#aliases
alias gedit='of gedit'
alias reanme='mv'
alias cls='clear'
alias upgrade='sudo apt upgrade'
alias update='sudo apt update && upgrade'
