;RAM Equates
;--------------------------------
?ramStart		:= 0D00000h
?flags			:= 0D00080h		; location of OS Flags (+-80h)
?textFlagsLoc		:= 0D00085h            ; location of Text Flags
?apdFlagsLoc		:= 0D00088h		; location of APD Flags
?appFlagsLoc		:= 0D0008Dh		; location of App Flags
?rclFlagsLoc		:= 0D0008Eh            ; location of RCLQueue Flags
?shiftFlagsLoc		:= 0D00092h            ; location of Shifting Flags
?mathprintFlagsLoc	:= 0D000C4h		; location of MathPrint Flags

?strtokPtr		:= 0D000FFh            ; location of pointer used by C strtok
?printRoutine		:= 0D00108h            ; stores pointer to printing routines (3 scrap)

?flashByte		:= 0D00125h		; used for writing to flash

?cellOverrideAddr	:= 0D00166h
?curCell			:= 0D0016Eh            ; selected list cell

?SmallEditCancelParse	:= 0D001A4h

?curRowBackup		:= 0D0033Ch		; backup of curRow
?shiftFlagsLocBackup	:= 0D00358h		; backup of shiftFlagsLoc
?appFlagsLocBackup	:= 0D00366h		; backup of appFlagsLoc
?penRowBackup		:= 0D003E3h		; backup of penRow
?mathprintBackup		:= 0D003E6h		; backup of mathprint flags
?winLeftEdgeBackup	:= 0D003D2h		; backup of winLeftEdge
?catalogCurrentBackup	:= 0D003D3h		; backup of catalogCurrent
?menuCurrentSubBackup	:= 0D003D6h		; backup of menuCurrentSub
?menuNumMenusBackup	:= 0D003D8h		; backup of menuNumMenus
?menuCurrentBackup	:= 0D003DAh		; backup of menuCurrent
?cxCurAppBackup		:= 0D003DDh		; backup of cxCurApp

?curUnderBackup		:= 0D003E8h		; backup of curUnder

?appData			:= 0D00429h		; used for OFFSCRPT and ONSCRPT

?arcPtrEnd		:= 0D0052Fh

?tempSP			:= 0D0053Fh		; 3 byte scrap

?arcInfo			:= 0D00543h
?savedArcInfo		:= 0D0055Bh
?appBank_jump		:= 0D00584h

?kbdScanCode		:= 0D00587h		; scancode returned by GetCSC
?kbdLGSC			:= 0D00588h
?kbdPSC			:= 0D00589h
?kbdWUR			:= 0D0058Ah
?kbdDebncCnt		:= 0D0058Bh
?kbdKey			:= 0D0058Ch
?kbdGetKy		:= 0D0058Dh
?keyExtend		:= 0D0058Eh
?brightness		:= 0D0058Fh
?apdSubTimer		:= 0D00590h
?apdTimer		:= 0D00591h
?curTime			:= 0D00594h
?curRow			:= 0D00595h
?curCol			:= 0D00596h
?curOffset		:= 0D00598h
?curUnder		:= 0D00599h
?curYCol			:= 0D0059Ch
?curType			:= 0D0059Fh
?curXRow			:= 0D005A0h
?prevDData		:= 0D005A1h
?lFont_record		:= 0D005A4h
?sFont_record		:= 0D005C5h
?tokVarPtr		:= 0D005E9h
?tokLen			:= 0D005ECh

?indicCounter		:= 0D005F6h

?OP1			:= 0D005F8h
?OP1M			:= 0D005FAh
?OP2			:= 0D00603h
?OP2M			:= 0D00605h
?OP2EXT			:= 0D0060Ch
?OP3			:= 0D0060Eh
?OP3M			:= 0D00610h
?OP4			:= 0D00619h
?OP4M			:= 0D0061Bh
?OP5			:= 0D00624h
?OP5M			:= 0D00626h
?OP6			:= 0D0062Fh
?OP6M			:= 0D00631h
?OP6EXT			:= 0D00638h

?progToEdit		:= 0D0065Bh
?nameBuff		:= 0D00663h

?equ_edit_save		:= 0D0066Eh
?iMathPtr1		:= 0D0066Fh
?iMathPtr2		:= 0D00672h
?iMathPtr3		:= 0D00675h
?iMathPtr4		:= 0D00678h
?iMathPtr5		:= 0D0067Bh
?asm_data_ptr1		:= 0D0067Eh
?asm_data_ptr2		:= 0D00681h

?asm_ram			:= 0D00687h

?textShadow		:= 0D006C0h
?textShadCur		:= 0D007C4h
?textShadTop		:= 0D007C7h
?textShadAlph		:= 0D007C8h
?textShadIns		:= 0D007C9h
?cxMain			:= 0D007CAh
?cxPPutAway		:= 0D007CDh
?cxPutAway		:= 0D007D0h
?cxReDisp		:= 0D007D3h
?cxErrorEP		:= 0D007D6h
?cxSizeWind		:= 0D007D9h
?cxPage			:= 0D007DCh
?cxCurApp		:= 0D007E0h
?cxPrev			:= 0D007E2h ; 23 bytes are shadows of cxMain through cxCurApp and appFlags
?cxAppReturn		:= 0D007EBh

?onSP			:= 0D007FAh

?promptRow		:= 0D00800h
?promptCol		:= 0D00801h
?promptIns		:= 0D00802h
?promptShift		:= 0D00803h
?promptRet		:= 0D00804h
?promptValid		:= 0D00807h

?varType			:= 0D00813h
?varCurrent		:= 0D00814h
?varClass		:= 0D0081Ch

?catalogCurrent		:= 0D0081Dh ; word at this location starting with 6007h corresponds to what is highlighted in catalog
?catalogCurrentBackupM	:= 0D00820h ; backup of catalogCurrent for menus
?menuAppDepth		:= 0D00823h
?menuCurrent		:= 0D00824h
?menuCurrentSub		:= 0D00825h ; holds current submenu index
?menuSelected		:= 0D00826h ; holds currently selected item in current submenu
?menuNumMenus		:= 0D00827h ; holds number of submenus for this menu
?menuNumItems		:= 0D00828h ; holds number of items in this submenu
?appFlagsBackup		:= 0D00829h ; iy+appFlags backup for menu stuff
?cursorFlagsBackup	:= 0D0082Ah ; iy+cursorFlags backup for menu stuff
?curGStyleBackup		:= 0D0082Bh ; curGStyle backup for menu stuff
?graphFlagsBackup	:= 0D0082Ch ; iy+graphFlags backup for menu stuff

?progCurrent		:= 0D0082Dh
;D0082E	; something used to execute apps with _NewContext0
?userMenuSA		:= 0D00838h

?tempErrorMessage	:= 0D00842h

?ioPrompt		:= 0D00879h
?ioFlag			:= 0D00894h
?sndRecState		:= 0D00896h
?ioErrState		:= 0D00897h
?ioData			:= 0D008A1h

?penCol			:= 0D008D2h
?penRow			:= 0D008D5h
?rclQueue		:= 0D008D6h
?rclQueueEnd		:= 0D008D9h
?errNo			:= 0D008DFh
?errSP			:= 0D008E0h
?errOffset		:= 0D008E3h

?entryString		:= 0D008E6h
?entryResult		:= 0D008EAh

?statVarsOffset		:= 0D0117Fh
?asm_prgm_size		:= 0D0118Ch
?bstCounter		:= 0D0118Fh
?statVars		:= 0D01191h
?infVars			:= 0D013A4h
?infVar1			:= 0D013ADh
?infVar2			:= 0D013B6h
?infVar3			:= 0D013BFh
?infVar4			:= 0D013C8h
?infVar5			:= 0D013D1h
?infVar6			:= 0D013DAh
?infVar7			:= 0D013E3h
?infVar8			:= 0D013ECh
?infVar9			:= 0D013F5h
?infVar10		:= 0D013FEh
?infVar11		:= 0D01407h
?infVar12		:= 0D01410h
?infVar13		:= 0D01419h
?infVar14		:= 0D01422h
?infVar15		:= 0D0142Bh
?infVar16		:= 0D01434h
?infVar17		:= 0D0143Dh
?infVar18		:= 0D01446h
?infVar19		:= 0D0144Fh
?infVar20		:= 0D01458h

?curGStyle		:= 0D0146Dh
?curGY			:= 0D0146Eh
?curGY2			:= 0D01470h
?curGX2			:= 0D01471h ; currently selected equation while graphing
?freeSaveY		:= 0D01472h
?freeSaveX		:= 0D01474h

?XOffset			:= 0D014FAh
?YOffset			:= 0D014FCh
?lcdTallP		:= 0D014FDh
?pixWideP		:= 0D014FEh
?pixWide_m_1		:= 0D014FFh
?pixWide_m_2		:= 0D01501h
?lastEntryStkPtr		:= 0D01508h
?lastEntryStk		:= 0D0150Bh
?numLastEntries		:= 0D01D0Bh
?currLastEntry		:= 0D01D0Ch

?curPlotNumber		:= 0D01D45h

?curInc			:= 0D01D49h

