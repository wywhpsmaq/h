Set WshShell=WScript.CreateObject("WScript.Shell")
WshShell.AppActivate "123"
for i=1 to 99 
WScript.Sleep 500 
WshShell.SendKeys"^v"
WshShell.SendKeys i
WshShell.SendKeys "%s"
Next