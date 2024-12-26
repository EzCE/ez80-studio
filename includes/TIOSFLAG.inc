?flags			:= 0D00080h
;System Flags
;----------------------------------------------------------------------
?ioDelFlag		:= 0h
?inDelete		:= 0		;1 = DELETE SCREEN

?trigFlags		:= 0h		;Trigonometry mode settings
?trigDeg			:= 2		;1 = degrees, 0=radians

?kbdFlags		:= 0h		;Keyboard scan
?kbdSCR			:= 3		;1=scan code ready
?kbdKeyPress		:= 4		;1=key has been pressed

?doneFlags		:= 0h		;display "Done"
?donePrgm		:= 5		;1=display "Done" after prgm
;----------------------------------------------------------------------
?editFlags		:= 1h
?editOpen		:= 2		;1=edit buffer is open

?ansFlags		:= 1
?AnsScroll		:= 3		;1=answer can scroll, seems must be reset in order to move about edit buffer

?monFlags		:= 1h	 	;monitor flags
?monAbandon		:= 4		;1=don't start any long process in put away (#715)
;----------------------------------------------------------------------
?plotFlags		:= 2h		;plot generation flags
?plotLoc 		:= 1		;0=bkup and display, 1=display only
?plotDisp		:= 2		;1=plot is in display, 0=text in display, this also indicates whether graph is being shown or not

?grfModeFlags		:= 2h		;graph mode settings
?grfFuncM		:= 4		;1=function graph
?grfPolarM		:= 5		;1=polar graph
?grfParamM		:= 6		;1=parametric graph
?grfRecurM		:= 7		;1=RECURSION graph
;----------------------------------------------------------------------
?graphFlags		:= 3h
?graphDraw		:= 0		;0=graph is valid, 1=redraw graph(dirty)
?graphCursor		:= 2
;----------------------------------------------------------------------
?grfDBFlags		:= 4h
?grfDot			:= 0		;0=line, 1=dot
?grfSimul		:= 1		;0=sequential, 1=simultaneous
?grfGrid 		:= 2		;0=no grid, 1=grid
?grfPolar		:= 3		;0=rectangular, 1=polar coordinates
?grfNoCoord		:= 4		;0=display coordinates, 1=off
?grfNoAxis		:= 5		;0=axis, 1=no axis
?grfLabel		:= 6		;0=off, 1=axis label
;----------------------------------------------------------------------
?textFlags		:= 5h		;Text output flags
?textEraseBelow		:= 1		;1=erase line below small char
?textScrolled		:= 2		;1=screen scrolled
?textInverse		:= 3		;1=display inverse bit-map
?textInsMode		:= 4		;0=overstrike, 1=insert mode
;----------------------------------------------------------------------
?ParsFlag		:= 6h		;PARSER flags
?listOpen		:= 5		; {...}
?matrixOpen1		:= 6		; [[...]]
?matrixOpen2		:= 7		; [...]
;----------------------------------------------------------------------
?ParsFlag2		:= 7h		;PARSER flags
?numOP1			:= 0		;1=RESULT IN OP1, 0=NO RESULT
;----------------------------------------------------------------------
?newDispF		:= 8h		;Derivative mode flags
?preClrForMode		:= 0		;1=HELP BLINK ON MODE SCREEN
?allowProgTokens		:= 1		;1=allow programming tokens to be parsed in BASIC programs
?progExecuting		:= 1

?apdFlags		:= 8h		;Automatic power-down
?apdAble 		:= 2		;1=APD enabled
?apdRunning		:= 3		;1=APD clock running
?apdWarmStart		:= 4		;1=calculator is turning on from APD or power loss
;----------------------------------------------------------------------
?web_err_mask		:= 60h
;----------------------------------------------------------------------
?onFlags 		:= 9h		;on key flags
?parseInput		:= 1		;1=parse input when done
?onRunning		:= 3		;1=calculator is running
?onInterrupt		:= 4		;1=on key interrupt request

?statFlags		:= 9h		;statistics flags
;unknown		equ 5		;unknown
?statsValid		:= 6		;1=stats are valid
;unknown		equ 7		;unknown
;----------------------------------------------------------------------
?fmtFlags		:= 0Ah		;numeric format flags
?fmtExponent		:= 0	 	;1=show exponent, 0=no exponent
?fmtEng			:= 1	 	;1=engineering notion, 0=scientific

?numMode			:= 0Ah
?fmtReal			:= 5
?fmtRect			:= 6
?fmtPolar		:= 7

?realMode		:= 5
?rectMode		:= 6
?polarMode		:= 7