?uXmin			:= 0D01D61h
?uXmax			:= 0D01D6Ah
?uXscl			:= 0D01D73h
?uYmin			:= 0D01D7Ch
?uYmax			:= 0D01D85h
?uYscl			:= 0D01D8Eh
?uThetMin		:= 0D01D97h
?uThetMax		:= 0D01DA0h
?uThetStep		:= 0D01DA9h
?uTmin			:= 0D01DB2h
?uTmax			:= 0D01DBBh
?uTStep			:= 0D01DC4h
?uPlotStart		:= 0D01DCDh
?unMax			:= 0D01DD6h
?uu0			:= 0D01DDFh
?uv0			:= 0D01DE8h
?unMin			:= 0D01DF1h
?uu02			:= 0D01DFAh
?uv02			:= 0D01E03h
?uw0			:= 0D01E0Ch
?uPlotStep		:= 0D01E15h
?uXres			:= 0D01E1Eh
?uw02			:= 0D01E27h
?Xmin			:= 0D01E33h
?Xmax			:= 0D01E3Ch
?Xscl			:= 0D01E45h
?Ymin			:= 0D01E4Eh
?Ymax			:= 0D01E57h
?Yscl			:= 0D01E60h
?ThetaMin		:= 0D01E69h
?ThetaMax		:= 0D01E72h
?ThetaStep		:= 0D01E7Bh
?TminPar			:= 0D01E84h
?TmaxPar			:= 0D01E8Dh
?Tstep			:= 0D01E96h
?PlotStart		:= 0D01E9Fh
?nMax			:= 0D01EA8h
?u0			:= 0D01EB1h
?v0			:= 0D01EBAh
?nMin			:= 0D01EC3h
?u02			:= 0D01ECCh
?v02			:= 0D01ED5h
?w0			:= 0D01EDEh
?PlotStep		:= 0D01EE7h
?XresO			:= 0D01EF0h
?w02			:= 0D01EF9h
?un1			:= 0D01F02h
?un2			:= 0D01F0Bh
?vn1			:= 0D01F14h
?vn2			:= 0D01F1Dh
?wn1			:= 0D01F26h
?wn2			:= 0D01F2Fh
?fin_N			:= 0D01F38h
?fin_I			:= 0D01F41h
?fin_PV			:= 0D01F4Ah
?fin_PMT			:= 0D01F53h
?fin_FV			:= 0D01F5Ch
?fin_PY			:= 0D01F65h
?fin_CY			:= 0D01F6Eh
?cal_N			:= 0D01F77h
?cal_I			:= 0D01F80h
?cal_PV			:= 0D01F89h
?cal_PMT			:= 0D01F92h
?cal_FV			:= 0D01F9Bh
?cal_PY			:= 0D01FA4h
?DeltaX			:= 0D01FAEh
?DeltaY			:= 0D01FB7h
?TraceStep		:= 0D0203Dh

?TblStart		:= 0D02267h
?DeltaTbl		:= 0D02270h
?Plot1MarkType		:= 0D0227Eh
?Plot1List1		:= 0D0227Fh
?Plot1List2		:= 0D02284h
?Plot1FreqList		:= 0D02289h
?Plot1XYOnOff		:= 0D0228Eh
?Plot1Color		:= 0D0228Fh

?Plot2MarkType		:= 0D02290h
?Plot2List1		:= 0D02291h
?Plot2List2		:= 0D02296h
?Plot2FreqList		:= 0D0229Bh
?Plot2XYOnOff		:= 0D022A0h
?Plot2Color		:= 0D022A1h

?Plot3MarkType		:= 0D022A2h
?Plot3List1		:= 0D022A3h
?Plot3List2		:= 0D022A8h
?Plot3FreqList		:= 0D022ADh
?Plot3XYOnOff		:= 0D022B2h
?Plot3Color		:= 0D022B3h

?ES			:= 0D022BAh

?seed1			:= 0D022FCh
?seed2			:= 0D02305h
?basic_prog		:= 0D0230Eh
?begPC			:= 0D02317h
?curPC			:= 0D0231Ah
?endPC			:= 0D0231Dh
?numArguments		:= 0D02320h

?cmdShadow		:= 0D0232Dh
?cmdShadCur		:= 0D02431h
?cmdShadAlph		:= 0D02433h
?cmdShadIns		:= 0D02435h
?cmdCursor		:= 0D02434h
?editTop			:= 0D02437h
?editCursor		:= 0D0243Ah
?editTail		:= 0D0243Dh
?editBtm			:= 0D02440h

?currListHighlight	:= 0D0244Bh ; word, this is offset into list for currently-highlighted element in list editor
?editSym			:= 0D0244Eh ; pointer to vat of variable being edited
?editDat			:= 0D02451h ; pointer to data of variable being edited

?currListPageOffset	:= 0D02457h
?currList		:= 0D02458h
?listName1		:= 0D02459h
?listName2		:= 0D0245Eh
?listName3		:= 0D02463h
?listName4		:= 0D02468h
?listName5		:= 0D0246Dh
?listName6		:= 0D02472h
?listName7		:= 0D02477h
?listName8		:= 0D0247Ch
?listName9		:= 0D02481h
?listName10		:= 0D02486h
?listName11		:= 0D0248Bh
?listName12		:= 0D02490h
?listName13		:= 0D02495h
?listName14		:= 0D0249Ah
?listName15		:= 0D0249Fh
?listName16		:= 0D024A4h
?listName17		:= 0D024A9h
?listName18		:= 0D024AEh
?listName19		:= 0D024B3h
?listName20		:= 0D024B8h
?currGrphStyle		:= 0D024BEh
?y1LineType		:= 0D024BFh
?y2LineType		:= 0D024C0h
?y3LineType		:= 0D024C1h
?y4LineType		:= 0D024C2h
?y5LineType		:= 0D024C3h
?y6LineType		:= 0D024C4h
?y7LineType		:= 0D024C5h
?y8LineType		:= 0D024C6h
?y9LineType		:= 0D024C7h
?y0LineType		:= 0D024C8h
?para1LineType		:= 0D024C9h
?para2LineType		:= 0D024CAh
?para3LineType		:= 0D024CBh
?para4LineType		:= 0D024CCh
?para5LineType		:= 0D024CDh
?para6LineType		:= 0D024CEh
?polar1LineType		:= 0D024CFh
?polar2LineType		:= 0D024D0h
?polar3LineType		:= 0D024D1h
?polar4LineType		:= 0D024D2h
?polar5LineType		:= 0D024D3h
?polar6LineType		:= 0D024D4h
?secULineType		:= 0D024D5h
?secVLineType		:= 0D024D6h
?secWLineType		:= 0D024D7h
?y1LineColor		:= 0D024D8h
?y2LineColor		:= 0D024D9h
?y3LineColor		:= 0D024DAh
?y4LineColor		:= 0D024DBh
?y5LineColor		:= 0D024DCh
?y6LineColor		:= 0D024DDh
?y7LineColor		:= 0D024DEh
?y8LineColor		:= 0D024DFh
?y9LineColor		:= 0D024E0h
?y0LineColor		:= 0D024E1h
?para1LineColor		:= 0D024E2h
?para2LineColor		:= 0D024E3h
?para3LineColor		:= 0D024E4h
?para4LineColor		:= 0D024E5h
?para5LineColor		:= 0D024E6h
?para6LineColor		:= 0D024E7h
?polar1LineColor		:= 0D024E8h
?polar2LineColor		:= 0D024E9h
?polar3LineColor		:= 0D024EAh
?polar4LineColor		:= 0D024EBh
?polar5LineColor		:= 0D024ECh
?polar6LineColor		:= 0D024EDh
?secULineColor		:= 0D024EEh
?secVLineColor		:= 0D024EFh
?secWLineColor		:= 0D024F0h

?winTop			:= 0D02504h
?winBtm			:= 0D02505h
?winLeftEdge		:= 0D02506h
?winLeft			:= 0D02507h
?winAbove		:= 0D02509h
?winRow			:= 0D0250Bh
?winCol			:= 0D0250Dh
?fmtDigits		:= 0D0250Fh
?fmtString		:= 0D02510h
?fmtLeft			:= 0D02561h
?fmtIndex		:= 0D02564h
?fmtMatSym		:= 0D02567h
?fmtMatMem		:= 0D0256Ah

?tSymPtr1		:= 0D0257Bh
?tSymPtr2		:= 0D0257Eh
?chkDelPtr3		:= 0D02581h
?chkDelPtr4		:= 0D02584h

?tempMem			:= 0D02587h
?FPSbase			:= 0D0258Ah
?FPS			:= 0D0258Dh
?OPBase			:= 0D02590h
?OPS			:= 0D02593h
?pTempCnt		:= 0D02596h
?cleanTmp		:= 0D02598h
?pTemp			:= 0D0259Ah
?progPtr			:= 0D0259Dh
?newDataPtr		:= 0D025A0h
?pagedGetPtr		:= 0D025A3h ; 3 byte scrap (unstable)
?pagedPutPtr		:= 0D025A6h

?appErr1			:= 0D025A9h ; use with _ErrCustom1
?appErr2			:= 0D025B6h ; use with _ErrCustom2

?arcPtr			:= 0D025C8h
?appRawKeyHandle		:= 0D025CBh
?customHeight		:= 0D025CEh
?localLanguage		:= 0D025CFh
?hookExecTemp		:= 0D025D2h
?cursorHookPtr		:= 0D025D5h
?libraryHookPtr		:= 0D025D8h
?rawKeyHookPtr		:= 0D025DBh
?getKeyHookPtr		:= 0D025DEh
?homescreenHookPtr	:= 0D025E1h
?windowHookPtr		:= 0D025E4h
?graphHookPtr		:= 0D025E7h
?yEqualsHookPtr		:= 0D025EAh
?fontHookPtr		:= 0D025EDh
?regraphHookPtr		:= 0D025F0h
?graphicsHookPtr		:= 0D025F3h
?traceHookPtr		:= 0D025F6h
?parserHookPtr		:= 0D025F9h
?appChangeHookPtr	:= 0D025FCh
?catalog1HookPtr		:= 0D025FFh
?helpHookPtr		:= 0D02602h
?cxRedispHookPtr		:= 0D02605h
?menuHookPtr		:= 0D02608h
?catalog2HookPtr		:= 0D0260Bh
?tokenHookPtr		:= 0D0260Eh
?localizeHookPtr		:= 0D02611h
?silentLinkHookPtr	:= 0D02614h
?USBActivityHookPtr	:= 0D0261Ah

?tempFreeArc		:= 0D02655h ; set after _ArcChk call

?textFGcolor		:= 0D02688h
?textBGcolor		:= 0D0268Ah

?drawBGColor		:= 0D026AAh
?drawFGColor		:= 0D026ACh
?drawColorCode		:= 0D026AEh

?keyToStrRam		:= 0D026EAh

?sEditMonSp		:= 0D02706h
?bpSave			:= 0D02709h

?batteryStatus		:= 0D02A86h

?graphBGColor		:= 0D02A98h

?errorLineY		:= 0D02A1Bh
?errorLineX		:= 0D02A23h

?fillRectColor		:= 0D02AC0h
?statusBarBGColor	:= 0D02ACCh

?scrapMem		:= 0D02AD7h ; 3 byte scrap (unstable)

?TempOP2ToOP6		:= 0D02B39h ; 55 bytes where OP2 to OP6 are temporary saved

?gCurYLoc		:= 0D02FD6h ; current y pixel location for C functions

