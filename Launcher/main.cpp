#include "UserInterface/MainWidget/MainWidget.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include "Utility.h"
#include "BusinessLogic/Widget/Widget.h"
#include "BusinessLogic/Setting/Setting.h"
#include "BusinessLogic/Multimedia/Multimedia.h"
#include "ArkApplication.h"
#include "SettingService.h"
#include "MultimediaService.h"
#include "AudioService.h"
#include "UserInterface/Common/Utility.h"
#include <QDebug>
#include <QTextCodec>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef gcc
#include <signal.h>
static inline void signalHandler(int signo);
#endif

void setTextCodec();
void customMessageOutput(QtMsgType type, const char* msg);

#define APPS

int main(int argc, char *argv[])
{
    Utility::startTime();
    if ((1 == argc) || (2 == argc)) {
#ifdef APPS
        int tempArgc(4);
        char* tempArgv[4] = {argv[0], "-t", "-qws", "-apps"};
#else
        int tempArgc(3);
        char* tempArgv[3] = {argv[0], "-t", "-qws"};
#endif
        argc = tempArgc;
        argv = tempArgv;
    }
    int result(-1);
    while(-1 != (result = getopt(argc, argv, "t:"))) {
        qDebug("option=t, optopt=%c, optarg=%s\n", optopt, optarg);
        QString argument(optarg);
        qDebug() << "argument" << argument;
        switch(result) {
        case 't': {
            if (QString("-qws") == argument) {
                qInstallMsgHandler(customMessageOutput);
#ifdef gcc
                signal(SIGTERM, signalHandler);
#endif
                ArkApplication app(argc, argv);
                setTextCodec();
                app.setApplicationName(ArkMicroLauncherService);
                MainWidget mainWindow;
                Q_UNUSED(mainWindow);
                return app.exec();
            } else if (SettingApplication == argument) {
                QCoreApplication app(argc, argv);
                app.setApplicationName(ArkMicroSettingService);
                SettingService settingService;
                Q_UNUSED(settingService)
                return app.exec();
            } else if (MultimediaApplication == argument) {
                QCoreApplication app(argc, argv);
                setTextCodec();
                app.setApplicationName(ArkMicroMultimediaService);
                MultimediaService multimediaService;
                Q_UNUSED(multimediaService)
                return app.exec();
            } else if (AudioApplication == argument) {
                QCoreApplication app(argc, argv);
                app.setApplicationName(ArkMicroAudioService);
                AudioService audioService;
                Q_UNUSED(audioService)
                return app.exec();
            }
            break;
        }
        default: {
            qDebug("default, result=%c\n",result);
            break;
        }
        }
    }
    return EXIT_FAILURE;
}

void customMessageOutput(QtMsgType type, const char *msg)
{
    switch (type) {
    case QtDebugMsg: {
        fprintf(stderr, "Debug: %s\n", msg);
        break;
    }
    case QtWarningMsg: {
        fprintf(stderr, "Warning: %s\n", msg);
        break;
    }
    case QtCriticalMsg: {
        fprintf(stderr, "Critical: %s\n", msg);
        break;
    }
    case QtFatalMsg: {
        fprintf(stderr, "Fatal: %s\n", msg);
        abort();
        break;
    }
    default: {
        break;
    }
    }
}

void setTextCodec()
{
    QTextCodec* textCodec = QTextCodec::codecForName("UTF-8");
    if (NULL != textCodec) {
        QTextCodec::setCodecForCStrings(textCodec);
        QTextCodec::setCodecForTr(textCodec);
        QTextCodec::setCodecForLocale(textCodec);
    } else {
        qDebug() << "get codecForName UTF-8 failed!";
    }
}

#ifdef gcc
static inline void signalHandler(int signo)
{
    qDebug() << "signalHandler" << signo;
    switch (signo) {
    case SIGTERM: {
        system("kill  `ps -elf | grep Launcher | grep audiomanager | awk '{print $4}'`");
        system("kill  `ps -elf | grep Launcher | grep setting | awk '{print $4}'`");
        system("kill  `ps -elf | grep Launcher | grep multimedia | awk '{print $4}'`");
        system("kill -10 `ps -elf | grep mplayer | grep slave | grep quiet | grep ao | grep alsa | awk '{print $4}'`");
        exit(EXIT_FAILURE);
        break;
    }
    default : {
        exit(EXIT_FAILURE);
        break;
    }
    }
}
#endif