?fmtBaseMask		:=  00011100b	; mask to base flags
?fmtBaseShift		:=  2		; offset to base flags
;----------------------------------------------------------------------
?fmtOverride		:= 0Bh		;copy of fmtFlags with conversion override
;----------------------------------------------------------------------
?fmtEditFlags		:= 0Ch		;numeric editing flags
?fmtEdit			:= 0		;1=format number for editing

?curFlags		:= 0Ch		;Cursor
?curAble 		:= 2		;1=cursor flash is enabled
?curOn			:= 3		;1=cursor is showing
?curLock 		:= 4		;1=cursor is locked off

?cmdFlags		:= 0Ch		;command editor flags
?cmdVirgin		:= 5		;1=nothing has been typed in cmd bfr
?cmdExec			:= 6           ;1=need to execute a command
;----------------------------------------------------------------------
?appFlags		:= 0Dh		;application flags
?appWantIntrpt		:= 0		;1=want ON key interrupts
?appTextSave		:= 1		;1=save characters in textShadow
?appAutoScroll		:= 2		;1=auto-scroll text on last line
?appMenus		:= 3		;1=process keys that bring up menus, 0=check Lock menu flag
?appLockMenus		:= 4		;1=ignore menu keys, 0=switch to home screen and bring up menu
?appCurGraphic		:= 5		;1=graphic cursor
?appCurWord		:= 6		;1=text cursor covers entire word
?appExit 		:= 7		;1=application handles [EXIT] key itself

?appWantIntrptF		:= 1 shl appWantIntrpt
?appTextSaveF		:= 1 shl appTextSave
?appAutoScrollF		:= 1 shl appAutoScroll
?appMenusF		:= 1 shl appMenus
?appLockMenusF		:= 1 shl appLockMenus
?appCurGraphicF		:= 1 shl appCurGraphic
?appCurWordF		:= 1 shl appCurWord
?appExitF		:= 1 shl appExit
;----------------------------------------------------------------------
?rclFlag			:= 0Eh		;OS recall queue flags
?enableQueue		:= 7		;1 = enable recall queue
;----------------------------------------------------------------------
?seqFlags		:= 0Fh		;Sequential Graph flags
?webMode			:= 0		;0 = NORMAL SEQ MODE, 1 = WEB MODE
?webVert			:= 1
?sequv			:= 2		;U vs V
?seqvw			:= 3		;V vs W
?sequw			:= 4		;U vs W
;----------------------------------------------------------------------
?promptFlags		:= 11h		;prompt line flags
?promptEdit		:= 0		;1=editing in prompt buffer
;unknown		equ 7		;unknown
;----------------------------------------------------------------------
?indicFlags		:= 12h		;Indicator flags
?indicRun		:= 0		;1=run indicator ON
?indicInUse		:= 1		;indicator save area in use=1, free=0 ;resetting will disable 2nd while in _getkey

?shiftFlags		:= 12h		;[2nd] and [ALPHA] flags
?shift2nd		:= 3		;1=[2nd] has been pressed
?shiftAlpha		:= 4		;1=[ALPHA] has been pressed
?shiftLwrAlph		:= 5		;1=lower case, 0=upper case
?shiftALock		:= 6		;1=alpha lock has been pressed
?shiftKeepAlph		:= 7		;1=cannot cancel alpha shift
;----------------------------------------------------------------------
?tblFlags		:= 13h		;table flags.
?autoFill		:= 4		;1=prompt, 0=fillAuto
?autoCalc		:= 5		;1=prompt, 0=CalcAuto
?reTable			:= 6		;0=table is okay, 1=must recompute table.
;----------------------------------------------------------------------
?sGrFlags		:= 14h
?grfSplit		:= 0		;1=Split Graph, 0=Normal
?vertSplit		:= 1		;1=Vertical (left-right) Split
?grfSChanged		:= 2		;1=Graph just changed Split <-> normal
?grfSplitOverride	:= 3		;1 = ignore graph split flag if set
?write_on_graph		:= 4		;1 = TEXT OR EQU WRITING TO GRAPH SCREEN
?g_style_active		:= 5		;1 = GRAPH STYLES ARE ENABLED, USE THEM
?cmp_mod_box		:= 6		;1 = DOING MOD BOX PLOT COMPUTATION
?textWrite		:= 7
;----------------------------------------------------------------------
?newIndicFlags		:= 15h
?extraIndic		:= 0
?saIndic			:= 1
;3 has something to do with stat/list editor
;----------------------------------------------------------------------
?interruptFlags		:= 16h
?secondTimerEnabled	:= 0		;1 = second hardware timer enabled
;----------------------------------------------------------------------
?smartFlags		:= 17h
?smarter_mask		:= 3
?smarter_test		:= 1
?smartGraph		:= 0
?smartGraph_inv		:= 1
;----------------------------------------------------------------------
?traceFlags		:= 18h
?grfExpr			:= 0		;set to hide expression while tracing
;----------------------------------------------------------------------
;There is a flag 19h.
;----------------------------------------------------------------------
?statFlags2		:= 1Ah
?statDiagnosticsOn	:= 0		;1 = stat diagnostics on
?noDelStat		:= 2		;1 = don't delete stats
;----------------------------------------------------------------------
?apdFlags2		:= 1Bh
?warmStartInt		:= 6           ;1 = a warm start is occurning before the next interrupt
;----------------------------------------------------------------------
;There is a flag 1Ch (stats-related).
;----------------------------------------------------------------------
;There is a flag 1Dh.
;----------------------------------------------------------------------
;There is a flag 1Eh.
;----------------------------------------------------------------------
?varTypeMask		:= 1Fh		;is this a flag byte? yes
?varGraphRef		:= 6
;----------------------------------------------------------------------
?graphFlags2		:= 1Fh
?splitOverride		:= 3		;0 = force full screen with ParseInp, or something
;----------------------------------------------------------------------
?asm_Flag1		:= 21h		;ASM CODING
?asm_Flag2		:= 22h		;ASM CODING
?asm_Flag3		:= 23h		;NO LONGER AVAILABLE
;----------------------------------------------------------------------
?arcFlag			:= 24h
?checkBatteryLevelFirst	:= 0		;1 = check battery levels in Arc_Unarc first and throw error if low