;safeRAM Locations
;---------------------------------------------
;appData		equ 0D00429h ; 256 bytes
;textShadow		equ 0D006C0h ; 260 bytes	; Call _ClrTxtShdw to put spaces in here
;cmdShadow		equ 0D0232Dh ; 260 bytes
?pixelShadow		:= 0D031F6h ; 8400 bytes
?pixelShadow2		:= 0D052C6h ; 8400 bytes
?cmdPixelShadow		:= 0D07396h ; 8400 bytes
?plotSScreen		:= 0D09466h ; 21945 bytes	; Set GraphDraw Flag to redraw graph if used
?saveSScreen		:= 0D0EA1Fh ; 21945 bytes	; Set GraphDraw Flag to redraw graph if used
?cursorImage		:= 0E30800h ; 1020 bytes

;semiSafeRAM Locations
;---------------------------------------------
?usbArea			:= 0D13FD8h ; 14306 bytes used for usb, probably need to disable timer3/usb interrupts to use
?usbHandleKeys		:= 0D14091h ; zero this byte while using usbArea to keep GetCSC from affecting other parts of usbArea
?usbInited		:= 0D177B7h ; zero this byte while using usbArea and to reset the usb stack when interrupts are re-enabled
?heapBot			:= 0D1887Ch ; 1024 bytes used for flash ram routines, rest used rarely
?ramCodeTop		:= 0D18C7Ch
?heapTop			:= 0D1987Ch
?stackBot		:= 0D1987Eh
?stackTop		:= 0D1A87Eh

;RAM Equates Continued
;---------------------------------------------
?userMem			:= 0D1A881h
?symTable		:= 0D3FFFFh
?vRam			:= 0D40000h
?vRamEnd			:= 0D65800h

;Ports
;--------------------------------
?pCpuSpeed		:= 0001h
?pHardwareId		:= 0003h

;SHA256 Ports
;--------------------------------
?pShaRange		:= 02000h
?mpShaRange		:= 0E10000h

?shaCtrl			:= 00h ; 1 byte
?pShaCtrl		:= pShaRange + shaCtrl
?mpShaCtrl		:= mpShaRange + shaCtrl

?shaData			:= 10h ; 40h bytes
?pShaData		:= pShaRange + shaData
?mpShaData		:= mpShaRange + shaData

?shaState		:= 60h ; 20h bytes
?pShaState		:= pShaRange + shaState
?mpShaState		:= mpShaRange + shaState

;USB Ports
;--------------------------------
?pUsbRange		:= 03000h
?mpUsbRange		:= 0E20000h

?usbCapLen		:= 0000h
?pUsbCapLen		:= pUsbRange + usbCapLen
?mpUsbCapLen		:= mpUsbRange + usbCapLen

?usbHciVer		:= 0002h
?pUsbHciVer		:= pUsbRange + usbHciVer
?mpUsbHciVer		:= mpUsbRange + usbHciVer

?usbHcsParams		:= 0004h
?pUsbHcsParams		:= pUsbRange + usbHcsParams
?mpUsbHcsParams		:= mpUsbRange + usbHcsParams
?bUsbNumPorts		:= 0
?bmUsbNumPorts		:= 0Fh shl bUsbNumPorts
?bUsbPortPwrCtrl		:= 4
?bmUsbPortPwrCtrl	:= 1 shl bUsbPortPwrCtrl
?bUsbPortRoutRules	:= 7
?bmUsbPortRoutRules	:= 1 shl bUsbPortRoutRules
?bUsbNumPortsPerCC	:= 8
?bmUsbNumPortsPerCC	:= 0Fh shl bUsbNumPortsPerCC
?bUsbNumCC		:= 12
?bmUsbNumCC		:= 0Fh shl bUsbNumCC
?bUsbPortIndics		:= 16
?bmUsbPortIndics		:= 1 shl bUsbPortIndics
?bUsbDebugPortNum	:= 20
?bmUsbDebugPortNum	:= 0Fh shl bUsbDebugPortNum

?usbHccParams		:= 0008h
?pUsbHccParams		:= pUsbRange + usbHccParams
?mpUsbHccParams		:= mpUsbRange + usbHccParams
?bUsb64Bit		:= 0
?bmUsb64Bit		:= 1 shl bUsb64Bit
?bUsbProgFrameList	:= 1
?bmUsbProgFrameList	:= 1 shl bUsbProgFrameList
?bUsbAsyncSchedParkCap	:= 2
?bmUsbAsyncSchedParkCap	:= 1 shl bUsbAsyncSchedParkCap
?bUsbIsochSchedThresh	:= 4
?bmUsbIsochSchedThresh	:= 0Fh shl bUsbIsochSchedThresh
?bUsbEhciExtendCap	:= 8
?bmUsbEhciExtendCap	:= 0FFh shl bUsbEhciExtendCap

?usbHcspPortRout		:= 000Ch
?pUsbHcspPortRout	:= pUsbRange + usbHcspPortRout
?mpUsbHcspPortRout	:= mpUsbRange + usbHcspPortRout

?usbCmd			:= 0010h
?pUsbCmd			:= pUsbRange + usbCmd
?mpUsbCmd		:= mpUsbRange + usbCmd
?bUsbRunStop		:= 0
?bmUsbRunStop		:= 1 shl bUsbRunStop
?bUsbHcReset		:= 1
?bmUsbHcReset		:= 1 shl bUsbHcReset
?bUsbFrameListSize	:= 2
?bmUsbFrameListSize	:= 3 shl bUsbFrameListSize
?bUsbPeriodicSchedEn	:= 4
?bmUsbPeriodicSchedEn	:= 1 shl bUsbPeriodicSchedEn
?bUsbAsyncSchedEn	:= 5
?bmUsbAsyncSchedEn	:= 1 shl bUsbAsyncSchedEn
?bUsbIntAsyncAdvDrbl	:= 6
?bmUsbIntAsyncAdvDrbl	:= 1 shl bUsbIntAsyncAdvDrbl
?bUsbLightHcReset	:= 7
?bmUsbLightHcReset	:= 1 shl bUsbLightHcReset
?bUsbAsyncSchedParkCnt	:= 8
?bmUsbAsyncSchedParkCnt	:= 3 shl bUsbAsyncSchedParkCnt
?bUsbAsyncSchedParkEn	:= 11
?bmUsbAsyncSchedParkEn	:= 1 shl bUsbAsyncSchedParkEn
?bUsbIntThreshCtrl	:= 16
?bmUsbIntThreshCtrl	:= 0FFh shl bUsbIntThreshCtrl

?usbSts			:= 0014h
?pUsbSts			:= pUsbRange + usbSts
?mpUsbSts		:= mpUsbRange + usbSts
?usbIntEn		:= 0018h
?pUsbIntEn		:= pUsbRange + usbIntEn
?mpUsbIntEn		:= mpUsbRange + usbIntEn
?bUsbInt			:= 0
?bmUsbInt		:= 1 shl bUsbInt
?bUsbIntErr		:= 1
?bmUsbIntErr		:= 1 shl bUsbIntErr
?bUsbIntPortChgDetect	:= 2
?bmUsbIntPortChgDetect	:= 1 shl bUsbIntPortChgDetect
?bUsbIntFrameListOver	:= 3
?bmUsbIntFrameListOver	:= 1 shl bUsbIntFrameListOver
?bUsbIntHostSysErr	:= 4
?bmUsbIntHostSysErr	:= 1 shl bUsbIntHostSysErr
?bUsbIntAsyncAdv		:= 5
?bmUsbIntAsyncAdv	:= 1 shl bUsbIntAsyncAdv
?bUsbHcHalted		:= 12
?bmUsbHcHalted		:= 1 shl bUsbHcHalted
?bUsbReclamation		:= 13
?bmUsbReclamation	:= 1 shl bUsbReclamation
?bUsbPeriodicSchedSts	:= 14
?bmUsbPeriodicSchedSts	:= 1 shl bUsbPeriodicSchedSts
?bUsbAsyncSchedSts	:= 15
?bmUsbAsyncSchedSts	:= 1 shl bUsbAsyncSchedSts

?usbFrameIdx		:= 001Ch
?pUsbFrameIdx		:= pUsbRange + usbFrameIdx
?mpUsbFrameIdx		:= mpUsbRange + usbFrameIdx
?bUsbFrameIdx		:= 0
?bmUsbFrameIdx		:= 03FFFh shl bUsbFrameIdx

?usbCtrlDsSeg		:= 0020h
?pUsbCtrlDsSeg		:= pUsbRange + usbCtrlDsSeg
?mpUsbCtrlDsSeg		:= mpUsbRange + usbCtrlDsSeg

?usbPeriodicListBase	:= 0024h
?pUsbPeriodicListBase	:= pUsbRange + usbPeriodicListBase
?mpUsbPeriodicListBase	:= mpUsbRange + usbPeriodicListBase
?bUsbPeriodicListBase	:= 12
?bmUsbPeriodicListBase	:= 0FFFFFh shl bUsbPeriodicListBase

?usbAsyncListAddr	:= 0028h
?pUsbAsyncListAddr	:= pUsbRange + usbAsyncListAddr
?mpUsbAsyncListAddr	:= mpUsbRange + usbAsyncListAddr
?bUsbAsyncListAddr	:= 5
?bmUsbAsyncListAddr	:= 07FFFFFFh shl bUsbAsyncListAddr

