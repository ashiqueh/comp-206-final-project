#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import os
import cgi

#Gets the current user from POST
form = cgi.FieldStorage()
userID = form.getvalue("userID")

print 'Content-type: text/html\r\n\r'
print '''
<html>
<head><title> Status Updated! </title></head>
<body bgcolor="#333333" text="white">
	<form action="dashboard.py" method="POST">
		<input type="submit" value="Back to Dashboard">
		<input type="hidden" name="userID" value="'''+userID+'''">
	</form>
'''

status = form.getfirst("status", "").upper()

if "status" in form:
	inputStatus = userID + " " + form["status"].value

	sysIn = "echo "+inputStatus+" >> ../status.txt "
	os.system(sysIn)

print '''
</body>
</html>
'''
