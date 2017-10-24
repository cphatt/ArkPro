#! /bin/sh
    echo $1 >> /tmp/asd
    echo $2 >> /tmp/asd
    ret1=`stat -c %Y $1.h`
    ret2=`stat -c %Y $2.h`
    if [ $ret1 -gt $ret2 ]; then
        /opt/external-toolchain/bin/QDBusProxy $1
	if [ $? -eq 0 ]; then
		touch /tmp/update.h
		echo "cmd ok!" > /tmp/cmd.txt
		echo "cmd ok!"
	else 
		echo "cmd failed!" > /tmp/cmd.txt
		echo "cmd failed!"
	fi
    else
	touch /tmp/noupdate.h
	echo "noupdate"
    fi
    echo `pwd` > /tmp/pwd.txt