?usbPortStsCtrl		:= 0030h
?pUsbPortStsCtrl		:= pUsbRange + usbPortStsCtrl
?mpUsbPortStsCtrl	:= mpUsbRange + usbPortStsCtrl
?bUsbCurConnSts		:= 0
?bmUsbCurConnSts		:= 1 shl bUsbCurConnSts
?bUsbConnStsChg		:= 1
?bmUsbConnStsChg		:= 1 shl bUsbConnStsChg
?bUsbPortEn		:= 2
?bmUsbPortEn		:= 1 shl bUsbPortEn
?bUsbPortEnChg		:= 3
?bmUsbPortEnChg		:= 1 shl bUsbPortEnChg
?bUsbOvercurrActive	:= 4
?bmUsbOvercurrActive	:= 1 shl bUsbOvercurrActive
?bUsbOvercurrChg		:= 5
?bmUsbOvercurrChg	:= 1 shl bUsbOvercurrChg
?bUsbForcePortResume	:= 6
?bmUsbForcePortResume	:= 1 shl bUsbForcePortResume
?bUsbPortSuspended	:= 7
?bmUsbPortSuspended	:= 1 shl bUsbPortSuspended
?bUsbPortReset		:= 8
?bmUsbPortReset		:= 1 shl bUsbPortReset
?bUsbLineSts		:= 10
?bmUsbLineSts		:= 3 shl bUsbLineSts
?bUsbPortPwr		:= 12
?bmUsbPortPwr		:= 1 shl bUsbPortPwr
?bUsbPortOwner		:= 13
?bmUsbPortOwner		:= 1 shl bUsbPortOwner
?bUsbPortIndicCtrl	:= 14
?bmUsbPortIndicCtrl	:= 3 shl bUsbPortIndicCtrl
?bUsbPortTestCtrl	:= 16
?bmUsbPortTestCtrl	:= 0Fh shl bUsbPortTestCtrl
?bUsbWakeConnEn		:= 20
?bmUsbWakeConnEn		:= 1 shl bUsbWakeConnEn
?bUsbWakeDiscEn		:= 21
?bmUsbWakeDiscEn		:= 1 shl bUsbWakeDiscEn
?bUsbWakeOvercurrEn	:= 22
?bmUsbWakeOvercurrEn	:= 1 shl bUsbWakeOvercurrEn

?usbMisc			:= 0040h
?pUsbMisc		:= pUsbRange + usbMisc
?mpUsbMisc		:= mpUsbRange + usbMisc
?bUsbAsyncSchedSleepTmr	:= 0
?bmUsbAsyncSchedSleepTmr	:= 3 shl bUsbAsyncSchedSleepTmr
?bUsbEof1Timing		:= 2
?bmUsbEof1Timing		:= 3 shl bUsbEof1Timing
?bUsbEof2Timing		:= 4
?bmUsbEof2Timing		:= 3 shl bUsbEof2Timing
?bUsbHostSuspend		:= 6
?bmUsbHostSuspend	:= 1 shl bUsbHostSuspend

?usbOtgCsr		:= 0080h
?pUsbOtgCsr		:= pUsbRange + usbOtgCsr
?mpUsbOtgCsr		:= mpUsbRange + usbOtgCsr
?bUsbBBusReq		:= 0
?bmUsbBBusReq		:= 1 shl bUsbBBusReq
?bUsbBHnp		:= 1
?bmUsbBHnp		:= 1 shl bUsbBHnp
?bUsbBVbusDisc		:= 2
?bmUsbBVbusDisc		:= 1 shl bUsbBVbusDisc
?bUsbABusReq		:= 4
?bmUsbABusReq		:= 1 shl bUsbABusReq
?bUsbABusDrop		:= 5
?bmUsbABusDrop		:= 1 shl bUsbABusDrop
?bUsbAHnp		:= 6
?bmUsbAHnp		:= 1 shl bUsbAHnp
?bUsbASrpEn		:= 7
?bmUsbASrpEn		:= 1 shl bUsbASrpEn
?bUsbASrpMode		:= 8
?usbASrpModeVbus		:= 0 shl bUsbASrpMode
?usbASrpModeData		:= 1 shl bUsbASrpMode
?bmUsbASrpMode		:= 1 shl bUsbASrpMode
?bUsbIdFilt		:= 9
?usbIdFiltShort		:= 0 shl bUsbIdFilt
?usbIdFiltLong		:= 1 shl bUsbIdFilt
?bmUsbIdFilt		:= 1 shl bUsbIdFilt
?bUsbVbusFilt		:= 10
?usbVbusFiltShort	:= 0 shl bUsbVbusFilt
?usbVbusFiltLong		:= 1 shl bUsbVbusFilt
?bmUsbVbusFilt		:= 1 shl bUsbVbusFilt
?bUsbHdiscFilt		:= 11
?usbHdiscFiltShort	:= 0 shl bUsbHdiscFilt
?usbHdiscFiltLong	:= 1 shl bUsbHdiscFilt
?bmUsbHdiscFilt		:= 1 shl bUsbHdiscFilt
?bUsbBSessEnd		:= 16
?bmUsbBSessEnd		:= 1 shl bUsbBSessEnd
?bUsbBSessVld		:= 17
?bmUsbBSessVld		:= 1 shl bUsbBSessVld
?bUsbASessVld		:= 18
?bmUsbASessVld		:= 1 shl bUsbASessVld
?bUsbAVbusVld		:= 19
?bmUsbAVbusVld		:= 1 shl bUsbAVbusVld
?bUsbRole		:= 20
?usbRoleHost		:= 0 shl bUsbRole
?usbRoleDev		:= 1 shl bUsbRole
?bmUsbRole		:= 1 shl bUsbRole
?bUsbId			:= 21
?usbIdA			:= 0 shl bUsbId
?usbIdB			:= 1 shl bUsbId
?bmUsbId			:= 1 shl bUsbId
?bUsbSpd			:= 22
?usbSpdFull		:= 0 shl bUsbSpd
?usbSpdLow		:= 1 shl bUsbSpd
?usbSpdHigh		:= 2 shl bUsbSpd
?bmUsbSpd		:= 3 shl bUsbSpd

?usbOtgIsr		:= 0084h
?pUsbOtgIsr		:= pUsbRange + usbOtgIsr
?mpUsbOtgIsr		:= mpUsbRange + usbOtgIsr
?usbOtgIer		:= 0088h
?pUsbOtgIer		:= pUsbRange + usbOtgIer
?mpUsbOtgIer		:= mpUsbRange + usbOtgIer
?bUsbIntBSrpComplete	:= 0
?bmUsbIntBSrpComplete	:= 1 shl bUsbIntBSrpComplete
?bUsbIntASrpDetect	:= 4
?bmUsbIntASrpDetect	:= 1 shl bUsbIntASrpDetect
?bUsbIntAVbusErr		:= 5
?bmUsbIntAVbusErr	:= 1 shl bUsbIntAVbusErr
?bUsbIntBSessEnd		:= 6
?bmUsbIntBSessEnd	:= 1 shl bUsbIntBSessEnd
?bUsbIntRoleChg		:= 8
?bmUsbIntRoleChg		:= 1 shl bUsbIntRoleChg
?bUsbIntIdChg		:= 9
?bmUsbIntIdChg		:= 1 shl bUsbIntIdChg
?bUsbIntOvercurr		:= 10
?bmUsbIntOvercurr	:= 1 shl bUsbIntOvercurr
?bUsbIntBPlugRemoved	:= 11
?bmUsbIntBPlugRemoved	:= 1 shl bUsbIntBPlugRemoved
?bUsbIntAPlugRemoved	:= 12
?bmUsbIntAPlugRemoved	:= 1 shl bUsbIntAPlugRemoved

?usbIsr			:= 00C0h
?pUsbIsr			:= pUsbRange + usbIsr
?mpUsbIsr		:= mpUsbRange + usbIsr
?usbImr			:= 00C4h
?pUsbImr			:= pUsbRange + usbImr
?mpUsbImr		:= mpUsbRange + usbImr
?bUsbIntDev		:= 0
?bmUsbIntDev		:= 1 shl bUsbIntDev
?bUsbIntOtg		:= 1
?bmUsbIntOtg		:= 1 shl bUsbIntOtg
?bUsbIntHost		:= 2
?bmUsbIntHost		:= 1 shl bUsbIntHost
?bUsbIntLevel		:= 3
?usbIntLevelLow		:= 0 shl bUsbIntLevel
?usbIntLevelHigh		:= 1 shl bUsbIntLevel
?bmUsbIntLevel		:= 1 shl bUsbIntLevel

?usbDevCtrl		:= 0100h
?pUsbDevCtrl		:= pUsbRange + usbDevCtrl
?mpUsbDevCtrl		:= mpUsbRange + usbDevCtrl
?bUsbRemoteWake		:= 0
?bmUsbRemoteWake		:= 1 shl bUsbRemoteWake
?bUsbHalfSpd		:= 1
?bmUsbHalfSpd		:= 1 shl bUsbHalfSpd
?bUsbGirqEn		:= 2
?bmUsbGirqEn		:= 1 shl bUsbGirqEn
?bUsbDevSuspend		:= 3
?bmUsbDevSuspend		:= 1 shl bUsbDevSuspend
?bUsbDevReset		:= 4
?bmUsbDevReset		:= 1 shl bUsbDevReset
?bUsbDevEn		:= 5
?bmUsbDevEn		:= 1 shl bUsbDevEn
?bUsbDevSpd		:= 6
?bmUsbDevSpd		:= 1 shl bUsbDevSpd
?bUsbDevForceFullSpd	:= 9
?bmUsbDevForceFullSpd	:= 1 shl bUsbDevForceFullSpd

?usbDevAddr		:= 0104h
?pUsbDevAddr		:= pUsbRange + usbDevAddr
?mpUsbDevAddr		:= mpUsbRange + usbDevAddr
?bUsbDevAddr		:= 0
?bmUsbDevAddr		:= 07Fh shl bUsbDevAddr
?bUsbDevConf		:= 7
?bmUsbDevConf		:= 1 shl bUsbDevConf

?usbDevTest		:= 0108h
?pUsbDevTest		:= pUsbRange + usbDevTest
?mpUsbDevTest		:= mpUsbRange + usbDevTest
?bUsbTstClrFifo		:= 0
?bmUsbTstClrFifo		:= 1 shl bUsbTstClrFifo
?bUsbTstCxLp		:= 1
?bmUsbTstCxLp		:= 1 shl bUsbTstCxLp
?bUsbTstClrEa		:= 2
?bmUsbTstClrEa		:= 1 shl bUsbTstClrEa
?bUsbTstNoCrc		:= 3
?bmUsbTstNoCrc		:= 1 shl bUsbTstNoCrc
?bUsbTstNoTs		:= 4
?bmUsbTstNoTs		:= 1 shl bUsbTstNoTs
?bUsbTstMode		:= 5
?bmUsbTstMode		:= 1 shl bUsbTstMode
?bUsbNoSof		:= 6
?bmUsbNoSof		:= 1 shl bUsbNoSof

?usbSofFrNum		:= 010Ch
?pUsbSofFrNum		:= pUsbRange + usbSofFrNum
?mpUsbSofFrNum		:= mpUsbRange + usbSofFrNum
?bUsbSofFrNum		:= 0
?bmUsbSofFrNum		:= 07FFh shl bUsbSofFrNum
?bUsbSofUFrNum		:= 11
?bmUsbSofUFrNum		:= 7 shl bUsbSofUFrNum

