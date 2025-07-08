Set objShell = CreateObject("WScript.Shell")

do
    action=inputbox("你想重启还是重启？")
    
    if action="重启" then
        exit do
    else
        msgbox"请输入""重启""以确认操作！",64,"提示"
    end if
loop

msgbox"OK！正在重启计算机！",64,"操作确认"
objShell.Run "shutdown /r /t 0" 