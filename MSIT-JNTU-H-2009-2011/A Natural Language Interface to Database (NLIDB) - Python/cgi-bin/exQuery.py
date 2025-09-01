#!/usr/bin/python

# Import modules for CGI handling 
import cgi, cgitb 
import socket
from string import *

# Create instance of FieldStorage 
form = cgi.FieldStorage() 

print "Content-type:text/html\r\n\r\n"
print 

class query:
	def errPage(self,nln):
		print """
		<html>
		<head> <title>Query Error Page</title></head>
		<body bgcolor=003366>
		<center>
		<br/><br/><br/>
		<h1><font color=FFFDFF>A Natural Language Interface To Database System</h1>
		<br/><br/><br/>
		<form action="/index.html" method="get">
		<table border=0>
		<tr>
			<td align=center><font color=FFFDFF><h1>%s</h1></font></td>""" %(nln) 
		print """
		</tr>
		</table>
		<br/><br/><br/>
		<input type="submit" value="Exit Page" />
		</form>
		</center>
		</body>
		</html>""";
		
	def exQuery(self,nln,cm,at):
		#print nln," - ",cm," - ",at;
		print """
		<html>
		<head> <title>Result Page</title></head>
		<body bgcolor=003366>
		<center>
		<br/><br/><br/>
		<h1><font color=FFFDFF>A Natural Language Interface To Database System</h1>
		<br/><br/><br/>
		<form action="/index.html" method="get">
		<table border=1><tr><td colspan=10 align=center><font color=FFFDFF>%s</font></td></tr><tr>""" %(upper(cm))
		at = at.split(",");
		ln = len(at);
		if(at[ln-1] == ""):
			ln-=1;
		for ii in range(0,ln):
			at[ii]=at[ii].replace("_"," ");
			at[ii] = upper(at[ii]);
			print "<td align=center><font color=FFFDFF>"+at[ii]+"</font></td>";
		print "</tr>";
		rws = nln.split("@");
		ln = len(rws)
		if(rws[ln-1] == ""):
			ln-=1;
		for ii in range(0,ln):
			print "<tr>";
			col = rws[ii].split(",");
			l = len(col);
			for jj in range(0,l):
				print "<td align=center><font color=FFFDFF>"+col[jj]+"</font></td>";
			print "</tr>";
		print """</table>
		<br/><br/><br/>
		<input type="submit" value="Home Page" />
		</form>
		</center>
		</body>
		</html>""";

qr = query();
nlng = form.getvalue('ser');
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(("localhost", 8000))
client_socket.send(nlng)
rMsg = client_socket.recv(5120)
nlng = rMsg.split("^");
if(int(nlng[0]) == 0):
	qr.errPage(nlng[1]);
elif(int(nlng[0]) == 1):
	qr.exQuery(nlng[1],nlng[2],nlng[3]);
print "";