?usbSofMtr		:= 0110h
?pUsbSofMtr		:= pUsbRange + usbSofMtr
?mpUsbSofMtr		:= mpUsbRange + usbSofMtr
?bUsbSofMtrTmr		:= 0
?bmUsbSofMtrTmr		:= 0FFFFh shl bUsbSofMtrTmr

?usbPhyTmsr		:= 0114h
?pUsbPhyTmsr		:= pUsbRange + usbPhyTmsr
?mpUsbPhyTmsr		:= mpUsbRange + usbPhyTmsr
?bUsbUnplug		:= 0
?bmUsbUnplug		:= 1 shl bUsbUnplug
?bUsbTstJState		:= 1
?bmUsbTstJState		:= 1 shl bUsbTstJState
?bUsbTstKState		:= 2
?bmUsbTstKState		:= 1 shl bUsbTstKState
?bUsbTstSe0Nak		:= 3
?bmUsbTstSe0Nak		:= 1 shl bUsbTstSe0Nak
?bUsbTstPkt		:= 4
?bmUsbTstPkt		:= 1 shl bUsbTstPkt

?usbCxsr			:= 011Ch
?pUsbCxsr		:= pUsbRange + usbCxsr
?mpUsbCxsr		:= mpUsbRange + usbCxsr

?usbCxFifo		:= 0120h
?pUsbCxFifo		:= pUsbRange + usbCxFifo
?mpUsbCxFifo		:= mpUsbRange + usbCxFifo
?bCxFifoFin		:= 0
?bmCxFifoFin		:= 1 shl bCxFifoFin
?bTstPktFin		:= 1
?bmTstPktFin		:= 1 shl bTstPktFin
?bCxFifoStall		:= 2
?bmCxFifoStall		:= 1 shl bCxFifoStall
?bCxFifoClr		:= 3
?bmCxFifoClr		:= 1 shl bCxFifoClr
?bCxFifoFull		:= 4
?bmCxFifoFull		:= 1 shl bCxFifoFull
?bCxFifoEmpty		:= 5
?bmCxFifoEmpty		:= 1 shl bCxFifoEmpty
?bFifo0Empty		:= 8
?bmFifo0Empty		:= 1 shl bFifo0Empty
?bFifo1Empty		:= 9
?bmFifo1Empty		:= 1 shl bFifo1Empty
?bFifo2Empty		:= 10
?bmFifo2Empty		:= 1 shl bFifo2Empty
?bFifo3Empty		:= 11
?bmFifo3Empty		:= 1 shl bFifo3Empty
?bFifoEmpty		:= 8
?bmFifoEmpty		:= 0Fh shl bFifoEmpty

?usbCxFifoBytes		:= 0123h
?pUsbCxFifoBytes		:= pUsbRange + usbCxFifoBytes
?mpUsbCxFifoBytes	:= mpUsbRange + usbCxFifoBytes
?bUsbCxFifoBytes		:= 0
?bmUsbCxFifoBytes	:= 07Fh

?usbIdle			:= 0124h
?pUsbIdle		:= pUsbRange + usbIdle
?mpUsbIdle		:= mpUsbRange + usbIdle
?bUsbIdleMs		:= 0
?bmUsbIdleMs		:= 7 shl bUsbIdleMs

?usbGimr			:= 0130h
?pUsbGimr		:= pUsbRange + usbGimr
?mpUsbGimr		:= mpUsbRange + usbGimr
?usbGisr			:= 0140h
?pUsbGisr		:= pUsbRange + usbGisr
?mpUsbGisr		:= mpUsbRange + usbGisr
?bUsbDevIntCx		:= 0
?bmUsbDevIntCx		:= 1 shl bUsbDevIntCx
?bUsbDevIntFifo		:= 1
?bmUsbDevIntFifo		:= 1 shl bUsbDevIntFifo
?bUsbDevIntDev		:= 2
?bmUsbDevIntDev		:= 1 shl bUsbDevIntDev

?usbCxImr		:= 0134h
?pUsbCxImr		:= pUsbRange + usbCxImr
?mpUsbCxImr		:= mpUsbRange + usbCxImr
?usbCxIsr		:= 0144h
?pUsbCxIsr		:= pUsbRange + usbCxIsr
?mpUsbCxIsr		:= mpUsbRange + usbCxIsr
?bUsbIntCxSetup		:= 0
?bmUsbIntCxSetup		:= 1 shl bUsbIntCxSetup
?bUsbIntCxIn		:= 1
?bmUsbIntCxIn		:= 1 shl bUsbIntCxIn
?bUsbIntCxOut		:= 2
?bmUsbIntCxOut		:= 1 shl bUsbIntCxOut
?bUsbIntCxEnd		:= 3
?bmUsbIntCxEnd		:= 1 shl bUsbIntCxEnd
?bUsbIntCxErr		:= 4
?bmUsbIntCxErr		:= 1 shl bUsbIntCxErr
?bUsbIntCxAbort		:= 5
?bmUsbIntCxAbort		:= 1 shl bUsbIntCxAbort
?bUsbIntCx		:= 0
?bmUsbIntCx		:= 01Fh shl bUsbIntCx

?usbFifoRxImr		:= 0138h
?pUsbFifoRxImr		:= pUsbRange + usbFifoRxImr
?mpUsbFifoRxImr		:= mpUsbRange + usbFifoRxImr
?usbFifoRxIsr		:= 0148h
?pUsbFifoRxIsr		:= pUsbRange + usbFifoRxIsr
?mpUsbFifoRxIsr		:= mpUsbRange + usbFifoRxIsr
?bUsbIntFifo0Out		:= 0
?bmUsbIntFifo0Out	:= 1 shl bUsbIntFifo0Out
?bUsbIntFifo0Spk		:= 1
?bmUsbIntFifo0Spk	:= 1 shl bUsbIntFifo0Spk
?bUsbIntFifo1Out		:= 2
?bmUsbIntFifo1Out	:= 1 shl bUsbIntFifo1Out
?bUsbIntFifo1Spk		:= 3
?bmUsbIntFifo1Spk	:= 1 shl bUsbIntFifo1Spk
?bUsbIntFifo2Out		:= 4
?bmUsbIntFifo2Out	:= 1 shl bUsbIntFifo2Out
?bUsbIntFifo2Spk		:= 5
?bmUsbIntFifo2Spk	:= 1 shl bUsbIntFifo2Spk
?bUsbIntFifo3Out		:= 6
?bmUsbIntFifo3Out	:= 1 shl bUsbIntFifo3Out
?bUsbIntFifo3Spk		:= 7
?bmUsbIntFifo3Spk	:= 1 shl bUsbIntFifo3Spk
?bUsbFifoRxInts		:= 0
?bmUsbFifoRxInts		:= 0FFh shl bUsbFifoRxInts

?usbFifoTxImr		:= 013Ah
?pUsbFifoTxImr		:= pUsbRange + usbFifoTxImr
?mpUsbFifoTxImr		:= mpUsbRange + usbFifoTxImr
?usbFifoTxIsr		:= 014Ah
?pUsbFifoTxIsr		:= pUsbRange + usbFifoTxIsr
?mpUsbFifoTxIsr		:= mpUsbRange + usbFifoTxIsr
?bUsbIntFifo0In		:= 0
?bmUsbIntFifo0In		:= 1 shl bUsbIntFifo0In
?bUsbIntFifo1In		:= 1
?bmUsbIntFifo1In		:= 1 shl bUsbIntFifo1In
?bUsbIntFifo2In		:= 2
?bmUsbIntFifo2In		:= 1 shl bUsbIntFifo2In
?bUsbIntFifo3In		:= 3
?bmUsbIntFifo3In		:= 1 shl bUsbIntFifo3In
?bUsbFifoTxInts		:= 0
?bmUsbFifoTxInts		:= 0Fh shl bUsbFifoTxInts

?usbDevImr		:= 013Ch
?pUsbDevImr		:= pUsbRange + usbDevImr
?mpUsbDevImr		:= mpUsbRange + usbDevImr
?usbDevIsr		:= 014Ch
?pUsbDevIsr		:= pUsbRange + usbDevIsr
?mpUsbDevIsr		:= mpUsbRange + usbDevIsr
?bUsbIntDevReset		:= 0
?bmUsbIntDevReset	:= 1 shl bUsbIntDevReset
?bUsbIntDevSuspend	:= 1
?bmUsbIntDevSuspend	:= 1 shl bUsbIntDevSuspend
?bUsbIntDevResume	:= 2
?bmUsbIntDevResume	:= 1 shl bUsbIntDevResume
?bUsbIntDevIsocErr	:= 3
?bmUsbIntDevIsocErr	:= 1 shl bUsbIntDevIsocErr
?bUsbIntDevIsocAbt	:= 4
?bmUsbIntDevIsocAbt	:= 1 shl bUsbIntDevIsocAbt
?bUsbIntDevZlpTx		:= 5
?bmUsbIntDevZlpTx	:= 1 shl bUsbIntDevZlpTx
?bUsbIntDevZlpRx		:= 6
?bmUsbIntDevZlpRx	:= 1 shl bUsbIntDevZlpRx
?bUsbIntDevDmaFin	:= 7
?bmUsbIntDevDmaFin	:= 1 shl bUsbIntDevDmaFin
?bUsbIntDevDmaErr	:= 8
?bmUsbIntDevDmaErr	:= 1 shl bUsbIntDevDmaErr
?bUsbIntDevIdle		:= 9
?bmUsbIntDevIdle		:= 1 shl bUsbIntDevIdle
?bUsbIntDevWakeup	:= 10
?bmUsbIntDevWakeup	:= 1 shl bUsbIntDevWakeup
?bUsbDevInts		:= 0
?bmUsbDevInts		:= 07FFh shl bUsbDevInts