?getSendFlg		:= 24h
?comFailed		:= 1		;1 = Get/Send Communication Failed

?selfTestFlag		:= 24h
?resetOnPowerOn		:= 2		;1 = Force RAM reset when APD disabled on next power on

?appLwrCaseFlag		:= 24h
?lwrCaseActive		:= 3
;----------------------------------------------------------------------
?contextFlags		:= 25h
?nocxPutAway		:= 5		;1 = do not call cxPutAway routine
;----------------------------------------------------------------------
?groupFlags		:= 26h		;used temporarily in Arc_Unarc
?inGroup			:= 1		;1 = IN GROUP CONTEXT
?noCompletionByte	:= 2		;1 = do not write 0FCh when calling Arc_Unarc, leave as 0FEh
?noDataWrite		:= 3		;1 = do not write data when calling Arc_Unarc, nor size bytes
?writeSizeBytesOnly	:= 5		;1 = only write size bytes when calling Arc_Unarc
;----------------------------------------------------------------------
?statusBarFlags		:= 27h
?noStatusBarMode		:= 7		; 1 = abort drawing of statusbar mode, like "TEST MODE ENABLED"
;----------------------------------------------------------------------
?APIFlg			:= 28h
?appAllowContext		:= 0           ;app wants context changes to happen

?appRunning		:= 4		;app is currently running
?appRetKeyOff		:= 7		;1 = GetKey returns kOff when [2nd]+[ON] pressed
;----------------------------------------------------------------------
?apiFlg2			:= 29h
;----------------------------------------------------------------------
?apiFlg3			:= 2Ah
;----------------------------------------------------------------------
?apiFlg4			:= 2Bh
?cellOverride		:= 1		;use cell override
?fullScrnDraw		:= 2		;DRAW INTO LAST ROW/COL OF SCREEN
;----------------------------------------------------------------------
?xapFlag0		:= 2Eh		;external app flags, do not use 0,(iy+2Eh) (used by mouse routines)
?xapFlag1		:= 2Fh
?xapFlag2		:= 30h
?xapFlag3		:= 31h
;----------------------------------------------------------------------
?fontFlags		:= 32h
?fracDrawLFont		:= 2
?fracTallLFont		:= 3
?customFont		:= 7
;----------------------------------------------------------------------
?hookflags1		:= 33h		;also scriptFlag, rclFlag2, backGroundLink
?alt_On			:= 0		;run ONSCRPT at startup
?alt_Off			:= 1		;run OFFSCRPT at shutdown
?useRclQueueEnd		:= 2		;1 = external mode
?ignoreBPLink		:= 3		;1 = override flag for link activity hook
?bPLinkOn		:= 4		;1 = link activity hook active
?enableKeyEcho		:= 5		;1 = sends keypresses back to connected calc as remote control packets (with GetCSC vs. GetKey codes...really dumb, TI)
?noTempDelete		:= 6		;1 = do not delete temporary programs at homescreen
;----------------------------------------------------------------------
?hookflags2		:= 34h		;also sysHookFlg
?getCSCHookActive	:= 0		;1 = GetCSC hook active
?libraryHookActive	:= 1		;1 = library hook active
?noHookActive		:= 2		;1 = same as 0; never used by OS
?homescreenHookActive	:= 4		;1 = homescreen hook active
?rawKeyHookActive	:= 5		;1 = raw key hook active
?catalog2HookActive	:= 6		;1 = catalog 2 hook active
?cursorHookActive	:= 7		;1 = cursor hook active
;----------------------------------------------------------------------
?hookflags3		:= 35h		;also sysHookFlg1
?tokenHookActive		:= 0		;1 = token hook active
?localizeHookActive	:= 1		;1 = localize hook active
?windowHookActive	:= 2		;1 = window hook active
?graphHookActive		:= 3		;1 = graph hook active
?yEquHookActive		:= 4		;1 = Y= hook active
?fontHookActive		:= 5		;1 = font hook active
?regraphHookActive	:= 6		;1 = regraph hook active
?drawingHookActive	:= 7		;1 = drawing hook active
;----------------------------------------------------------------------
?hookflags4		:= 36h		;also sysHookFlag2
?traceHookActive		:= 0		;1 = trace hook active
?parserHookActive	:= 1		;1 = parser hook active
?appChangeHookActive	:= 2		;1 = app change hook active
?catalog1HookActive	:= 3		;1 = catalog 1 hook active
?helpHookActive		:= 4		;1 = help hook active
?cxRedispHookActive	:= 5		;1 = cxRedisp hook active
?menuHookActive		:= 6		;1 = menu hook active
?silentLinkHookActive	:= 7		;1 = silent link hook active
;----------------------------------------------------------------------
;hookflags2Override	equ 37h		;set corresponding bit to kill iy+35h hook when executing app
;----------------------------------------------------------------------
;hookflags3Override	equ 38h		;set corresponding bit to kill iy+36h hook when executing app
;----------------------------------------------------------------------
;hookflags4Override	equ 39h		;set corresponding bit to kill iy+37h hook when executing app
;----------------------------------------------------------------------
?hookflags5		:= 3Ah
?usbActivityHookActive	:= 0		;1 = USB activity hook active
;----------------------------------------------------------------------
?plotFlag3		:= 3Ch
?bufferOnly		:= 0
?useFastCirc		:= 4
;----------------------------------------------------------------------
?dBKeyFlags		:= 3Dh
?keyDefaultsF		:= 6		;1 = GetKey returns extended keycodes with TI-Keyboard
;----------------------------------------------------------------------
?silentLinkFlags		:= 3Eh
?silentLinkActive	:= 0		;1 = SE/84+ silent link is active

