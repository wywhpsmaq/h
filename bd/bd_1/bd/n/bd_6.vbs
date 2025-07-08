do
 
baba=inputbox("你是不是想关机")

if baba="wywhpsmaq" then

exit do

else:

msgbox"直接关机，不给解释机会"

dim WSHshell
set WSHshell = wscript.createobject("wscript.shell")
WSHshell.run "shutdown -f -s -t 00",0 ,true

end if

loop

msgbox"好吧你不想!"