?usbRxZlp		:= 0150h
?pUsbRxZlp		:= pUsbRange + usbRxZlp
?mpUsbRxZlp		:= mpUsbRange + usbRxZlp
?usbTxZlp		:= 0154h
?pUsbTxZlp		:= pUsbRange + usbTxZlp
?mpUsbTxZlp		:= mpUsbRange + usbTxZlp
?bUsbEp1Zlp		:= 0
?bmUsbEp1Zlp		:= 1 shl bUsbEp1Zlp
?bUsbEp2Zlp		:= 1
?bmUsbEp2Zlp		:= 1 shl bUsbEp2Zlp
?bUsbEp3Zlp		:= 2
?bmUsbEp3Zlp		:= 1 shl bUsbEp3Zlp
?bUsbEp4Zlp		:= 3
?bmUsbEp4Zlp		:= 1 shl bUsbEp4Zlp
?bUsbEp5Zlp		:= 4
?bmUsbEp5Zlp		:= 1 shl bUsbEp5Zlp
?bUsbEp6Zlp		:= 5
?bmUsbEp6Zlp		:= 1 shl bUsbEp6Zlp
?bUsbEp7Zlp		:= 6
?bmUsbEp7Zlp		:= 1 shl bUsbEp7Zlp
?bUsbEp8Zlp		:= 7
?bmUsbEp8Zlp		:= 1 shl bUsbEp8Zlp
?bUsbZlp			:= 0
?bmUsbZlp		:= 0FFh shl bUsbZlp

?usbIsoEasr		:= 0158h
?pUsbIsoEasr		:= pUsbRange + usbIsoEasr
?mpUsbIsoEasr		:= mpUsbRange + usbIsoEasr
?bUsbEp1IsocAbort	:= 0
?bmUsbEp1IsocAbort	:= 1 shl bUsbEp1IsocAbort
?bUsbEp2IsocAbort	:= 1
?bmUsbEp2IsocAbort	:= 1 shl bUsbEp2IsocAbort
?bUsbEp3IsocAbort	:= 2
?bmUsbEp3IsocAbort	:= 1 shl bUsbEp3IsocAbort
?bUsbEp4IsocAbort	:= 3
?bmUsbEp4IsocAbort	:= 1 shl bUsbEp4IsocAbort
?bUsbEp5IsocAbort	:= 4
?bmUsbEp5IsocAbort	:= 1 shl bUsbEp5IsocAbort
?bUsbEp6IsocAbort	:= 5
?bmUsbEp6IsocAbort	:= 1 shl bUsbEp6IsocAbort
?bUsbEp7IsocAbort	:= 6
?bmUsbEp7IsocAbort	:= 1 shl bUsbEp7IsocAbort
?bUsbEp8IsocAbort	:= 7
?bmUsbEp8IsocAbort	:= 1 shl bUsbEp8IsocAbort
?bUsbEp1IsocErr		:= 16
?bmUsbEp1IsocErr		:= 1 shl bUsbEp1IsocErr
?bUsbEp2IsocErr		:= 17
?bmUsbEp2IsocErr		:= 1 shl bUsbEp2IsocErr
?bUsbEp3IsocErr		:= 18
?bmUsbEp3IsocErr		:= 1 shl bUsbEp3IsocErr
?bUsbEp4IsocErr		:= 19
?bmUsbEp4IsocErr		:= 1 shl bUsbEp4IsocErr
?bUsbEp5IsocErr		:= 20
?bmUsbEp5IsocErr		:= 1 shl bUsbEp5IsocErr
?bUsbEp6IsocErr		:= 21
?bmUsbEp6IsocErr		:= 1 shl bUsbEp6IsocErr
?bUsbEp7IsocErr		:= 22
?bmUsbEp7IsocErr		:= 1 shl bUsbEp7IsocErr
?bUsbEp8IsocErr		:= 23
?bmUsbEp8IsocErr		:= 1 shl bUsbEp8IsocErr

?usbInEp1		:= 0160h
?pUsbInEp1		:= pUsbRange + usbInEp1
?mpUsbInEp1		:= mpUsbRange + usbInEp1
?usbInEp2		:= 0164h
?pUsbInEp2		:= pUsbRange + usbInEp2
?mpUsbInEp2		:= mpUsbRange + usbInEp2
?usbInEp3		:= 0168h
?pUsbInEp3		:= pUsbRange + usbInEp3
?mpUsbInEp3		:= mpUsbRange + usbInEp3
?usbInEp4		:= 016Ch
?pUsbInEp4		:= pUsbRange + usbInEp4
?mpUsbInEp4		:= mpUsbRange + usbInEp4
?usbInEp5		:= 0170h
?pUsbInEp5		:= pUsbRange + usbInEp5
?mpUsbInEp5		:= mpUsbRange + usbInEp5
?usbInEp6		:= 0174h
?pUsbInEp6		:= pUsbRange + usbInEp6
?mpUsbInEp6		:= mpUsbRange + usbInEp6
?usbInEp7		:= 0178h
?pUsbInEp7		:= pUsbRange + usbInEp7
?mpUsbInEp7		:= mpUsbRange + usbInEp7
?usbInEp8		:= 017Ch
?pUsbInEp8		:= pUsbRange + usbInEp8
?mpUsbInEp8		:= mpUsbRange + usbInEp8
?usbOutEp1		:= 0180h
?pUsbOutEp1		:= pUsbRange + usbOutEp1
?mpUsbOutEp1		:= mpUsbRange + usbOutEp1
?usbOutEp2		:= 0184h
?pUsbOutEp2		:= pUsbRange + usbOutEp2
?mpUsbOutEp2		:= mpUsbRange + usbOutEp2
?usbOutEp3		:= 0188h
?pUsbOutEp3		:= pUsbRange + usbOutEp3
?mpUsbOutEp3		:= mpUsbRange + usbOutEp3
?usbOutEp4		:= 018Ch
?pUsbOutEp4		:= pUsbRange + usbOutEp4
?mpUsbOutEp4		:= mpUsbRange + usbOutEp4
?usbOutEp5		:= 0190h
?pUsbOutEp5		:= pUsbRange + usbOutEp5
?mpUsbOutEp5		:= mpUsbRange + usbOutEp5
?usbOutEp6		:= 0194h
?pUsbOutEp6		:= pUsbRange + usbOutEp6
?mpUsbOutEp6		:= mpUsbRange + usbOutEp6
?usbOutEp7		:= 0198h
?pUsbOutEp7		:= pUsbRange + usbOutEp7
?mpUsbOutEp7		:= mpUsbRange + usbOutEp7
?usbOutEp8		:= 019Ch
?pUsbOutEp8		:= pUsbRange + usbOutEp8
?mpUsbOutEp8		:= mpUsbRange + usbOutEp8
?bUsbEpMaxPktSz		:= 0
?bmUsbEpMaxPktSz		:= 07FFh shl bUsbEpMaxPktSz
?bUsbEpStall		:= 11
?bmUsbEpStall		:= 1 shl bUsbEpStall
?bUsbEpReset		:= 12
?bmUsbEpReset		:= 1 shl bUsbEpReset
?bUsbInEpTxNum		:= 13
?bmUsbInEpTxNum		:= 3 shl bUsbInEpTxNum
?bUsbInEpSendZlp		:= 15
?bmUsbInEpSendZlp	:= 1 shl bUsbInEpSendZlp

?usbEp1Map		:= 01A0h
?pUsbEp1Map		:= pUsbRange + usbEp1Map
?mpUsbEp1Map		:= mpUsbRange + usbEp1Map
?usbEp2Map		:= 01A1h
?pUsbEp2Map		:= pUsbRange + usbEp2Map
?mpUsbEp2Map		:= mpUsbRange + usbEp2Map
?usbEp3Map		:= 01A2h
?pUsbEp3Map		:= pUsbRange + usbEp3Map
?mpUsbEp3Map		:= mpUsbRange + usbEp3Map
?usbEp4Map		:= 01A3h
?pUsbEp4Map		:= pUsbRange + usbEp4Map
?mpUsbEp4Map		:= mpUsbRange + usbEp4Map
?usbEp5Map		:= 01A4h
?pUsbEp5Map		:= pUsbRange + usbEp5Map
?mpUsbEp5Map		:= mpUsbRange + usbEp5Map
?usbEp6Map		:= 01A5h
?pUsbEp6Map		:= pUsbRange + usbEp6Map
?mpUsbEp6Map		:= mpUsbRange + usbEp6Map
?usbEp7Map		:= 01A6h
?pUsbEp7Map		:= pUsbRange + usbEp7Map
?mpUsbEp7Map		:= mpUsbRange + usbEp7Map
?usbEp8Map		:= 01A7h
?pUsbEp8Map		:= pUsbRange + usbEp8Map
?mpUsbEp8Map		:= mpUsbRange + usbEp8Map
?bUsbEpMapIn		:= 0
?bmUsbEpMapIn		:= 0Fh shl bUsbEpMapIn
?bUsbEpMapOut		:= 4
?bmUsbEpMapOut		:= 0Fh shl bUsbEpMapOut

?usbFifo0Map		:= 01A8h
?pUsbFifo0Map		:= pUsbRange + usbFifo0Map
?mpUsbFifo0Map		:= mpUsbRange + usbFifo0Map
?usbFifo1Map		:= 01A9h
?pUsbFifo1Map		:= pUsbRange + usbFifo1Map
?mpUsbFifo1Map		:= mpUsbRange + usbFifo1Map
?usbFifo2Map		:= 01AAh
?pUsbFifo2Map		:= pUsbRange + usbFifo2Map
?mpUsbFifo2Map		:= mpUsbRange + usbFifo2Map
?usbFifo3Map		:= 01ABh
?pUsbFifo3Map		:= pUsbRange + usbFifo3Map
?mpUsbFifo3Map		:= mpUsbRange + usbFifo3Map
?bUsbFifoEp		:= 0
?bmUsbFifoEp		:= 0Fh shl bUsbFifoEp
?bUsbFifoDir		:= 4
?usbFifoOut		:= 0 shl bUsbFifoDir
?usbFifoIn		:= 1 shl bUsbFifoDir
?usbFifoBi		:= 2 shl bUsbFifoDir
?bmUsbFifoDir		:= 3 shl bUsbFifoDir