?extraHookFlags		:= 3Eh
?checkCatalog2HookVer	:= 3		;1 = check catalog 2 hook's version before executing it (and error or take other action if so)
?openLibActive		:= 4		;1 = OpenLib( was successfully called on a Flash application (ExecLib will error if zero)
;----------------------------------------------------------------------
?clockFlags		:= 3Fh
?notMDYMode		:= 0		;0 = M/D/Y format
?isYMDMode		:= 1		;1 = Y/M/D format
?is24Hour		:= 2		;1 = clock in 24 hour mode
?inAfternoon		:= 3		;1 = current time is in afternoon (PM) (I think)
?useTokensInString	:= 4		;1 = use tokens instead of characters when displaying clock as string (for getTmStr and getDtStr vs. MODE screen) (keep this reset)
?displayClock		:= 5		;1 = display clock (this is set every second, reset otherwise)
?clockOn			:= 6		;1 = clock on
;----------------------------------------------------------------------
?mathprintFlags		:= 44h
?mathprintEnabled	:= 5		;1 = use mathprint styling
;----------------------------------------------------------------------
?InitialBootMenuFlags	:= 45h
?dispinitialBootMenu	:= 4		; 1 = don't display the initial boot menu
;----------------------------------------------------------------------
?backlightFlags		:= 46h
?restoreBrightness	:= 0		;1 = restore lcd brightness when needed
;----------------------------------------------------------------------
?grFlags			:= 4Ah
?drawGrLbls		:= 0		;1 = don't draw Graph Labels (this is usually reset anyway)

?putMapFlags		:= 4Ah
?usePixelShadow2		:= 3		;1 = use pixelshadow2, not pixelshadow
?putMapUseColor		:= 4		;1 = use custom color
;----------------------------------------------------------------------
?graphDispFlags		:= 4Bh
?backgroundValid		:= 4		;1 = items in graph background are still valid
;----------------------------------------------------------------------

