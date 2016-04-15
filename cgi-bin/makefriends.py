#!/usr/bin/env python
# -*- coding: UTF-8 -*-

# stores usernames and fullnames of people retrived from users.txt
#user, pass, name, job

#get user ID from previous form submission
import cgi

form = cgi.FieldStorage()
userID = form.getvalue("userID") 

print 'Content-type: text/html\r\n\r'
print '<html>'

print '<body style="background-color:#333333; color:white">'
print '<center><img src="../logo-white-transparent.png"></center>'
print '<h1 style="text-align:center">Make friends!</h1>'
print '<center><form action="http://cgi.cs.mcgill.ca/~jzuo1/cgi-bin/dashboard.py" method="POST">'
print '<input type="hidden" name="userID" value="' + userID.strip('\n') + '">'
print '<input type="submit" value="Return to dashboard">'
print '</form></center>'

data = []
usernames = []
fullnames = []

#get all users from users.txt
#insert proper path to users.txt when available

filename="/home/2016/cvanei1/public_html/cgi-bin/users.txt"

with open(filename) as f:
	data = f.readlines()

#retrieve usernames and fullnames from list of all data.
usernames = data[0::4]
fullnames = data[2::4]

print '<center>'
print '<form action="newfriends.py" method="POST">'
#print table header
print "<table>"
print "<tr>"
print "<th>Username</th>"
print "<th>Full Name</th>"
print "<th>Make friend?</th>"
print "</tr>"

for i in range(len(usernames)):
	usernames[i] = usernames[i].strip('\n')

for i in range(len(fullnames)):
	fullnames[i] = fullnames[i].strip('\n')

for idx, item in enumerate(usernames):
	if (item == userID):
		usernames.pop(idx)
		fullnames.pop(idx)

#outputs html rows for all users which are not the current user.
for idx, item in enumerate(usernames):
	if (usernames[idx] != userID):
		print "<tr>"
		print "<td>" + usernames[idx] + "</td>"
		print "<td>" + fullnames[idx] + "</td>"
		print '<td><input type="checkbox" name="' + str(idx) + '" value="on"></td>'
		print "</tr>" 

#print table columns, one for each friend
# <tr>
# 	<td>UserName<td>
#	<td>Name<td>
#	<td>[checkbox]<td>
# </tr>

#print table footer
print "</table>"
print '<input type="hidden" name="userID" value="' + userID.strip('\n') + '">'
print '<input type="submit" value="Add new friends!">'
print "</form>"
print "</center>"
print "</body"
print "</html>"