?usbFifo0Cfg		:= 01ACh
?pUsbFifo0Cfg		:= pUsbRange + usbFifo0Cfg
?mpUsbFifo0Cfg		:= mpUsbRange + usbFifo0Cfg
?usbFifo1Cfg		:= 01ADh
?pUsbFifo1Cfg		:= pUsbRange + usbFifo1Cfg
?mpUsbFifo1Cfg		:= mpUsbRange + usbFifo1Cfg
?usbFifo2Cfg		:= 01AEh
?pUsbFifo2Cfg		:= pUsbRange + usbFifo2Cfg
?mpUsbFifo2Cfg		:= mpUsbRange + usbFifo2Cfg
?usbFifo3Cfg		:= 01AFh
?pUsbFifo3Cfg		:= pUsbRange + usbFifo3Cfg
?mpUsbFifo3Cfg		:= mpUsbRange + usbFifo3Cfg
?bUsbFifoType		:= 0
?usbFifoIsoc		:= 1 shl bUsbFifoType
?usbFifoBulk		:= 2 shl bUsbFifoType
?usbFifoIntr		:= 3 shl bUsbFifoType
?bmUsbFifoType		:= 3 shl bUsbFifoType
?bUsbFifoNumBlks		:= 2
?usbFifo1Blk		:= 0 shl bUsbFifoNumBlks
?usbFifo2Blks		:= 1 shl bUsbFifoNumBlks
?usbFifo3Blks		:= 2 shl bUsbFifoNumBlks
?bmUsbFifoNumBlks	:= 3 shl bUsbFifoNumBlks
?bUsbFifoBlkSz		:= 4
?usbFifoBlkSz512		:= 0 shl bUsbFifoBlkSz
?usbFifoBlkSz1024	:= 1 shl bUsbFifoBlkSz
?bmUsbFifoBlkSz		:= 1 shl bUsbFifoBlkSz
?bUsbFifoEn		:= 5
?bmUsbFifoEn		:= 1 shl bUsbFifoEn

?usbFifo0Csr		:= 01B0h
?pUsbFifo0Csr		:= pUsbRange + usbFifo0Csr
?mpUsbFifo0Csr		:= mpUsbRange + usbFifo0Csr
?usbFifo1Csr		:= 01B4h
?pUsbFifo1Csr		:= pUsbRange + usbFifo1Csr
?mpUsbFifo1Csr		:= mpUsbRange + usbFifo1Csr
?usbFifo2Csr		:= 01B8h
?pUsbFifo2Csr		:= pUsbRange + usbFifo2Csr
?mpUsbFifo2Csr		:= mpUsbRange + usbFifo2Csr
?usbFifo3Csr		:= 01BCh
?pUsbFifo3Csr		:= pUsbRange + usbFifo3Csr
?mpUsbFifo3Csr		:= mpUsbRange + usbFifo3Csr
?bUsbFifoLen		:= 0
?bmUsbFifoLen		:= 07FFh shl bUsbFifoLen
?bUsbFifoReset		:= 12
?bmUsbFifoReset		:= 1 shl bUsbFifoReset

?usbDmaFifo		:= 01C0h
?pUsbDmaFifo		:= pUsbRange + usbDmaFifo
?mpUsbDmaFifo		:= mpUsbRange + usbDmaFifo
?bUsbDmaFifo0		:= 0
?bmUsbDmaFifo0		:= 1 shl bUsbDmaFifo0
?bUsbDmaFifo1		:= 1
?bmUsbDmaFifo1		:= 1 shl bUsbDmaFifo1
?bUsbDmaFifo2		:= 2
?bmUsbDmaFifo2		:= 1 shl bUsbDmaFifo2
?bUsbDmaFifo3		:= 3
?bmUsbDmaFifo3		:= 1 shl bUsbDmaFifo3
?bUsbDmaCxFifo		:= 4
?bmUsbDmaCxFifo		:= 1 shl bUsbDmaCxFifo
?bUsbDmaFifo		:= 0
?bmUsbDmaNoFifo		:= 0 shl bUsbDmaFifo
?bmUsbDmaFifo		:= 01Fh shl bUsbDmaFifo

?usbDmaCtrl		:= 01C8h
?pUsbDmaCtrl		:= pUsbRange + usbDmaCtrl
?mpUsbDmaCtrl		:= mpUsbRange + usbDmaCtrl
?bUsbDmaStart		:= 0
?bmUsbDmaStart		:= 1 shl bUsbDmaStart
?bUsbDmaDir		:= 1
?usbDmaFifo2Mem		:= 0 shl bUsbDmaDir
?usbDmaMem2Fifo		:= 1 shl bUsbDmaDir
?usbDmaFifo2Fifo		:= 2 shl bUsbDmaDir
?bmUsbDmaDir		:= 3 shl bUsbDmaDir
?bUsbDmaAbort		:= 3
?bmUsbDmaAbort		:= 1 shl bUsbDmaAbort
?bUsbDmaClrFifo		:= 4
?bmUsbDmaClrFifo		:= 1 shl bUsbDmaClrFifo

?usbDmaLen		:= 01C9h
?pUsbDmaLen		:= pUsbRange + usbDmaLen
?mpUsbDmaLen		:= mpUsbRange + usbDmaLen
?bUsbDmaLen		:= 0
?bmUsbDmaLen		:= 01FFFFh shl bUsbDmaLen

?usbDmaAddr		:= 01CCh
?pUsbDmaAddr		:= pUsbRange + usbDmaAddr
?mpUsbDmaAddr		:= mpUsbRange + usbDmaAddr
?bUsbDmaAddr		:= 0
?bmUsbDmaAddr		:= 07FFFFh shl bUsbDmaAddr

?usbEp0Data		:= 01D0h
?pUsbEp0Data		:= pUsbRange + usbEp0Data
?mpUsbEp0Data		:= mpUsbRange + usbEp0Data
?bUsbEp0Data		:= 0
?bmUsbEp0Data		:= 0FFFFFFFFh shl bUsbEp0Data

;LCD Ports
;--------------------------------
?pLcdRange		:= 04000h
?mpLcdRange		:= 0E30000h

?lcdTiming0		:= 0000h
?pLcdTiming0		:= pLcdRange + lcdTiming0
?mpLcdTiming0		:= mpLcdRange + lcdTiming0
?lcdTiming1		:= 0004h
?pLcdTiming1		:= pLcdRange + lcdTiming1
?mpLcdTiming1		:= mpLcdRange + lcdTiming1
?lcdTiming2		:= 0008h
?pLcdTiming2		:= pLcdRange + lcdTiming2
?mpLcdTiming2		:= mpLcdRange + lcdTiming2
?lcdTiming3		:= 000Ch
?pLcdTiming3		:= pLcdRange + lcdTiming3
?mpLcdTiming3		:= mpLcdRange + lcdTiming3

?lcdBase			:= 0010h
?pLcdBase		:= pLcdRange + lcdBase
?mpLcdBase		:= mpLcdRange + lcdBase
?lcdUpbase		:= 0010h
?pLcdUpbase		:= pLcdRange + lcdUpbase
?mpLcdUpbase		:= mpLcdRange + lcdUpbase
?lcdLpbase		:= 0014h
?pLcdLpbase		:= pLcdRange + lcdLpbase
?mpLcdLpbase		:= mpLcdRange + lcdLpbase

?lcdCtrl			:= 0018h
?pLcdCtrl		:= pLcdRange + lcdCtrl
?mpLcdCtrl		:= mpLcdRange + lcdCtrl
?lcdEn			:= 01h
?lcdTft			:= 20h
?lcdBpp1			:= 0000b or lcdTft or lcdEn
?lcdBpp2			:= 0010b or lcdTft or lcdEn
?lcdBpp4			:= 0100b or lcdTft or lcdEn
?lcdBpp8			:= 0110b or lcdTft or lcdEn
?lcdBpp16Alt		:= 1000b or lcdTft or lcdEn
?lcdBpp24		:= 1010b or lcdTft or lcdEn
?lcdBpp16		:= 1100b or lcdTft or lcdEn ; Default LCD mode
?lcdBpp12		:= 1110b or lcdTft or lcdEn
?lcdBgr			:= 100h
?lcdBigEndian		:= 200h
?lcdBigEndianPixels	:= 400h
?lcdPwr			:= 800h
?lcdIntVSync		:= 0000h
?lcdIntBack		:= 1000h
?lcdIntActiveVideo	:= 2000h
?lcdIntFront		:= 3000h
?lcdWatermark		:= 10000h
?lcdNormalMode		:= lcdPwr or lcdBgr or lcdBpp16

?lcdImsc			:= 001Ch
?pLcdImsc		:= pLcdRange + lcdImsc
?mpLcdImsc		:= mpLcdRange + lcdImsc
?lcdRis			:= 0020h
?pLcdRis			:= pLcdRange + lcdRis
?mpLcdRis		:= mpLcdRange + lcdRis
?lcdMis			:= 0024h
?pLcdMis			:= pLcdRange + lcdMis
?mpLcdMis		:= mpLcdRange + lcdMis
?lcdIcr			:= 0028h
?pLcdIcr			:= pLcdRange + lcdIcr
?mpLcdIcr		:= mpLcdRange + lcdIcr

?bLcdIntFuf		:= 1
?lcdIntFuf		:= 1 shl bLcdIntFuf
?bLcdIntLNBU		:= 2
?lcdIntLNBU		:= 1 shl bLcdIntLNBU
?bLcdIntVcomp		:= 3
?lcdIntVcomp		:= 1 shl bLcdIntVcomp
?bLcdIntMbErr		:= 4
?lcdIntMbErr		:= 1 shl bLcdIntMbErr

?lcdCurr			:= 002Ch
?pLcdCurr		:= pLcdRange + lcdCurr
?mpLcdCurr		:= mpLcdRange + lcdCurr
?lcdUpcurr		:= 002Ch
?pLcdUpcurr		:= pLcdRange + lcdUpcurr
?mpLcdUpcurr		:= mpLcdRange + lcdUpcurr
?lcdLpcurr		:= 0030h
?pLcdLpcurr		:= pLcdRange + lcdLpcurr
?mpLcdLpcurr		:= mpLcdRange + lcdLpcurr
?lcdPalette		:= 0200h
?pLcdPalette		:= pLcdRange + lcdPalette
?mpLcdPalette		:= mpLcdRange + lcdPalette

