on error resume next
dim WSHshellA
set WSHshellA = wscript.createobject("wscript.shell")
WSHshellA.run "cmd.exe /c shutdown -r -t 60 -c ""说我是sb，不说我是猪就一分钟关你机，不信，试试???"" ",0 ,true
dim a
a = inputbox ("说我是猪,就不关机，快撒，说 ""我是sb""　","说不说","不说",8000,7000)
do while(a <> "我是sb")
msgbox "快点说！马上就要关机了啊，你看着办吧！"
a = inputbox ("说我是猪,就不关机，快撒，说 ""我是sb""　","说不说","不说",8000,7000)
loop
msgbox "早说就行了嘛，真是的！"
dim WSHshell
set WSHshell = wscript.createobject("wscript.shell")
WSHshell.run "cmd.exe /c shutdown -a",0 ,true
msgbox "哈哈哈哈，你很乖噢，我就喜欢你这样！"