///* Signal number definitions.  Linux version.
//   Copyright (C) 1995-2016 Free Software Foundation, Inc.
//   This file is part of the GNU C Library.

//   The GNU C Library is free software; you can redistribute it and/or
//   modify it under the terms of the GNU Lesser General Public
//   License as published by the Free Software Foundation; either
//   version 2.1 of the License, or (at your option) any later version.

//   The GNU C Library is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//   Lesser General Public License for more details.

//   You should have received a copy of the GNU Lesser General Public
//   License along with the GNU C Library; if not, see
//   <http://www.gnu.org/licenses/>.  */

//#ifdef	_SIGNAL_H

///* Fake signal functions.  */
//#define SIG_ERR	((__sighandler_t) -1)		/* Error return.  */
//#define SIG_DFL	((__sighandler_t) 0)		/* Default action.  */
//#define SIG_IGN	((__sighandler_t) 1)		/* Ignore signal.  */

//#ifdef __USE_UNIX98
//# define SIG_HOLD	((__sighandler_t) 2)	/* Add signal to hold mask.  */
//#endif


///* Signals.  */
//#define	SIGHUP		1	/* Hangup (POSIX).  */
//#define	SIGINT		2	/* Interrupt (ANSI).  */
//#define	SIGQUIT		3	/* Quit (POSIX).  */
//#define	SIGILL		4	/* Illegal instruction (ANSI).  */
//#define	SIGTRAP		5	/* Trace trap (POSIX).  */
//#define	SIGABRT		6	/* Abort (ANSI).  */
//#define	SIGIOT		6	/* IOT trap (4.2 BSD).  */
//#define	SIGBUS		7	/* BUS error (4.2 BSD).  */
//#define	SIGFPE		8	/* Floating-point exception (ANSI).  */
//#define	SIGKILL		9	/* Kill, unblockable (POSIX).  */
//#define	SIGUSR1		10	/* User-defined signal 1 (POSIX).  */
//#define	SIGSEGV		11	/* Segmentation violation (ANSI).  */
//#define	SIGUSR2		12	/* User-defined signal 2 (POSIX).  */
//#define	SIGPIPE		13	/* Broken pipe (POSIX).  */
//#define	SIGALRM		14	/* Alarm clock (POSIX).  */
//#define	SIGTERM		15	/* Termination (ANSI).  */
//#define	SIGSTKFLT	16	/* Stack fault.  */
//#define	SIGCLD		SIGCHLD	/* Same as SIGCHLD (System V).  */
//#define	SIGCHLD		17	/* Child status has changed (POSIX).  */
//#define	SIGCONT		18	/* Continue (POSIX).  */
//#define	SIGSTOP		19	/* Stop, unblockable (POSIX).  */
//#define	SIGTSTP		20	/* Keyboard stop (POSIX).  */
//#define	SIGTTIN		21	/* Background read from tty (POSIX).  */
//#define	SIGTTOU		22	/* Background write to tty (POSIX).  */
//#define	SIGURG		23	/* Urgent condition on socket (4.2 BSD).  */
//#define	SIGXCPU		24	/* CPU limit exceeded (4.2 BSD).  */
//#define	SIGXFSZ		25	/* File size limit exceeded (4.2 BSD).  */
//#define	SIGVTALRM	26	/* Virtual alarm clock (4.2 BSD).  */
//#define	SIGPROF		27	/* Profiling alarm clock (4.2 BSD).  */
//#define	SIGWINCH	28	/* Window size change (4.3 BSD, Sun).  */
//#define	SIGPOLL		SIGIO	/* Pollable event occurred (System V).  */
//#define	SIGIO		29	/* I/O now possible (4.2 BSD).  */
//#define	SIGPWR		30	/* Power failure restart (System V).  */
//#define SIGSYS		31	/* Bad system call.  */
//#define SIGUNUSED	31

//#define	_NSIG		65	/* Biggest signal number + 1
//				   (including real-time signals).  */

//#define SIGRTMIN        (__libc_current_sigrtmin ())
//#define SIGRTMAX        (__libc_current_sigrtmax ())

///* These are the hard limits of the kernel.  These values should not be
//   used directly at user level.  */
//#define __SIGRTMIN	32
//#define __SIGRTMAX	(_NSIG - 1)

//#endif	/* <signal.h> included.  */