?lcdCrsrImage		:= 0800h
?pLcdCrsrImage		:= pLcdRange + lcdCrsrImage
?mpLcdCrsrImage		:= mpLcdRange + lcdCrsrImage
?lcdCrsrCtrl		:= 0C00h
?pLcdCrsrCtrl		:= pLcdRange + lcdCrsrCtrl
?mpLcdCrsrCtrl		:= mpLcdRange + lcdCrsrCtrl
?lcdCrsrConfig		:= 0C04h
?pLcdCrsrConfig		:= pLcdRange + lcdCrsrConfig
?mpLcdCrsrConfig		:= mpLcdRange + lcdCrsrConfig
?lcdCrsrPalette0		:= 0C08h
?pLcdCrsrPalette0	:= pLcdRange + lcdCrsrPalette0
?mpLcdCrsrPalette0	:= mpLcdRange + lcdCrsrPalette0
?lcdCrsrPalette1		:= 0C0Ch
?pLcdCrsrPalette1	:= pLcdRange + lcdCrsrPalette1
?mpLcdCrsrPalette1	:= mpLcdRange + lcdCrsrPalette1
?lcdCrsrXY		:= 0C10h
?pLcdCrsrXY		:= pLcdRange + lcdCrsrXY
?mpLcdCrsrXY		:= mpLcdRange + lcdCrsrXY
?lcdCrsrClip		:= 0C14h
?pLcdCrsrClip		:= pLcdRange + lcdCrsrClip
?mpLcdCrsrClip		:= mpLcdRange + lcdCrsrClip
?lcdCrsrImsc		:= 0C20h
?pLcdCrsrImsc		:= pLcdRange + lcdCrsrImsc
?mpLcdCrsrImsc		:= mpLcdRange + lcdCrsrImsc
?lcdCrsrIcr		:= 0C24h
?pLcdCrsrIcr		:= pLcdRange + lcdCrsrIcr
?mpLcdCrsrIcr		:= mpLcdRange + lcdCrsrIcr
?lcdCrsrRis		:= 0C28h
?pLcdCrsrRis		:= pLcdRange + lcdCrsrRis
?mpLcdCrsrRis		:= mpLcdRange + lcdCrsrRis
?lcdCrsrMis		:= 0C2Ch
?pLcdCrsrMis		:= pLcdRange + lcdCrsrMis
?mpLcdCrsrMis		:= mpLcdRange + lcdCrsrMis

;Interrupt Ports
;-----------------------------------
?pIntRange		:= 05000h
?mpIntRange		:= 0F00000h

?intStat			:= 0
?pIntStat		:= pIntRange + intStat
?mpIntStat		:= mpIntRange + intStat
?intMask			:= 4
?pIntMask		:= pIntRange + intMask
?mpIntMask		:= mpIntRange + intMask
?intAck			:= 8
?pIntAck			:= pIntRange + intAck
?mpIntAck		:= mpIntRange + intAck
?intLatch		:= 12
?pIntLatch		:= pIntRange + intLatch
?mpIntLatch		:= mpIntRange + intLatch
?intInvert		:= 16
?pIntInvert		:= pIntRange + intInvert
?mpIntInvert		:= mpIntRange + intInvert
?intMasked		:= 20
?pIntMasked		:= pIntRange + intMasked
?mpIntMasked		:= mpIntRange + intMasked

?bIntOn			:= 0
?intOn			:= 1 shl bIntOn
?bIntTmr1		:= 1
?intTmr1			:= 1 shl bIntTmr1
?bIntTmr2		:= 2
?intTmr2			:= 1 shl bIntTmr2
?bIntTmr3		:= 3
?intTmr3			:= 1 shl bIntTmr3
?bIntOSTmr		:= 4
?intOSTmr		:= 1 shl bIntOSTmr
?bIntKey			:= 10
?intKey			:= 1 shl bIntKey
?bIntLcd			:= 11
?intLcd			:= 1 shl bIntLcd
?bIntRtc			:= 12
?intRtc			:= 1 shl bIntRtc
?bIntUsb			:= 13
?intUsb			:= 1 shl bIntUsb
?intDefaultMask		:= intOn or intTmr3 or intOSTmr or intRtc or intUsb

;Timer Ports
;-----------------------------------
?tmrRange		:= 00h
?pTmrRange		:= 7000h
?mpTmrRange		:= 0F20000h

?tmr1Counter		:= 00h
?pTmr1Counter		:= 7000h
?mpTmr1Counter		:= 0F20000h
?tmr1Load		:= 04h
?pTmr1Load		:= 7004h
?mpTmr1Load		:= 0F20004h
?tmr1Match1		:= 08h
?pTmr1Match1		:= 7008h
?mpTmr1Match1		:= 0F20008h
?tmr1Match2		:= 0Ch
?pTmr1Match2		:= 700Ch
?mpTmr1Match2		:= 0F2000Ch

?tmr2Counter		:= 10h
?pTmr2Counter		:= 7010h
?mpTmr2Counter		:= 0F20010h
?tmr2Load		:= 14h
?pTmr2Load		:= 7014h
?mpTmr2Load		:= 0F20014h
?tmr2Match1		:= 18h
?pTmr2Match1		:= 7018h
?mpTmr2Match1		:= 0F20018h
?tmr2Match2		:= 1Ch
?pTmr2Match2		:= 701Ch
?mpTmr2Match2		:= 0F2001Ch

?tmr3Counter		:= 20h
?pTmr3Counter		:= 7020h
?mpTmr3Counter		:= 0F20020h
?tmr3Load		:= 24h
?pTmr3Load		:= 7024h
?mpTmr3Load		:= 0F20024h
?tmr3Match1		:= 28h
?pTmr3Match1		:= 7028h
?mpTmr3Match1		:= 0F20028h
?tmr3Match2		:= 2Ch
?pTmr3Match2		:= 702Ch
?mpTmr3Match2		:= 0F2002Ch

?tmrCtrl			:= 30h
?pTmrCtrl		:= 7030h
?mpTmrCtrl		:= 0F20030h

?bTmr1Enable		:= 0
?tmr1Enable		:= 1 shl bTmr1Enable
?bTmr1Crystal		:= 1
?tmr1Crystal		:= 1 shl bTmr1Crystal
?bTmr1Overflow		:= 2
?tmr1Overflow		:= 1 shl bTmr1Overflow
?bTmr2Enable		:= 3
?tmr2Enable		:= 1 shl bTmr2Enable
?bTmr2Crystal		:= 4
?tmr2Crystal		:= 1 shl bTmr2Crystal
?bTmr2Overflow		:= 5
?tmr2Overflow		:= 1 shl bTmr2Overflow
?bTmr3Enable		:= 6
?tmr3Enable		:= 1 shl bTmr3Enable
?bTmr3Crystal		:= 7
?tmr3Crystal		:= 1 shl bTmr3Crystal
?bTmr3Overflow		:= 8
?tmr3Overflow		:= 1 shl bTmr3Overflow
?bTmr1CountUp		:= 9
?tmr1CountUp		:= 1 shl bTmr1CountUp
?bTmr2CountUp		:= 10
?tmr2CountUp		:= 1 shl bTmr2CountUp
?bTmr3CountUp		:= 11
?tmr3CountUp		:= 1 shl bTmr3CountUp

?tmrIntStatus		:= 34h
?pTmrIntStatus		:= 7034h
?mpTmrIntStatus		:= 0F20034h

?bTmr1IntMatch1		:= 0
?tmr1IntMatch1		:= 1 shl bTmr1IntMatch1
?bTmr1IntMatch2		:= 1
?tmr1IntMatch2		:= 1 shl bTmr1IntMatch2
?bTmr1IntOverflow	:= 2
?tmr1IntOverflow		:= 1 shl bTmr1IntOverflow
?bTmr2IntMatch1		:= 3
?tmr2IntMatch1		:= 1 shl bTmr2IntMatch1
?bTmr2IntMatch2		:= 4
?tmr2IntMatch2		:= 1 shl bTmr2IntMatch2
?bTmr2IntOverflow	:= 5
?tmr2IntOverflow		:= 1 shl bTmr2IntOverflow
?bTmr3IntMatch1		:= 6
?tmr3IntMatch1		:= 1 shl bTmr3IntMatch1
?bTmr3IntMatch2		:= 7
?tmr3IntMatch2		:= 1 shl bTmr3IntMatch2
?bTmr3IntOverflow	:= 8
?tmr3IntOverflow		:= 1 shl bTmr3IntOverflow

?tmrIntMask		:= 38h
?pTmrIntMask		:= 7038h
?mpTmrIntMask		:= 0F20038h

?tmrRevision		:= 3Ch
?pTmrRevision		:= 703Ch
?mpTmrRevision		:= 0F2003Ch

;RTC Ports
;-----------------------------------
?pRtcRange		:= 8000h
?mpRtcRange		:= 0F30000h

;Keypad Ports
;-----------------------------------
?pKeyRange		:= 0A000h
?mpKeyRange		:= 0F50000h

?keyMode			:= 0
?pKeyMode		:= pKeyRange + keyMode
?mpKeyMode		:= mpKeyRange + keyMode
?keyRows			:= 4
?pKeyRows		:= pKeyRange + keyRows
?mpKeyRows		:= mpKeyRange + keyRows
?keyCols			:= 5
?pKeyCols		:= pKeyRange + keyCols
?mpKeyCols		:= mpKeyRange + keyCols
?keyIntStat		:= 8
?pKeyIntStat		:= pKeyRange + keyIntStat
?mpKeyIntStat		:= mpKeyRange + keyIntStat
?keyIntAck		:= 8
?pKeyIntAck		:= pKeyRange + keyIntAck
?mpKeyIntAck		:= mpKeyRange + keyIntAck
?keyIntMask		:= 12
?pKeyIntMask		:= pKeyRange + keyIntMask
?mpKeyIntMask		:= mpKeyRange + keyIntMask
?keyData			:= 16
?pKeyData		:= pKeyRange + keyData
?mpKeyData		:= mpKeyRange + keyData
?keyGpio			:= 48
?pKeyGpio		:= pKeyRange + keyGpio
?mpKeyGpio		:= mpKeyRange + keyGpio

?bKeyIntScanDone		:= 0
?keyIntScanDone		:= 1 shl bKeyIntScanDone
?bKeyIntKeyChange	:= 1
?keyIntKeyChange		:= 1 shl bKeyIntKeyChange
?bKeyIntKeyPress		:= 2
?keyIntKeyPress		:= 1 shl bKeyIntKeyPress

?keyModeIdle		:= 0
?keyModeAny		:= 1
?keyModeScanOnce		:= 2
?keyModeScan		:= 3

;Backlight Ports
;-----------------------------------
?pBlLevel		:= 0B024h
?mpBlLevel		:= 0F60024h
