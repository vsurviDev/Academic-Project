# TCP server example
#!/usr/bin/env python 
import socket
from string import *
import MySQLdb
import re
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
port = 8000;
server_socket.bind(("", port))
server_socket.listen(5)

conn = MySQLdb.connect (host = "localhost",
                           user = "root",
                           passwd = "",
                           db = "projectDB")
cursor = conn.cursor ()

class qry:
	def queryProcess(self,rMsg):
		sData = "";
		fpr = open("StopWords.txt","r");
		lines = fpr.readlines();
		fpr.close();
		cMsg = rMsg.split(" ");
		ln = len(cMsg);
		for line in lines:
			line = line.replace("\n","");
			line = line.replace("\"","");
			line=lower(line);
			for ii in range(0,ln):
				cMsg[ii] = cMsg[ii].replace("?","");
				cMsg[ii]=lower(cMsg[ii]);
				if(line == cMsg[ii]):
					cMsg[ii] = "";
		for ii in range(0,ln):
			if(cMsg[ii] != ""):
				sData=sData+" "+cMsg[ii];
				
		vData = self.queryPreparation(sData);
		vData = vData.split("|");
		col = int(vData[0]);
		#ERROR
		try :
			rt = cursor.execute(vData[1]);
			cm = vData[2];
			at = vData[3];
			vData = cursor.fetchall();
			sData = "";
			for ii in range(0,rt):
				kk=vData[ii]
				for jj in range(0,col):
					if((jj+1) == col):
						sData = sData + str(kk[jj]).replace(","," ");
					else:
						sData = sData + str(kk[jj]).replace(","," ") + ",";
				sData = sData + "@";
			if(rt > 0):
				rt = 1;
				sData=str(rt)+"^"+str(sData)+"^"+cm+"^"+at;
		except :
			rt = 0;
			sData=str(rt)+"^Query Doesn't Exist";

		#print "\n2----------------- "+sData;
		return sData;
	
	def queryPreparation(self,sData):
		finance = [];
		management = [];
		profiles = [];
		fpr = open("config.txt","r");
		lines = fpr.readlines();
		fpr.close();
		tbl = "";
		attr = [];
		tikr = [];
		for line in lines:
			line = line.replace("\n","");
			line = line.split(":");
			idx = len(line);
			if(idx == 1):
				tbl = line[0];
			elif(idx > 1):
				if(tbl == "finance"):
					finance.append(line[0]);
				elif(tbl == "management"):
					management.append(line[0]);
				elif(tbl == "profiles"):
					profiles.append(line[0]);
		vData = self.simpleMessage(sData);
		vData = vData.split(" ");
		ln = len(vData);
		at = "";
		for ii in range(0,ln):
			if(vData[ii] in finance):
				attr.append("f."+vData[ii]);
				at = at + vData[ii] + ",";
			elif(vData[ii] in management):
				attr.append("m."+vData[ii]);
				at = at + vData[ii] + ",";
			elif(vData[ii] in profiles):
				attr.append("p."+vData[ii]);
				at = at + vData[ii] + ",";
		ln = len(attr);
		col = ln;
		sData = "select "
		if(ln == 1):
			sData=sData+attr[0]+" from finance f,management m,profiles p";
		elif(ln > 1):
			sData=sData+attr[0];
			for ii in range(1,ln):
				sData = sData+","+attr[ii];
			sData=sData+" from finance f,management m,profiles p";
		ln = len(vData);
		fpr = open("company.txt","r");
		lines = fpr.readlines();
		fpr.close();
		cnt = 0;
		cm = "";
		for line in lines:
			line = line.replace("\n","");
			line = line.split(":");
			cp = line[1];
			line[1] = lower(line[1]);
			cmpy = line[1].split(" ");
			for ii in range(0,ln):
				if(vData[ii] in cmpy):
					if(cnt == 0):
						cm = cp;
						sData = sData + " where "; 
					elif(cnt != 0):
						cm = cm +" and "+ cp;
						sData = sData + " and ";
					sData = sData+"f.fin_ticker = \""+line[0]+"\" and m.mgt_ticker = \""+line[0]+"\" and p.ticker = \""+line[0]+"\"";
					cnt = cnt + 1;
					break;
		sData = str(col)+"|"+sData+"|"+cm+"|"+at;
		#print "\n1----------------- "+sData;
		return sData;
			
	def simpleMessage(self,vData):
		sData = "";
		fpr = open("KeyWords.txt","r");
		lines = fpr.readlines();
		fpr.close();
		cMsg = vData.split(" ");
		ln = len(cMsg);
		for line in lines:
			line = line.replace("\n","");
			line = line.split(":");
			for ii in range(0,ln):
				if(cMsg[ii] in line):
					cMsg[ii] = line[0];
		for ii in range(0,ln):
			if(cMsg[ii] != ""):
				sData=sData+" "+cMsg[ii];
		
		return sData;
	
print "TCPServer Waiting for client on port "+str(port)
qr = qry();
while 1:
	client_socket, address = server_socket.accept()
	print "I got a connection from ", address
        rData = client_socket.recv(512)
	ret = qr.queryProcess(rData);
	rData = ret;
	#print "\n3----------------- "+rData;
	client_socket.send (rData)
	client_socket.close()
